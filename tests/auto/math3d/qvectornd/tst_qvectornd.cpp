/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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

#include <QtTest/QtTest>
#include <QtCore/qmath.h>
#include "math3dincludes.h"

class tst_QVector : public QObject
{
    Q_OBJECT
public:
    tst_QVector() {}
    ~tst_QVector() {}

private slots:
    void create2();
    void create3();
    void create4();

    void length2_data();
    void length2();
    void length3_data();
    void length3();
    void length4_data();
    void length4();

    void normalized2_data();
    void normalized2();
    void normalized3_data();
    void normalized3();
    void normalized4_data();
    void normalized4();

    void normalize2_data();
    void normalize2();
    void normalize3_data();
    void normalize3();
    void normalize4_data();
    void normalize4();

    void compare2();
    void compare3();
    void compare4();

    void add2_data();
    void add2();
    void add3_data();
    void add3();
    void add4_data();
    void add4();

    void subtract2_data();
    void subtract2();
    void subtract3_data();
    void subtract3();
    void subtract4_data();
    void subtract4();

    void multiply2_data();
    void multiply2();
    void multiply3_data();
    void multiply3();
    void multiply4_data();
    void multiply4();

    void multiplyFactor2_data();
    void multiplyFactor2();
    void multiplyFactor3_data();
    void multiplyFactor3();
    void multiplyFactor4_data();
    void multiplyFactor4();

    void divide2_data();
    void divide2();
    void divide3_data();
    void divide3();
    void divide4_data();
    void divide4();

    void negate2_data();
    void negate2();
    void negate3_data();
    void negate3();
    void negate4_data();
    void negate4();

    void crossProduct_data();
    void crossProduct();
    void normal_data();
    void normal();
    void distanceToPlane_data();
    void distanceToPlane();
    void distanceToLine_data();
    void distanceToLine();

    void dotProduct2_data();
    void dotProduct2();
    void dotProduct3_data();
    void dotProduct3();
    void dotProduct4_data();
    void dotProduct4();
};

// qFuzzyCompare isn't quite "fuzzy" enough to handle conversion
// to fixed-point and back again.  So create "fuzzier" compares.
static bool fuzzyCompare(float x, float y)
{
    float diff = x - y;
    if (diff < 0.0f)
        diff = -diff;
    return (diff < 0.001);
}

// Test the creation of QVector2D objects in various ways:
// construct, copy, and modify.
void tst_QVector::create2()
{
    QVector2D null;
    QCOMPARE(null.x(), (qreal)0.0f);
    QCOMPARE(null.y(), (qreal)0.0f);
    QVERIFY(null.isNull());

    QVector2D v1(1.0f, 2.5f);
    QCOMPARE(v1.x(), (qreal)1.0f);
    QCOMPARE(v1.y(), (qreal)2.5f);
    QVERIFY(!v1.isNull());

    QVector2D v1i(1, 2);
    QCOMPARE(v1i.x(), (qreal)1.0f);
    QCOMPARE(v1i.y(), (qreal)2.0f);
    QVERIFY(!v1i.isNull());

    QVector2D v2(v1);
    QCOMPARE(v2.x(), (qreal)1.0f);
    QCOMPARE(v2.y(), (qreal)2.5f);
    QVERIFY(!v2.isNull());

    QVector2D v4;
    QCOMPARE(v4.x(), (qreal)0.0f);
    QCOMPARE(v4.y(), (qreal)0.0f);
    QVERIFY(v4.isNull());
    v4 = v1;
    QCOMPARE(v4.x(), (qreal)1.0f);
    QCOMPARE(v4.y(), (qreal)2.5f);
    QVERIFY(!v4.isNull());

    QVector2D v5(QPoint(1, 2));
    QCOMPARE(v5.x(), (qreal)1.0f);
    QCOMPARE(v5.y(), (qreal)2.0f);
    QVERIFY(!v5.isNull());

    QVector2D v6(QPointF(1, 2.5));
    QCOMPARE(v6.x(), (qreal)1.0f);
    QCOMPARE(v6.y(), (qreal)2.5f);
    QVERIFY(!v6.isNull());

    QVector2D v7(QVector3D(1.0f, 2.5f, 54.25f));
    QCOMPARE(v7.x(), (qreal)1.0f);
    QCOMPARE(v7.y(), (qreal)2.5f);
    QVERIFY(!v6.isNull());

    QVector2D v8(QVector4D(1.0f, 2.5f, 54.25f, 34.0f));
    QCOMPARE(v8.x(), (qreal)1.0f);
    QCOMPARE(v8.y(), (qreal)2.5f);
    QVERIFY(!v6.isNull());

    v1.setX(3.0f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)2.5f);
    QVERIFY(!v1.isNull());

    v1.setY(10.5f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)10.5f);
    QVERIFY(!v1.isNull());

    v1.setX(0.0f);
    v1.setY(0.0f);
    QCOMPARE(v1.x(), (qreal)0.0f);
    QCOMPARE(v1.y(), (qreal)0.0f);
    QVERIFY(v1.isNull());

    QPoint p1 = v8.toPoint();
    QCOMPARE(p1.x(), 1);
    QCOMPARE(p1.y(), 3);

    QPointF p2 = v8.toPointF();
    QCOMPARE((qreal)p2.x(), (qreal)1.0f);
    QCOMPARE((qreal)p2.y(), (qreal)2.5f);

    QVector3D v9 = v8.toVector3D();
    QCOMPARE(v9.x(), (qreal)1.0f);
    QCOMPARE(v9.y(), (qreal)2.5f);
    QCOMPARE(v9.z(), (qreal)0.0f);

    QVector4D v10 = v8.toVector4D();
    QCOMPARE(v10.x(), (qreal)1.0f);
    QCOMPARE(v10.y(), (qreal)2.5f);
    QCOMPARE(v10.z(), (qreal)0.0f);
    QCOMPARE(v10.w(), (qreal)0.0f);
}

// Test the creation of QVector3D objects in various ways:
// construct, copy, and modify.
void tst_QVector::create3()
{
    QVector3D null;
    QCOMPARE(null.x(), (qreal)0.0f);
    QCOMPARE(null.y(), (qreal)0.0f);
    QCOMPARE(null.z(), (qreal)0.0f);
    QVERIFY(null.isNull());

    QVector3D v1(1.0f, 2.5f, -89.25f);
    QCOMPARE(v1.x(), (qreal)1.0f);
    QCOMPARE(v1.y(), (qreal)2.5f);
    QCOMPARE(v1.z(), (qreal)-89.25f);
    QVERIFY(!v1.isNull());

    QVector3D v1i(1, 2, -89);
    QCOMPARE(v1i.x(), (qreal)1.0f);
    QCOMPARE(v1i.y(), (qreal)2.0f);
    QCOMPARE(v1i.z(), (qreal)-89.0f);
    QVERIFY(!v1i.isNull());

    QVector3D v2(v1);
    QCOMPARE(v2.x(), (qreal)1.0f);
    QCOMPARE(v2.y(), (qreal)2.5f);
    QCOMPARE(v2.z(), (qreal)-89.25f);
    QVERIFY(!v2.isNull());

    QVector3D v3(1.0f, 2.5f, 0.0f);
    QCOMPARE(v3.x(), (qreal)1.0f);
    QCOMPARE(v3.y(), (qreal)2.5f);
    QCOMPARE(v3.z(), (qreal)0.0f);
    QVERIFY(!v3.isNull());

    QVector3D v3i(1, 2, 0);
    QCOMPARE(v3i.x(), (qreal)1.0f);
    QCOMPARE(v3i.y(), (qreal)2.0f);
    QCOMPARE(v3i.z(), (qreal)0.0f);
    QVERIFY(!v3i.isNull());

    QVector3D v4;
    QCOMPARE(v4.x(), (qreal)0.0f);
    QCOMPARE(v4.y(), (qreal)0.0f);
    QCOMPARE(v4.z(), (qreal)0.0f);
    QVERIFY(v4.isNull());
    v4 = v1;
    QCOMPARE(v4.x(), (qreal)1.0f);
    QCOMPARE(v4.y(), (qreal)2.5f);
    QCOMPARE(v4.z(), (qreal)-89.25f);
    QVERIFY(!v4.isNull());

    QVector3D v5(QPoint(1, 2));
    QCOMPARE(v5.x(), (qreal)1.0f);
    QCOMPARE(v5.y(), (qreal)2.0f);
    QCOMPARE(v5.z(), (qreal)0.0f);
    QVERIFY(!v5.isNull());

    QVector3D v6(QPointF(1, 2.5));
    QCOMPARE(v6.x(), (qreal)1.0f);
    QCOMPARE(v6.y(), (qreal)2.5f);
    QCOMPARE(v6.z(), (qreal)0.0f);
    QVERIFY(!v6.isNull());

    QVector3D v7(QVector2D(1.0f, 2.5f));
    QCOMPARE(v7.x(), (qreal)1.0f);
    QCOMPARE(v7.y(), (qreal)2.5f);
    QCOMPARE(v7.z(), (qreal)0.0f);
    QVERIFY(!v7.isNull());

    QVector3D v8(QVector2D(1.0f, 2.5f), 54.25f);
    QCOMPARE(v8.x(), (qreal)1.0f);
    QCOMPARE(v8.y(), (qreal)2.5f);
    QCOMPARE(v8.z(), (qreal)54.25f);
    QVERIFY(!v8.isNull());

    QVector3D v9(QVector4D(1.0f, 2.5f, 54.25f, 34.0f));
    QCOMPARE(v9.x(), (qreal)1.0f);
    QCOMPARE(v9.y(), (qreal)2.5f);
    QCOMPARE(v9.z(), (qreal)54.25f);
    QVERIFY(!v9.isNull());

    v1.setX(3.0f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)2.5f);
    QCOMPARE(v1.z(), (qreal)-89.25f);
    QVERIFY(!v1.isNull());

    v1.setY(10.5f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)10.5f);
    QCOMPARE(v1.z(), (qreal)-89.25f);
    QVERIFY(!v1.isNull());

    v1.setZ(15.5f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)10.5f);
    QCOMPARE(v1.z(), (qreal)15.5f);
    QVERIFY(!v1.isNull());

    v1.setX(0.0f);
    v1.setY(0.0f);
    v1.setZ(0.0f);
    QCOMPARE(v1.x(), (qreal)0.0f);
    QCOMPARE(v1.y(), (qreal)0.0f);
    QCOMPARE(v1.z(), (qreal)0.0f);
    QVERIFY(v1.isNull());

    QPoint p1 = v8.toPoint();
    QCOMPARE(p1.x(), 1);
    QCOMPARE(p1.y(), 3);

    QPointF p2 = v8.toPointF();
    QCOMPARE((qreal)p2.x(), (qreal)1.0f);
    QCOMPARE((qreal)p2.y(), (qreal)2.5f);

    QVector2D v10 = v8.toVector2D();
    QCOMPARE(v10.x(), (qreal)1.0f);
    QCOMPARE(v10.y(), (qreal)2.5f);

    QVector4D v11 = v8.toVector4D();
    QCOMPARE(v11.x(), (qreal)1.0f);
    QCOMPARE(v11.y(), (qreal)2.5f);
    QCOMPARE(v11.z(), (qreal)54.25f);
    QCOMPARE(v11.w(), (qreal)0.0f);
}

// Test the creation of QVector4D objects in various ways:
// construct, copy, and modify.
void tst_QVector::create4()
{
    QVector4D null;
    QCOMPARE(null.x(), (qreal)0.0f);
    QCOMPARE(null.y(), (qreal)0.0f);
    QCOMPARE(null.z(), (qreal)0.0f);
    QCOMPARE(null.w(), (qreal)0.0f);
    QVERIFY(null.isNull());

    QVector4D v1(1.0f, 2.5f, -89.25f, 34.0f);
    QCOMPARE(v1.x(), (qreal)1.0f);
    QCOMPARE(v1.y(), (qreal)2.5f);
    QCOMPARE(v1.z(), (qreal)-89.25f);
    QCOMPARE(v1.w(), (qreal)34.0f);
    QVERIFY(!v1.isNull());

    QVector4D v1i(1, 2, -89, 34);
    QCOMPARE(v1i.x(), (qreal)1.0f);
    QCOMPARE(v1i.y(), (qreal)2.0f);
    QCOMPARE(v1i.z(), (qreal)-89.0f);
    QCOMPARE(v1i.w(), (qreal)34.0f);
    QVERIFY(!v1i.isNull());

    QVector4D v2(v1);
    QCOMPARE(v2.x(), (qreal)1.0f);
    QCOMPARE(v2.y(), (qreal)2.5f);
    QCOMPARE(v2.z(), (qreal)-89.25f);
    QCOMPARE(v2.w(), (qreal)34.0f);
    QVERIFY(!v2.isNull());

    QVector4D v3(1.0f, 2.5f, 0.0f, 0.0f);
    QCOMPARE(v3.x(), (qreal)1.0f);
    QCOMPARE(v3.y(), (qreal)2.5f);
    QCOMPARE(v3.z(), (qreal)0.0f);
    QCOMPARE(v3.w(), (qreal)0.0f);
    QVERIFY(!v3.isNull());

    QVector4D v3i(1, 2, 0, 0);
    QCOMPARE(v3i.x(), (qreal)1.0f);
    QCOMPARE(v3i.y(), (qreal)2.0f);
    QCOMPARE(v3i.z(), (qreal)0.0f);
    QCOMPARE(v3i.w(), (qreal)0.0f);
    QVERIFY(!v3i.isNull());

    QVector4D v3b(1.0f, 2.5f, -89.25f, 0.0f);
    QCOMPARE(v3b.x(), (qreal)1.0f);
    QCOMPARE(v3b.y(), (qreal)2.5f);
    QCOMPARE(v3b.z(), (qreal)-89.25f);
    QCOMPARE(v3b.w(), (qreal)0.0f);
    QVERIFY(!v3b.isNull());

    QVector4D v3bi(1, 2, -89, 0);
    QCOMPARE(v3bi.x(), (qreal)1.0f);
    QCOMPARE(v3bi.y(), (qreal)2.0f);
    QCOMPARE(v3bi.z(), (qreal)-89.0f);
    QCOMPARE(v3bi.w(), (qreal)0.0f);
    QVERIFY(!v3bi.isNull());

    QVector4D v4;
    QCOMPARE(v4.x(), (qreal)0.0f);
    QCOMPARE(v4.y(), (qreal)0.0f);
    QCOMPARE(v4.z(), (qreal)0.0f);
    QCOMPARE(v4.w(), (qreal)0.0f);
    QVERIFY(v4.isNull());
    v4 = v1;
    QCOMPARE(v4.x(), (qreal)1.0f);
    QCOMPARE(v4.y(), (qreal)2.5f);
    QCOMPARE(v4.z(), (qreal)-89.25f);
    QCOMPARE(v4.w(), (qreal)34.0f);
    QVERIFY(!v4.isNull());

    QVector4D v5(QPoint(1, 2));
    QCOMPARE(v5.x(), (qreal)1.0f);
    QCOMPARE(v5.y(), (qreal)2.0f);
    QCOMPARE(v5.z(), (qreal)0.0f);
    QCOMPARE(v5.w(), (qreal)0.0f);
    QVERIFY(!v5.isNull());

    QVector4D v6(QPointF(1, 2.5));
    QCOMPARE(v6.x(), (qreal)1.0f);
    QCOMPARE(v6.y(), (qreal)2.5f);
    QCOMPARE(v6.z(), (qreal)0.0f);
    QCOMPARE(v6.w(), (qreal)0.0f);
    QVERIFY(!v6.isNull());

    QVector4D v7(QVector2D(1.0f, 2.5f));
    QCOMPARE(v7.x(), (qreal)1.0f);
    QCOMPARE(v7.y(), (qreal)2.5f);
    QCOMPARE(v7.z(), (qreal)0.0f);
    QCOMPARE(v7.w(), (qreal)0.0f);
    QVERIFY(!v7.isNull());

    QVector4D v8(QVector3D(1.0f, 2.5f, -89.25f));
    QCOMPARE(v8.x(), (qreal)1.0f);
    QCOMPARE(v8.y(), (qreal)2.5f);
    QCOMPARE(v8.z(), (qreal)-89.25f);
    QCOMPARE(v8.w(), (qreal)0.0f);
    QVERIFY(!v8.isNull());

    QVector4D v9(QVector3D(1.0f, 2.5f, -89.25f), 34);
    QCOMPARE(v9.x(), (qreal)1.0f);
    QCOMPARE(v9.y(), (qreal)2.5f);
    QCOMPARE(v9.z(), (qreal)-89.25f);
    QCOMPARE(v9.w(), (qreal)34.0f);
    QVERIFY(!v9.isNull());

    QVector4D v10(QVector2D(1.0f, 2.5f), 23.5f, -8);
    QCOMPARE(v10.x(), (qreal)1.0f);
    QCOMPARE(v10.y(), (qreal)2.5f);
    QCOMPARE(v10.z(), (qreal)23.5f);
    QCOMPARE(v10.w(), (qreal)-8.0f);
    QVERIFY(!v10.isNull());

    v1.setX(3.0f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)2.5f);
    QCOMPARE(v1.z(), (qreal)-89.25f);
    QCOMPARE(v1.w(), (qreal)34.0f);
    QVERIFY(!v1.isNull());

    v1.setY(10.5f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)10.5f);
    QCOMPARE(v1.z(), (qreal)-89.25f);
    QCOMPARE(v1.w(), (qreal)34.0f);
    QVERIFY(!v1.isNull());

    v1.setZ(15.5f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)10.5f);
    QCOMPARE(v1.z(), (qreal)15.5f);
    QCOMPARE(v1.w(), (qreal)34.0f);
    QVERIFY(!v1.isNull());

    v1.setW(6.0f);
    QCOMPARE(v1.x(), (qreal)3.0f);
    QCOMPARE(v1.y(), (qreal)10.5f);
    QCOMPARE(v1.z(), (qreal)15.5f);
    QCOMPARE(v1.w(), (qreal)6.0f);
    QVERIFY(!v1.isNull());

    v1.setX(0.0f);
    v1.setY(0.0f);
    v1.setZ(0.0f);
    v1.setW(0.0f);
    QCOMPARE(v1.x(), (qreal)0.0f);
    QCOMPARE(v1.y(), (qreal)0.0f);
    QCOMPARE(v1.z(), (qreal)0.0f);
    QCOMPARE(v1.w(), (qreal)0.0f);
    QVERIFY(v1.isNull());

    QPoint p1 = v8.toPoint();
    QCOMPARE(p1.x(), 1);
    QCOMPARE(p1.y(), 3);

    QPointF p2 = v8.toPointF();
    QCOMPARE((qreal)p2.x(), (qreal)1.0f);
    QCOMPARE((qreal)p2.y(), (qreal)2.5f);

    QVector2D v11 = v8.toVector2D();
    QCOMPARE(v11.x(), (qreal)1.0f);
    QCOMPARE(v11.y(), (qreal)2.5f);

    QVector3D v12 = v8.toVector3D();
    QCOMPARE(v12.x(), (qreal)1.0f);
    QCOMPARE(v12.y(), (qreal)2.5f);
    QCOMPARE(v12.z(), (qreal)-89.25f);

    QVector2D v13 = v9.toVector2DAffine();
    QVERIFY(fuzzyCompare(v13.x(), (qreal)(1.0f / 34.0f)));
    QVERIFY(fuzzyCompare(v13.y(), (qreal)(2.5f / 34.0f)));

    QVector4D zerow(1.0f, 2.0f, 3.0f, 0.0f);
    v13 = zerow.toVector2DAffine();
    QVERIFY(v13.isNull());

    QVector3D v14 = v9.toVector3DAffine();
    QVERIFY(fuzzyCompare(v14.x(), (qreal)(1.0f / 34.0f)));
    QVERIFY(fuzzyCompare(v14.y(), (qreal)(2.5f / 34.0f)));
    QVERIFY(fuzzyCompare(v14.z(), (qreal)(-89.25f / 34.0f)));

    v14 = zerow.toVector3DAffine();
    QVERIFY(v14.isNull());
}

// Test vector length computation for 2D vectors.
void tst_QVector::length2_data()
{
    QTest::addColumn<qreal>("x");
    QTest::addColumn<qreal>("y");
    QTest::addColumn<qreal>("len");

    QTest::newRow("null") << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;
    QTest::newRow("1x") << (qreal)1.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("1y") << (qreal)0.0f << (qreal)1.0f << (qreal)1.0f;
    QTest::newRow("-1x") << (qreal)-1.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("-1y") << (qreal)0.0f << (qreal)-1.0f << (qreal)1.0f;
    QTest::newRow("two") << (qreal)2.0f << (qreal)-2.0f << (qreal)qSqrt(8.0f);
}
void tst_QVector::length2()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, len);

    QVector2D v(x, y);
    QCOMPARE((float)(v.length()), (float)len);
    QCOMPARE((float)(v.lengthSquared()), (float)(x * x + y * y));
}

// Test vector length computation for 3D vectors.
void tst_QVector::length3_data()
{
    QTest::addColumn<qreal>("x");
    QTest::addColumn<qreal>("y");
    QTest::addColumn<qreal>("z");
    QTest::addColumn<qreal>("len");

    QTest::newRow("null") << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;
    QTest::newRow("1x") << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("1y") << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("1z") << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f << (qreal)1.0f;
    QTest::newRow("-1x") << (qreal)-1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("-1y") << (qreal)0.0f << (qreal)-1.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("-1z") << (qreal)0.0f << (qreal)0.0f << (qreal)-1.0f << (qreal)1.0f;
    QTest::newRow("two") << (qreal)2.0f << (qreal)-2.0f << (qreal)2.0f << (qreal)qSqrt(12.0f);
}
void tst_QVector::length3()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, z);
    QFETCH(qreal, len);

    QVector3D v(x, y, z);
    QCOMPARE((float)(v.length()), (float)len);
    QCOMPARE((float)(v.lengthSquared()), (float)(x * x + y * y + z * z));
}

// Test vector length computation for 4D vectors.
void tst_QVector::length4_data()
{
    QTest::addColumn<qreal>("x");
    QTest::addColumn<qreal>("y");
    QTest::addColumn<qreal>("z");
    QTest::addColumn<qreal>("w");
    QTest::addColumn<qreal>("len");

    QTest::newRow("null") << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;
    QTest::newRow("1x") << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("1y") << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("1z") << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("1w") << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f << (qreal)1.0f;
    QTest::newRow("-1x") << (qreal)-1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("-1y") << (qreal)0.0f << (qreal)-1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("-1z") << (qreal)0.0f << (qreal)0.0f << (qreal)-1.0f << (qreal)0.0f << (qreal)1.0f;
    QTest::newRow("-1w") << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)-1.0f << (qreal)1.0f;
    QTest::newRow("two") << (qreal)2.0f << (qreal)-2.0f << (qreal)2.0f << (qreal)2.0f << (qreal)qSqrt(16.0f);
}
void tst_QVector::length4()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, z);
    QFETCH(qreal, w);
    QFETCH(qreal, len);

    QVector4D v(x, y, z, w);
    QCOMPARE((float)(v.length()), (float)len);
    QCOMPARE((float)(v.lengthSquared()), (float)(x * x + y * y + z * z + w * w));
}

// Test the unit vector conversion for 2D vectors.
void tst_QVector::normalized2_data()
{
    // Use the same test data as the length test.
    length2_data();
}
void tst_QVector::normalized2()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, len);

    QVector2D v(x, y);
    QVector2D u = v.normalized();
    if (v.isNull())
        QVERIFY(u.isNull());
    else
        QCOMPARE((float)(u.length()), (float)1.0f);
    QCOMPARE((float)(u.x() * len), (float)(v.x()));
    QCOMPARE((float)(u.y() * len), (float)(v.y()));
}

// Test the unit vector conversion for 3D vectors.
void tst_QVector::normalized3_data()
{
    // Use the same test data as the length test.
    length3_data();
}
void tst_QVector::normalized3()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, z);
    QFETCH(qreal, len);

    QVector3D v(x, y, z);
    QVector3D u = v.normalized();
    if (v.isNull())
        QVERIFY(u.isNull());
    else
        QCOMPARE((float)(u.length()), (float)1.0f);
    QCOMPARE((float)(u.x() * len), (float)(v.x()));
    QCOMPARE((float)(u.y() * len), (float)(v.y()));
    QCOMPARE((float)(u.z() * len), (float)(v.z()));
}

// Test the unit vector conversion for 4D vectors.
void tst_QVector::normalized4_data()
{
    // Use the same test data as the length test.
    length4_data();
}
void tst_QVector::normalized4()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, z);
    QFETCH(qreal, w);
    QFETCH(qreal, len);

    QVector4D v(x, y, z, w);
    QVector4D u = v.normalized();
    if (v.isNull())
        QVERIFY(u.isNull());
    else
        QCOMPARE((float)(u.length()), (float)1.0f);
    QCOMPARE((float)(u.x() * len), (float)(v.x()));
    QCOMPARE((float)(u.y() * len), (float)(v.y()));
    QCOMPARE((float)(u.z() * len), (float)(v.z()));
    QCOMPARE((float)(u.w() * len), (float)(v.w()));
}

// Test the unit vector conversion for 2D vectors.
void tst_QVector::normalize2_data()
{
    // Use the same test data as the length test.
    length2_data();
}
void tst_QVector::normalize2()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);

    QVector2D v(x, y);
    bool isNull = v.isNull();
    v.normalize();
    if (isNull)
        QVERIFY(v.isNull());
    else
        QCOMPARE((float)(v.length()), (float)1.0f);
}

// Test the unit vector conversion for 3D vectors.
void tst_QVector::normalize3_data()
{
    // Use the same test data as the length test.
    length3_data();
}
void tst_QVector::normalize3()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, z);

    QVector3D v(x, y, z);
    bool isNull = v.isNull();
    v.normalize();
    if (isNull)
        QVERIFY(v.isNull());
    else
        QCOMPARE((float)(v.length()), (float)1.0f);
}

// Test the unit vector conversion for 4D vectors.
void tst_QVector::normalize4_data()
{
    // Use the same test data as the length test.
    length4_data();
}
void tst_QVector::normalize4()
{
    QFETCH(qreal, x);
    QFETCH(qreal, y);
    QFETCH(qreal, z);
    QFETCH(qreal, w);

    QVector4D v(x, y, z, w);
    bool isNull = v.isNull();
    v.normalize();
    if (isNull)
        QVERIFY(v.isNull());
    else
        QCOMPARE((float)(v.length()), (float)1.0f);
}

// Test the comparison operators for 2D vectors.
void tst_QVector::compare2()
{
    QVector2D v1(1, 2);
    QVector2D v2(1, 2);
    QVector2D v3(3, 2);
    QVector2D v4(1, 3);

    QVERIFY(v1 == v2);
    QVERIFY(v1 != v3);
    QVERIFY(v1 != v4);
}

// Test the comparison operators for 3D vectors.
void tst_QVector::compare3()
{
    QVector3D v1(1, 2, 4);
    QVector3D v2(1, 2, 4);
    QVector3D v3(3, 2, 4);
    QVector3D v4(1, 3, 4);
    QVector3D v5(1, 2, 3);

    QVERIFY(v1 == v2);
    QVERIFY(v1 != v3);
    QVERIFY(v1 != v4);
    QVERIFY(v1 != v5);
}

// Test the comparison operators for 4D vectors.
void tst_QVector::compare4()
{
    QVector4D v1(1, 2, 4, 8);
    QVector4D v2(1, 2, 4, 8);
    QVector4D v3(3, 2, 4, 8);
    QVector4D v4(1, 3, 4, 8);
    QVector4D v5(1, 2, 3, 8);
    QVector4D v6(1, 2, 4, 3);

    QVERIFY(v1 == v2);
    QVERIFY(v1 != v3);
    QVERIFY(v1 != v4);
    QVERIFY(v1 != v5);
    QVERIFY(v1 != v6);
}

// Test vector addition for 2D vectors.
void tst_QVector::add2_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f
        << (qreal)3.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)2.0f
        << (qreal)0.0f << (qreal)3.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f
        << (qreal)4.0f << (qreal)5.0f
        << (qreal)5.0f << (qreal)7.0f;
}
void tst_QVector::add2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);

    QVector2D v1(x1, y1);
    QVector2D v2(x2, y2);
    QVector2D v3(x3, y3);

    QVERIFY((v1 + v2) == v3);

    QVector2D v4(v1);
    v4 += v2;
    QVERIFY(v4 == v3);

    QCOMPARE(v4.x(), v1.x() + v2.x());
    QCOMPARE(v4.y(), v1.y() + v2.y());
}

// Test vector addition for 3D vectors.
void tst_QVector::add3_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)3.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)3.0f << (qreal)0.0f;

    QTest::newRow("zonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)3.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f << (qreal)3.0f
        << (qreal)4.0f << (qreal)5.0f << (qreal)-6.0f
        << (qreal)5.0f << (qreal)7.0f << (qreal)-3.0f;
}
void tst_QVector::add3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);

    QVERIFY((v1 + v2) == v3);

    QVector3D v4(v1);
    v4 += v2;
    QVERIFY(v4 == v3);

    QCOMPARE(v4.x(), v1.x() + v2.x());
    QCOMPARE(v4.y(), v1.y() + v2.y());
    QCOMPARE(v4.z(), v1.z() + v2.z());
}

// Test vector addition for 4D vectors.
void tst_QVector::add4_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("w1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("w2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");
    QTest::addColumn<qreal>("w3");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)3.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)3.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("zonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)3.0f << (qreal)0.0f;

    QTest::newRow("wonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)3.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f << (qreal)3.0f << (qreal)8.0f
        << (qreal)4.0f << (qreal)5.0f << (qreal)-6.0f << (qreal)9.0f
        << (qreal)5.0f << (qreal)7.0f << (qreal)-3.0f << (qreal)17.0f;
}
void tst_QVector::add4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, w2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);
    QFETCH(qreal, w3);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(x2, y2, z2, w2);
    QVector4D v3(x3, y3, z3, w3);

    QVERIFY((v1 + v2) == v3);

    QVector4D v4(v1);
    v4 += v2;
    QVERIFY(v4 == v3);

    QCOMPARE(v4.x(), v1.x() + v2.x());
    QCOMPARE(v4.y(), v1.y() + v2.y());
    QCOMPARE(v4.z(), v1.z() + v2.z());
    QCOMPARE(v4.w(), v1.w() + v2.w());
}

// Test vector subtraction for 2D vectors.
void tst_QVector::subtract2_data()
{
    // Use the same test data as the add test.
    add2_data();
}
void tst_QVector::subtract2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);

    QVector2D v1(x1, y1);
    QVector2D v2(x2, y2);
    QVector2D v3(x3, y3);

    QVERIFY((v3 - v1) == v2);
    QVERIFY((v3 - v2) == v1);

    QVector2D v4(v3);
    v4 -= v1;
    QVERIFY(v4 == v2);

    QCOMPARE(v4.x(), v3.x() - v1.x());
    QCOMPARE(v4.y(), v3.y() - v1.y());

    QVector2D v5(v3);
    v5 -= v2;
    QVERIFY(v5 == v1);

    QCOMPARE(v5.x(), v3.x() - v2.x());
    QCOMPARE(v5.y(), v3.y() - v2.y());
}

// Test vector subtraction for 3D vectors.
void tst_QVector::subtract3_data()
{
    // Use the same test data as the add test.
    add3_data();
}
void tst_QVector::subtract3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);

    QVERIFY((v3 - v1) == v2);
    QVERIFY((v3 - v2) == v1);

    QVector3D v4(v3);
    v4 -= v1;
    QVERIFY(v4 == v2);

    QCOMPARE(v4.x(), v3.x() - v1.x());
    QCOMPARE(v4.y(), v3.y() - v1.y());
    QCOMPARE(v4.z(), v3.z() - v1.z());

    QVector3D v5(v3);
    v5 -= v2;
    QVERIFY(v5 == v1);

    QCOMPARE(v5.x(), v3.x() - v2.x());
    QCOMPARE(v5.y(), v3.y() - v2.y());
    QCOMPARE(v5.z(), v3.z() - v2.z());
}

// Test vector subtraction for 4D vectors.
void tst_QVector::subtract4_data()
{
    // Use the same test data as the add test.
    add4_data();
}
void tst_QVector::subtract4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, w2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);
    QFETCH(qreal, w3);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(x2, y2, z2, w2);
    QVector4D v3(x3, y3, z3, w3);

    QVERIFY((v3 - v1) == v2);
    QVERIFY((v3 - v2) == v1);

    QVector4D v4(v3);
    v4 -= v1;
    QVERIFY(v4 == v2);

    QCOMPARE(v4.x(), v3.x() - v1.x());
    QCOMPARE(v4.y(), v3.y() - v1.y());
    QCOMPARE(v4.z(), v3.z() - v1.z());
    QCOMPARE(v4.w(), v3.w() - v1.w());

    QVector4D v5(v3);
    v5 -= v2;
    QVERIFY(v5 == v1);

    QCOMPARE(v5.x(), v3.x() - v2.x());
    QCOMPARE(v5.y(), v3.y() - v2.y());
    QCOMPARE(v5.z(), v3.z() - v2.z());
    QCOMPARE(v5.w(), v3.w() - v2.w());
}

// Test component-wise vector multiplication for 2D vectors.
void tst_QVector::multiply2_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)2.0f
        << (qreal)0.0f << (qreal)2.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f
        << (qreal)4.0f << (qreal)5.0f
        << (qreal)4.0f << (qreal)10.0f;
}
void tst_QVector::multiply2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);

    QVector2D v1(x1, y1);
    QVector2D v2(x2, y2);
    QVector2D v3(x3, y3);

    QVERIFY((v1 * v2) == v3);

    QVector2D v4(v1);
    v4 *= v2;
    QVERIFY(v4 == v3);

    QCOMPARE(v4.x(), v1.x() * v2.x());
    QCOMPARE(v4.y(), v1.y() * v2.y());
}

// Test component-wise vector multiplication for 3D vectors.
void tst_QVector::multiply3_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f;

    QTest::newRow("zonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f << (qreal)3.0f
        << (qreal)4.0f << (qreal)5.0f << (qreal)-6.0f
        << (qreal)4.0f << (qreal)10.0f << (qreal)-18.0f;
}
void tst_QVector::multiply3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);

    QVERIFY((v1 * v2) == v3);

    QVector3D v4(v1);
    v4 *= v2;
    QVERIFY(v4 == v3);

    QCOMPARE(v4.x(), v1.x() * v2.x());
    QCOMPARE(v4.y(), v1.y() * v2.y());
    QCOMPARE(v4.z(), v1.z() * v2.z());
}

// Test component-wise vector multiplication for 4D vectors.
void tst_QVector::multiply4_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("w1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("w2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");
    QTest::addColumn<qreal>("w3");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("zonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f;

    QTest::newRow("wonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f << (qreal)3.0f << (qreal)8.0f
        << (qreal)4.0f << (qreal)5.0f << (qreal)-6.0f << (qreal)9.0f
        << (qreal)4.0f << (qreal)10.0f << (qreal)-18.0f << (qreal)72.0f;
}
void tst_QVector::multiply4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, w2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);
    QFETCH(qreal, w3);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(x2, y2, z2, w2);
    QVector4D v3(x3, y3, z3, w3);

    QVERIFY((v1 * v2) == v3);

    QVector4D v4(v1);
    v4 *= v2;
    QVERIFY(v4 == v3);

    QCOMPARE(v4.x(), v1.x() * v2.x());
    QCOMPARE(v4.y(), v1.y() * v2.y());
    QCOMPARE(v4.z(), v1.z() * v2.z());
    QCOMPARE(v4.w(), v1.w() * v2.w());
}

// Test vector multiplication by a factor for 2D vectors.
void tst_QVector::multiplyFactor2_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("factor");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)100.0f
        << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f
        << (qreal)2.0f
        << (qreal)2.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f
        << (qreal)2.0f
        << (qreal)0.0f << (qreal)2.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f
        << (qreal)2.0f
        << (qreal)2.0f << (qreal)4.0f;

    QTest::newRow("allzero")
        << (qreal)1.0f << (qreal)2.0f
        << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f;
}
void tst_QVector::multiplyFactor2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, factor);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);

    QVector2D v1(x1, y1);
    QVector2D v2(x2, y2);

    QVERIFY((v1 * factor) == v2);
    QVERIFY((factor * v1) == v2);

    QVector2D v3(v1);
    v3 *= factor;
    QVERIFY(v3 == v2);

    QCOMPARE(v3.x(), v1.x() * factor);
    QCOMPARE(v3.y(), v1.y() * factor);
}

// Test vector multiplication by a factor for 3D vectors.
void tst_QVector::multiplyFactor3_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("factor");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)100.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)2.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f;

    QTest::newRow("zonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f << (qreal)-3.0f
        << (qreal)2.0f
        << (qreal)2.0f << (qreal)4.0f << (qreal)-6.0f;

    QTest::newRow("allzero")
        << (qreal)1.0f << (qreal)2.0f << (qreal)-3.0f
        << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;
}
void tst_QVector::multiplyFactor3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, factor);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);

    QVERIFY((v1 * factor) == v2);
    QVERIFY((factor * v1) == v2);

    QVector3D v3(v1);
    v3 *= factor;
    QVERIFY(v3 == v2);

    QCOMPARE(v3.x(), v1.x() * factor);
    QCOMPARE(v3.y(), v1.y() * factor);
    QCOMPARE(v3.z(), v1.z() * factor);
}

// Test vector multiplication by a factor for 4D vectors.
void tst_QVector::multiplyFactor4_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("w1");
    QTest::addColumn<qreal>("factor");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("w2");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)100.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("xonly")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f
        << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("yonly")
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)2.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f << (qreal)0.0f;

    QTest::newRow("zonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f;

    QTest::newRow("wonly")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)2.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f;

    QTest::newRow("all")
        << (qreal)1.0f << (qreal)2.0f << (qreal)-3.0f << (qreal)4.0f
        << (qreal)2.0f
        << (qreal)2.0f << (qreal)4.0f << (qreal)-6.0f << (qreal)8.0f;

    QTest::newRow("allzero")
        << (qreal)1.0f << (qreal)2.0f << (qreal)-3.0f << (qreal)4.0f
        << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f;
}
void tst_QVector::multiplyFactor4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);
    QFETCH(qreal, factor);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, w2);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(x2, y2, z2, w2);

    QVERIFY((v1 * factor) == v2);
    QVERIFY((factor * v1) == v2);

    QVector4D v3(v1);
    v3 *= factor;
    QVERIFY(v3 == v2);

    QCOMPARE(v3.x(), v1.x() * factor);
    QCOMPARE(v3.y(), v1.y() * factor);
    QCOMPARE(v3.z(), v1.z() * factor);
    QCOMPARE(v3.w(), v1.w() * factor);
}

// Test vector division by a factor for 2D vectors.
void tst_QVector::divide2_data()
{
    // Use the same test data as the multiply test.
    multiplyFactor2_data();
}
void tst_QVector::divide2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, factor);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);

    QVector2D v1(x1, y1);
    QVector2D v2(x2, y2);

    if (factor == (qreal)0.0f)
        return;

    QVERIFY((v2 / factor) == v1);

    QVector2D v3(v2);
    v3 /= factor;
    QVERIFY(v3 == v1);

    QCOMPARE(v3.x(), v2.x() / factor);
    QCOMPARE(v3.y(), v2.y() / factor);
}

// Test vector division by a factor for 3D vectors.
void tst_QVector::divide3_data()
{
    // Use the same test data as the multiply test.
    multiplyFactor3_data();
}
void tst_QVector::divide3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, factor);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);

    if (factor == (qreal)0.0f)
        return;

    QVERIFY((v2 / factor) == v1);

    QVector3D v3(v2);
    v3 /= factor;
    QVERIFY(v3 == v1);

    QCOMPARE(v3.x(), v2.x() / factor);
    QCOMPARE(v3.y(), v2.y() / factor);
    QCOMPARE(v3.z(), v2.z() / factor);
}

// Test vector division by a factor for 4D vectors.
void tst_QVector::divide4_data()
{
    // Use the same test data as the multiply test.
    multiplyFactor4_data();
}
void tst_QVector::divide4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);
    QFETCH(qreal, factor);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, w2);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(x2, y2, z2, w2);

    if (factor == (qreal)0.0f)
        return;

    QVERIFY((v2 / factor) == v1);

    QVector4D v3(v2);
    v3 /= factor;
    QVERIFY(v3 == v1);

    QCOMPARE(v3.x(), v2.x() / factor);
    QCOMPARE(v3.y(), v2.y() / factor);
    QCOMPARE(v3.z(), v2.z() / factor);
    QCOMPARE(v3.w(), v2.w() / factor);
}

// Test vector negation for 2D vectors.
void tst_QVector::negate2_data()
{
    // Use the same test data as the add test.
    add2_data();
}
void tst_QVector::negate2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);

    QVector2D v1(x1, y1);
    QVector2D v2(-x1, -y1);

    QVERIFY(-v1 == v2);
}

// Test vector negation for 3D vectors.
void tst_QVector::negate3_data()
{
    // Use the same test data as the add test.
    add3_data();
}
void tst_QVector::negate3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(-x1, -y1, -z1);

    QVERIFY(-v1 == v2);
}

// Test vector negation for 4D vectors.
void tst_QVector::negate4_data()
{
    // Use the same test data as the add test.
    add4_data();
}
void tst_QVector::negate4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(-x1, -y1, -z1, -w1);

    QVERIFY(-v1 == v2);
}

// Test the computation of vector cross-products.
void tst_QVector::crossProduct_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("x3");
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");
    QTest::addColumn<qreal>("dot");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f;

    QTest::newRow("unitvec")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f;

    QTest::newRow("complex")
        << (qreal)1.0f << (qreal)2.0f << (qreal)3.0f
        << (qreal)4.0f << (qreal)5.0f << (qreal)6.0f
        << (qreal)-3.0f << (qreal)6.0f << (qreal)-3.0f
        << (qreal)32.0f;
}
void tst_QVector::crossProduct()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);

    QVector3D v4 = QVector3D::crossProduct(v1, v2);
    QVERIFY(v4 == v3);

    // Compute the cross-product long-hand and check again.
    qreal xres = y1 * z2 - z1 * y2;
    qreal yres = z1 * x2 - x1 * z2;
    qreal zres = x1 * y2 - y1 * x2;

    QCOMPARE(v4.x(), xres);
    QCOMPARE(v4.y(), yres);
    QCOMPARE(v4.z(), zres);
}

// Test the computation of normals.
void tst_QVector::normal_data()
{
    // Use the same test data as the crossProduct test.
    crossProduct_data();
}
void tst_QVector::normal()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);

    QVERIFY(QVector3D::normal(v1, v2) == v3.normalized());
    QVERIFY(QVector3D::normal(QVector3D(), v1, v2) == v3.normalized());

    QVector3D point(1.0f, 2.0f, 3.0f);
    QVERIFY(QVector3D::normal(point, v1 + point, v2 + point) == v3.normalized());
}

// Test distance to plane calculations.
void tst_QVector::distanceToPlane_data()
{
    QTest::addColumn<qreal>("x1");  // Point on plane
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("x2");  // Normal to plane
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("x3");  // Point to test for distance
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");
    QTest::addColumn<qreal>("x4");  // Second point on plane
    QTest::addColumn<qreal>("y4");
    QTest::addColumn<qreal>("z4");
    QTest::addColumn<qreal>("x5");  // Third point on plane
    QTest::addColumn<qreal>("y5");
    QTest::addColumn<qreal>("z5");
    QTest::addColumn<qreal>("distance");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)0.0f;

    QTest::newRow("above")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)2.0f
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)2.0f;

    QTest::newRow("below")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)-1.0f << (qreal)1.0f << (qreal)-2.0f
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)2.0f << (qreal)0.0f
        << (qreal)-2.0f;
}
void tst_QVector::distanceToPlane()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);
    QFETCH(qreal, x4);
    QFETCH(qreal, y4);
    QFETCH(qreal, z4);
    QFETCH(qreal, x5);
    QFETCH(qreal, y5);
    QFETCH(qreal, z5);
    QFETCH(qreal, distance);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);
    QVector3D v4(x4, y4, z4);
    QVector3D v5(x5, y5, z5);

    QCOMPARE(v3.distanceToPlane(v1, v2), distance);
    QCOMPARE(v3.distanceToPlane(v1, v4, v5), distance);
}

// Test distance to line calculations.
void tst_QVector::distanceToLine_data()
{
    QTest::addColumn<qreal>("x1");  // Point on line
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("x2");  // Direction of the line
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("x3");  // Point to test for distance
    QTest::addColumn<qreal>("y3");
    QTest::addColumn<qreal>("z3");
    QTest::addColumn<qreal>("distance");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f;

    QTest::newRow("on line")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)5.0f
        << (qreal)0.0f;

    QTest::newRow("off line")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)1.0f;

    QTest::newRow("off line 2")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f << (qreal)-2.0f << (qreal)0.0f
        << (qreal)2.0f;

    QTest::newRow("points")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)5.0f << (qreal)0.0f
        << (qreal)5.0f;
}
void tst_QVector::distanceToLine()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);
    QFETCH(qreal, distance);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);
    QVector3D v3(x3, y3, z3);

    QCOMPARE(v3.distanceToLine(v1, v2), distance);
}

// Test the computation of dot products for 2D vectors.
void tst_QVector::dotProduct2_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("dot");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f;

    QTest::newRow("unitvec")
        << (qreal)1.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)1.0f
        << (qreal)0.0f;

    QTest::newRow("complex")
        << (qreal)1.0f << (qreal)2.0f
        << (qreal)4.0f << (qreal)5.0f
        << (qreal)14.0f;
}
void tst_QVector::dotProduct2()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, dot);

    QVector2D v1(x1, y1);
    QVector2D v2(x2, y2);

    QVERIFY(QVector2D::dotProduct(v1, v2) == dot);

    // Compute the dot-product long-hand and check again.
    qreal d = x1 * x2 + y1 * y2;

    QCOMPARE(QVector2D::dotProduct(v1, v2), d);
}

// Test the computation of dot products for 3D vectors.
void tst_QVector::dotProduct3_data()
{
    // Use the same test data as the crossProduct test.
    crossProduct_data();
}
void tst_QVector::dotProduct3()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, x3);
    QFETCH(qreal, y3);
    QFETCH(qreal, z3);
    QFETCH(qreal, dot);

    Q_UNUSED(x3);
    Q_UNUSED(y3);
    Q_UNUSED(z3);

    QVector3D v1(x1, y1, z1);
    QVector3D v2(x2, y2, z2);

    QVERIFY(QVector3D::dotProduct(v1, v2) == dot);

    // Compute the dot-product long-hand and check again.
    qreal d = x1 * x2 + y1 * y2 + z1 * z2;

    QCOMPARE(QVector3D::dotProduct(v1, v2), d);
}

// Test the computation of dot products for 4D vectors.
void tst_QVector::dotProduct4_data()
{
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("z1");
    QTest::addColumn<qreal>("w1");
    QTest::addColumn<qreal>("x2");
    QTest::addColumn<qreal>("y2");
    QTest::addColumn<qreal>("z2");
    QTest::addColumn<qreal>("w2");
    QTest::addColumn<qreal>("dot");

    QTest::newRow("null")
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f;

    QTest::newRow("unitvec")
        << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f << (qreal)1.0f << (qreal)0.0f << (qreal)0.0f
        << (qreal)0.0f;

    QTest::newRow("complex")
        << (qreal)1.0f << (qreal)2.0f << (qreal)3.0f << (qreal)4.0f
        << (qreal)4.0f << (qreal)5.0f << (qreal)6.0f << (qreal)7.0f
        << (qreal)60.0f;
}
void tst_QVector::dotProduct4()
{
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, z1);
    QFETCH(qreal, w1);
    QFETCH(qreal, x2);
    QFETCH(qreal, y2);
    QFETCH(qreal, z2);
    QFETCH(qreal, w2);
    QFETCH(qreal, dot);

    QVector4D v1(x1, y1, z1, w1);
    QVector4D v2(x2, y2, z2, w2);

    QVERIFY(QVector4D::dotProduct(v1, v2) == dot);

    // Compute the dot-product long-hand and check again.
    qreal d = x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;

    QCOMPARE(QVector4D::dotProduct(v1, v2), d);
}

QTEST_APPLESS_MAIN(tst_QVector)

#include "tst_qvectornd.moc"