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

#ifndef QT_S60_P_H
#define QT_S60_P_H

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

#include "QtGui/qwindowdefs.h"
#include "private/qcore_symbian_p.h"
#include "qhash.h"
#include "qpoint.h"
#include "QtGui/qfont.h"
#include "QtGui/qimage.h"
#include "QtGui/qevent.h"
#include "qpointer.h"
#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <eikappui.h>
#include <aknutils.h>               // AknLayoutUtils
#include <avkon.hrh>                // EEikStatusPaneUidTitle
#include <akntitle.h>               // CAknTitlePane
#include <akncontext.h>             // CAknContextPane
#include <eikspane.h>               // CEikStatusPane
    
QT_BEGIN_NAMESPACE

// Application internal HandleResourceChangeL events, 
// system evens seems to start with 0x10
const TInt KInternalStatusPaneChange = 0x50000000;

struct QS60Data;
extern QS60Data *qt_s60Data;

#define S60 qt_s60Data

class QS60Data
{
public:
    TUid uid;
    int screenDepth;
    QPoint lastCursorPos;
    QPoint lastPointerEventPos;
    QPointer<QWidget> lastPointerEventTarget;
    QPointer<QWidget> mousePressTarget;
    int screenWidthInPixels;
    int screenHeightInPixels;
    int screenWidthInTwips;
    int screenHeightInTwips;
    int defaultDpiX;
    int defaultDpiY;
    static inline void updateScreenSize();
    static inline RWsSession& wsSession();
    static inline RWindowGroup& windowGroup();
    static inline CWsScreenDevice* screenDevice();
    static inline CCoeAppUi* appUi();
    static inline CEikStatusPane* statusPane();
    static inline CCoeControl* statusPaneSubPane(TInt aPaneId);
    static inline CAknTitlePane* titlePane();
    static inline CAknContextPane* contextPane();
    static inline CEikButtonGroupContainer* buttonGroupContainer();
};

class QAbstractLongTapObserver
{
public:
    virtual void HandleLongTapEventL( const TPoint& aPenEventLocation, 
                                      const TPoint& aPenEventScreenLocation ) = 0;
};
class QLongTapTimer;

class QSymbianControl : public CCoeControl, public QAbstractLongTapObserver
{
public:
    DECLARE_TYPE_ID(0x51740000) // Fun fact: the two first values are "Qt" in ASCII.

public:
    QSymbianControl(QWidget *w);
    void ConstructL(bool topLevel = false, bool desktop = false);
    ~QSymbianControl();
    void HandleResourceChange(int resourceType);
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
#ifndef QT_NO_IM
    TCoeInputCapabilities InputCapabilities() const;
#endif
    TTypeUid::Ptr MopSupplyObject(TTypeUid id);

    inline QWidget* widget() const { return qwidget; };
    void setWidget(QWidget *w);
    void sendInputEvent(QWidget *widget, QInputEvent *inputEvent);
    void setIgnoreFocusChanged(bool enabled) { m_ignoreFocusChanged = enabled; }
    void CancelLongTapTimer();

protected:
    void Draw(const TRect& aRect) const;
    void SizeChanged();
    void PositionChanged();
    void FocusChanged(TDrawNow aDrawNow);

private:
    TKeyResponse sendKeyEvent(QWidget *widget, QKeyEvent *keyEvent);
    void sendMouseEvent(QWidget *widget, QMouseEvent *mEvent);
    void HandleLongTapEventL( const TPoint& aPenEventLocation, const TPoint& aPenEventScreenLocation );

private:
    QWidget *qwidget;
    bool m_ignoreFocusChanged;
    QLongTapTimer* m_longTapDetector;
    bool m_previousEventLongTap;
};

inline void QS60Data::updateScreenSize()
{
    TPixelsTwipsAndRotation params;
    int mode = S60->screenDevice()->CurrentScreenMode();
    S60->screenDevice()->GetScreenModeSizeAndRotation(mode, params);
    S60->screenWidthInPixels = params.iPixelSize.iWidth;
    S60->screenHeightInPixels = params.iPixelSize.iHeight;
    S60->screenWidthInTwips = params.iTwipsSize.iWidth;
    S60->screenHeightInTwips = params.iTwipsSize.iHeight;

    TReal inches = S60->screenHeightInTwips / (TReal)KTwipsPerInch;
    S60->defaultDpiY = S60->screenHeightInPixels / inches;
    inches = S60->screenWidthInTwips / (TReal)KTwipsPerInch;
    S60->defaultDpiX = S60->screenWidthInPixels / inches;
}

inline RWsSession& QS60Data::wsSession()
{
    return CCoeEnv::Static()->WsSession();
}

inline RWindowGroup& QS60Data::windowGroup()
{
    return CCoeEnv::Static()->RootWin();
}

inline CWsScreenDevice* QS60Data::screenDevice()
{
    return CCoeEnv::Static()->ScreenDevice();
}

inline CCoeAppUi* QS60Data::appUi()
{
    return CCoeEnv::Static()-> AppUi();
}

inline CEikStatusPane* QS60Data::statusPane()
{
    return CEikonEnv::Static()->AppUiFactory()->StatusPane();
}

// Returns the application's status pane control, if not present returns NULL.
inline CCoeControl* QS60Data::statusPaneSubPane( TInt aPaneId )
{
    const TUid paneUid = { aPaneId };
    CEikStatusPane* statusPane = S60->statusPane();
    if (statusPane && statusPane->PaneCapabilities(paneUid).IsPresent()) {
        CCoeControl* control = NULL;
        // ControlL shouldn't leave because the pane is present
        TRAPD(err, control = statusPane->ControlL(paneUid));
        return err != KErrNone ? NULL : control;
    }
    return NULL;
}

// Returns the application's title pane, if not present returns NULL.
inline CAknTitlePane* QS60Data::titlePane()
{
    return static_cast<CAknTitlePane*>(S60->statusPaneSubPane(EEikStatusPaneUidTitle));
}

// Returns the application's title pane, if not present returns NULL.
inline CAknContextPane* QS60Data::contextPane()
{
    return static_cast<CAknContextPane*>(S60->statusPaneSubPane(EEikStatusPaneUidContext));
}

inline CEikButtonGroupContainer* QS60Data::buttonGroupContainer()
{
    return CEikonEnv::Static()->AppUiFactory()->Cba();
}

static inline QFont qt_TFontSpec2QFontL(const TFontSpec &fontSpec)
{
    return QFont(
        qt_TDesC2QStringL(fontSpec.iTypeface.iName),
        fontSpec.iHeight / KTwipsPerPoint,
        fontSpec.iFontStyle.StrokeWeight() == EStrokeWeightNormal ? QFont::Normal : QFont::Bold,
        fontSpec.iFontStyle.Posture() == EPostureItalic
    );
}

static inline QImage::Format qt_TDisplayMode2Format(TDisplayMode mode)
{
	QImage::Format format;
	switch(mode) {
	case EColor256:
	    // TODO: is the correct?
	    format = QImage::Format_Indexed8;
	    break;
	case EColor4K:
	    format = QImage::Format_RGB444;
	    break;
	case EColor64K:
	    format = QImage::Format_RGB16;
	    break;
	case EColor16M:
	    format = QImage::Format_RGB666;
	    break;
	case EColor16MU:
	    format = QImage::Format_RGB32;
	    break;
	case EColor16MA:
	    format = QImage::Format_ARGB32;
	    break;
#ifdef __S60_50__ 	    
	case EColor16MAP:
	    format = QImage::Format_ARGB32_Premultiplied;
	    break;
#endif	    
	default:
	    qFatal("Screen format not supported");
	    break;
	}
	return format;
}


QT_END_NAMESPACE

#endif // QT_S60_P_H