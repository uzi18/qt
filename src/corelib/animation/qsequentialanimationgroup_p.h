/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSEQUENTIALANIMATIONGROUP_P_H
#define QSEQUENTIALANIMATIONGROUP_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QIODevice. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qsequentialanimationgroup.h"
#include "private/qanimationgroup_p.h"


QT_BEGIN_NAMESPACE

class QSequentialAnimationGroupPrivate : public QAnimationGroupPrivate
{
    Q_DECLARE_PUBLIC(QSequentialAnimationGroup)
public:
    QSequentialAnimationGroupPrivate()
        : currentAnimation(0), currentAnimationIndex(-1), lastLoop(0)
    { }


    struct AnimationIndex
    {
        AnimationIndex() : index(0), timeOffset(0) {}
        // index points to the animation at timeOffset, skipping 0 duration animations.
        // Note that the index semantic is slightly different depending on the direction.
        int index; // the index of the animation in timeOffset
        int timeOffset; // time offset when the animation at index starts.
    };

    int animationActualTotalDuration(int index) const;
    AnimationIndex indexForTime(int msecs) const;

    void setCurrentAnimation(int index, bool intermediate = false);
    void activateCurrentAnimation(bool intermediate = false);

    void animationInsertedAt(int index);
    void animationRemovedAt(int index);

    bool atEnd() const;

    QAbstractAnimation *currentAnimation;
    int currentAnimationIndex;

    // this is the actual duration of uncontrolled animations
    // it helps seeking and even going forward
    QList<int> actualDuration;

    void restart();
    int lastLoop;

    // handle time changes
    void rewindForwards(const AnimationIndex &newAnimationIndex);
    void advanceForwards(const AnimationIndex &newAnimationIndex);

    // private slot
    void _q_uncontrolledAnimationFinished();
};

QT_END_NAMESPACE

#endif //QSEQUENTIALANIMATIONGROUP_P_H