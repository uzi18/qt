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

#ifndef QFONTENGINE_S60_P_H
#define QFONTENGINE_S60_P_H

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

#include "qconfig.h"
#include "qfontengine_p.h"
#include "qsize.h"
#include <OPENFONT.H>

class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CFont;

QT_BEGIN_NAMESPACE

// ..gives us access to truetype tables, UTF-16<->GlyphID mapping, and glyph outlines
class QFontEngineS60Extensions
{
public:
    QFontEngineS60Extensions(COpenFont *font);

    QByteArray getSfntTable(uint tag) const;
    const unsigned char *cmap() const;
    QPainterPath glyphOutline(glyph_t glyph) const;

private:
    COpenFont *m_font;
    const MOpenFontShapingExtension *m_shapingExtension;
    mutable MOpenFontTrueTypeExtension *m_trueTypeExtension;
    mutable const unsigned char *m_cmap;
    mutable bool m_symbolCMap;
    mutable QByteArray m_cmapTable;
};

class QFontEngineS60 : public QFontEngine
{
public:
    QFontEngineS60(const QFontDef &fontDef, const QFontEngineS60Extensions *extensions);
    ~QFontEngineS60();

    bool stringToCMap(const QChar *str, int len, QGlyphLayout *glyphs, int *nglyphs, QTextEngine::ShaperFlags flags) const;
    void recalcAdvances(QGlyphLayout *glyphs, QTextEngine::ShaperFlags flags) const;

    QImage alphaMapForGlyph(glyph_t glyph);

    glyph_metrics_t boundingBox(const QGlyphLayout &glyphs);
    glyph_metrics_t boundingBox_const(glyph_t glyph) const; // Const correctnes quirk.
    glyph_metrics_t boundingBox(glyph_t glyph);

    QFixed ascent() const;
    QFixed descent() const;
    QFixed leading() const;
    qreal maxCharWidth() const;
    qreal minLeftBearing() const { return 0; }
    qreal minRightBearing() const { return 0; }

    QByteArray getSfntTable(uint tag) const;

    static qreal pixelsToPoints(qreal pixels, Qt::Orientation orientation = Qt::Horizontal);
    static qreal pointsToPixels(qreal points, Qt::Orientation orientation = Qt::Horizontal);

    const char *name() const;

    bool canRender(const QChar *string, int len);

    Type type() const;

private:
    friend class QFontPrivate;

    QFixed glyphAdvance(HB_Glyph glyph) const;
    void getCharacterData(glyph_t glyph, TOpenFontCharMetrics& metrics, const TUint8*& bitmap, TSize& bitmapSize) const;

    CFbsBitmap *m_textRenderBitmap;
    CFbsBitmapDevice *m_textRenderBitmapDevice;
    CFbsBitGc *m_textRenderBitmapGc;
    CFont* m_font;
    const QFontEngineS60Extensions *m_extensions;
    qreal m_fontSizeInPixels;
};

class QFontEngineMultiS60 : public QFontEngineMulti
{
public:
    QFontEngineMultiS60(QFontEngine *first, int script, const QStringList &fallbackFamilies);
    void loadEngine(int at);

    int m_script;
    QStringList m_fallbackFamilies;
};

QT_END_NAMESPACE

#endif // QFONTENGINE_S60_P_H