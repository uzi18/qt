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

#include <QtGui>

//! [0]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QPushButton button;
    QStateMachine machine;
//! [0]

//! [1]
    QState *off = new QState();
    off->assignProperty(&button, "text", "Off");
    off->setObjectName("off");

    QState *on = new QState();
    on->setObjectName("on");
    on->assignProperty(&button, "text", "On");
//! [1]

//! [2]
    off->addTransition(&button, SIGNAL(clicked()), on);
    on->addTransition(&button, SIGNAL(clicked()), off);
//! [2]

//! [3]
    machine.addState(off);
    machine.addState(on);
//! [3]

//! [4]
    machine.setInitialState(off);
    machine.start();
//! [4]

//! [5]
    button.resize(100, 50);
    button.show();
    return app.exec();
}
//! [5]