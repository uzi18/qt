/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the $MODULE$ of the Qt Toolkit.
**
** $TROLLTECH_DUAL_EMBEDDED_LICENSE$
**
****************************************************************************/

#ifndef QEVENTDISPATCHER_SYMBIAN_P_H
#define QEVENTDISPATCHER_SYMBIAN_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qhash.h>
#include <qset.h>
#include <qshareddata.h>
#include <qabstracteventdispatcher.h>
#include <private/qabstracteventdispatcher_p.h>
#include <qthread.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qsocketnotifier.h>

#include <e32base.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

QT_BEGIN_NAMESPACE


class QEventDispatcherSymbian;
class QTimerActiveObject;

class QActiveObject : public CActive
{
public:
    QActiveObject(TInt priority, QEventDispatcherSymbian *dispatcher);
    ~QActiveObject();

    bool okToRun();

    void reactivateAndComplete();

protected:
    QEventDispatcherSymbian *m_dispatcher;

private:
    bool m_hasAlreadyRun : 1;
    bool m_hasRunAgain : 1;
    int m_iterationCount;
};

class QWakeUpActiveObject : public CActive
{
public:
    QWakeUpActiveObject(QEventDispatcherSymbian *dispatcher);
    ~QWakeUpActiveObject();

    void Complete();

protected:
    void DoCancel();
    void RunL();

private:
    QEventDispatcherSymbian *m_dispatcher;
};

struct SymbianTimerInfo : public QSharedData
{
    ~SymbianTimerInfo();

    int timerId;
    int interval;
    bool inTimerEvent;
    QObject *receiver;
    QTimerActiveObject *timerAO;
    QEventDispatcherSymbian *dispatcher;
};

typedef QExplicitlySharedDataPointer<SymbianTimerInfo> SymbianTimerInfoPtr;

// This is a bit of a proxy class. See comments in SetActive and Start for details.
class QTimerActiveObject : public QActiveObject
{
public:
    QTimerActiveObject(QEventDispatcherSymbian *dispatcher, SymbianTimerInfo *timerInfo);
    ~QTimerActiveObject();

    void Start();

protected:
    void DoCancel();
    void RunL();

private:
    SymbianTimerInfo *m_timerInfo;
    RTimer m_rTimer;
};

class QCompleteDeferredAOs : public CActive
{
public:
    QCompleteDeferredAOs(QEventDispatcherSymbian *dispatcher);
    ~QCompleteDeferredAOs();

    void complete();

protected:
    void DoCancel();
    void RunL();

private:
    QEventDispatcherSymbian *m_dispatcher;
};

class QSocketActiveObject : public QActiveObject
{
public:
    QSocketActiveObject(QEventDispatcherSymbian *dispatcher, QSocketNotifier *notifier);
    ~QSocketActiveObject();

    void deleteLater();

protected:
    void DoCancel();
    void RunL();

private:
    QSocketNotifier *m_notifier;
    bool m_inSocketEvent;
    bool m_deleteLater;

    friend class QEventDispatcherSymbian;
};

class QSelectThread : public QThread
{
    Q_DECLARE_PRIVATE(QThread)

public:
    QSelectThread();
    ~QSelectThread();

    void requestSocketEvents ( QSocketNotifier *notifier, TRequestStatus *status );
    void cancelSocketEvents ( QSocketNotifier *notifier );
    void restart();
    void stop();

protected:
    void run();

private:
    int updateSocketSet(QSocketNotifier::Type type, fd_set *fds);
    void updateActivatedNotifiers(QSocketNotifier::Type type, fd_set *fds);

private:
    int m_pipeEnds[2];
    QHash<QSocketNotifier *, TRequestStatus *> m_AOStatuses;
    QMutex m_mutex;
    QWaitCondition m_waitCond;
    bool m_quit;
};

class Q_CORE_EXPORT QEventDispatcherSymbian : public QAbstractEventDispatcher
{
    Q_DECLARE_PRIVATE(QAbstractEventDispatcher)

public:
    QEventDispatcherSymbian(QObject *parent = 0);
    ~QEventDispatcherSymbian();

    void flush();
    bool hasPendingEvents();
    void interrupt();
    bool processEvents ( QEventLoop::ProcessEventsFlags flags );
    void registerSocketNotifier ( QSocketNotifier * notifier );
    void registerTimer ( int timerId, int interval, QObject * object );
    QList<TimerInfo> registeredTimers ( QObject * object ) const;
    void unregisterSocketNotifier ( QSocketNotifier * notifier );
    bool unregisterTimer ( int timerId );
    bool unregisterTimers ( QObject * object );
    void wakeUp();

    void startingUp();
    void closingDown();

    void timerFired(int timerId);
    void socketFired(QSocketActiveObject *socketAO);
    void wakeUpWasCalled();
    void reactivateSocketNotifier(QSocketNotifier *notifier);

    void addDeferredActiveObject(QActiveObject *object);
    void removeDeferredActiveObject(QActiveObject *object);
    void reactivateDeferredActiveObjects();

    inline int iterationCount() const { return m_iterationCount; }

    static void RequestComplete(TRequestStatus *&status, TInt reason);
    static void RequestComplete(RThread &threadHandle, TRequestStatus *&status, TInt reason);

private:
    bool sendPostedEvents();
    bool sendDeferredSocketEvents();

private:
    QSelectThread m_selectThread;

    CActiveScheduler *m_activeScheduler;

    QHash<int, SymbianTimerInfoPtr> m_timerList;
    QHash<QSocketNotifier *, QSocketActiveObject *> m_notifiers;

    QWakeUpActiveObject *m_wakeUpAO;
    QCompleteDeferredAOs *m_completeDeferredAOs;

    volatile bool m_interrupt;
    QAtomicInt m_wakeUpDone;

    unsigned char m_iterationCount;
    bool m_noSocketEvents;
    QList<QSocketActiveObject *> m_deferredSocketEvents;

    QList<QActiveObject *> m_deferredActiveObjects;

    RProcess m_processHandle;
};

#ifdef QT_DEBUG
// EActive is defined to 1 and ERequestPending to 2, but they are both private.
// A little dangerous to rely on, but it is only for debugging.
# define REQUEST_STATUS_ACTIVE_AND_PENDING 3
# define VERIFY_PENDING_REQUEST_STATUS \
    Q_ASSERT(status->Int() & REQUEST_STATUS_ACTIVE_AND_PENDING == REQUEST_STATUS_ACTIVE_AND_PENDING);
#else
# define REQUEST_STATUS_ACTIVE_AND_PENDING
# define VERIFY_PENDING_REQUEST_STATUS
#endif

// Convenience functions for doing some sanity checking on our own complete code.
// Unless QT_DEBUG is defined, it is exactly equivalent to the Symbian version.
inline void QEventDispatcherSymbian::RequestComplete(TRequestStatus *&status, TInt reason)
{
    VERIFY_PENDING_REQUEST_STATUS
    User::RequestComplete(status, reason);
}
inline void QEventDispatcherSymbian::RequestComplete(RThread &threadHandle, TRequestStatus *&status, TInt reason)
{
    VERIFY_PENDING_REQUEST_STATUS
    threadHandle.RequestComplete(status, reason);
}

#undef REQUEST_STATUS_ACTIVE_AND_PENDING
#undef VERIFY_PENDING_REQUEST_STATUS

QT_END_NAMESPACE

#endif // QEVENTDISPATCHER_SYMBIAN_P_H