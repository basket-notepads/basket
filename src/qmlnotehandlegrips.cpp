#include "qmlnotehandlegrips.h"
#include "qmlutils.h"
#include "qmlnotesmodel.h"
#include <QPainter>

void NoteHandleGrips::paint(QPainter *painter)
{
    QColor foreground = Utils().highlightColor();
    int height = painter->viewport().height();

    // Draw the grips:
        int xGrips             = 4;
        int marginedHeight = (height * 80 / 100); // 10% empty on top, and 10% empty on bottom, so 20% of the height should be empty of any grip, and 80% should be in the grips
        int nbGrips            = (marginedHeight - 3) / 6;
        if (nbGrips < 2)
            nbGrips = 2;
        int yGrips             = (height + 1 - nbGrips * 6 - 3) / 2; // +1 to avoid rounding errors, -nbGrips*6-3 the size of the grips
        QColor darker  = foreground.dark(130);
        QColor lighter = foreground.light(130);
        for (int i = 0; i < nbGrips; ++i) {
            /// Dark color:
            painter->setPen(darker);
            // Top-left point:
            painter->drawPoint(xGrips,     yGrips);
            painter->drawPoint(xGrips + 1, yGrips);
            painter->drawPoint(xGrips,     yGrips + 1);
            // Bottom-right point:
            painter->drawPoint(xGrips + 4, yGrips + 3);
            painter->drawPoint(xGrips + 5, yGrips + 3);
            painter->drawPoint(xGrips + 4, yGrips + 4);
            /// Light color:
            painter->setPen(lighter);
            // Top-left point:
            painter->drawPoint(xGrips + 1, yGrips + 1);
            // Bottom-right point:
            painter->drawPoint(xGrips + 5, yGrips + 4);
            yGrips += 6;
        }
        // The remaining point:
        painter->setPen(darker);
        painter->drawPoint(xGrips,     yGrips);
        painter->drawPoint(xGrips + 1, yGrips);
        painter->drawPoint(xGrips,     yGrips + 1);
        painter->setPen(lighter);
        painter->drawPoint(xGrips + 1, yGrips + 1);
}

QColor mixColor(const QColor &color1, const QColor &color2)
{
    QColor mixedColor;
    mixedColor.setRgb((color1.red()   + color2.red())   / 2,
                      (color1.green() + color2.green()) / 2,
                      (color1.blue()  + color2.blue())  / 2);
    return mixedColor;
}

void drawGradient(QPainter *p, const QColor &colorTop, const QColor & colorBottom,
                  int x, int y, int w, int h,
                  bool sunken, bool horz, bool flat)   /*const*/
{
    QColor highlight(colorBottom);
    QColor subh1(colorTop);
    QColor subh2(colorTop);

    QColor topgrad(colorTop);
    QColor botgrad(colorBottom);


    if (flat && !sunken)
        p->fillRect(x, y, w, h, colorTop);
    else {
        int i  = 0;
        int x1 = x;
        int y1 = y;
        int x2 = x + w - 1;
        int y2 = y + h - 1;
        if (horz)
            x2 = x2;
        else
            y2 = y2;

#define DRAWLINE if (horz) \
        p->drawLine( x1, y1+i, x2, y1+i ); \
    else \
        p->drawLine( x1+i, y1, x1+i, y2 ); \
    i++;

        // Gradient:
        int ng = (horz ? h : w); // how many lines for the gradient?

        int h1, h2, s1, s2, v1, v2;
        if (!sunken) {
            topgrad.getHsv(&h1, &s1, &v1);
            botgrad.getHsv(&h2, &s2, &v2);
        } else {
            botgrad.getHsv(&h1, &s1, &v1);
            topgrad.getHsv(&h2, &s2, &v2);
        }

        if (ng > 1) {
            for (int j = 0; j < ng; j++) {
                p->setPen(QColor::fromHsv(h1 + ((h2 - h1)*j) / (ng - 1),
                                          s1 + ((s2 - s1)*j) / (ng - 1),
                                          v1 + ((v2 - v1)*j) / (ng - 1)));
                DRAWLINE;
            }
        } else if (ng == 1) {
            p->setPen(QColor::fromHsv((h1 + h2) / 2, (s1 + s2) / 2, (v1 + v2) / 2));
            DRAWLINE;
        }
    }
}

inline void drawLineByRect(QPainter &painter, int x, int y, int width, int height)
{
    painter.drawLine(x, y, x + width - 1, y + height - 1);
}

void NoteInserter::paint(QPainter *painter)
{
    bool m_inserterGroup = false;
    bool m_inserterTop = false;
    bool m_inserterSplit = true;

    QRect rect = painter->viewport(); //m_inserterRect; // For shorter code-lines when drawing!
//        rect.translate(-xPainter, -yPainter);
        int lineY  = (m_inserterGroup && m_inserterTop ? 0 : 2);
        int roundY = (m_inserterGroup && m_inserterTop ? 0 : 1);

//        KStatefulBrush statefulBrush(KColorScheme::View, KColorScheme::HoverColor);
        QColor dark = QColor(Qt::red); //statefulBrush.brush(palette()).color();
        QColor light = QColor(Qt::green); //dark.lighter().lighter();
//        if (m_inserterGroup && Settings::groupOnInsertionLine())
//            light = Tools::mixColor(light, palette().color(QPalette::Highlight));
        painter->setPen(dark);
        // The horizontal line:
        //painter->drawRect(       rect.x(),                    rect.y() + lineY,  rect.width(), 2);
        int width = rect.width() - 4;
        drawGradient(painter, dark,  light, rect.x() + 2,           rect.y() + lineY, width / 2,         2, /*sunken=*/false, /*horz=*/false, /*flat=*/false);
        drawGradient(painter, light, dark,  rect.x() + 2 + width / 2, rect.y() + lineY, width - width / 2, 2, /*sunken=*/false, /*horz=*/false, /*flat=*/false);
        // The left-most and right-most edges (biggest vertical lines):
        drawLineByRect(*painter, rect.x(),                    rect.y(),          1, (m_inserterGroup ? 4 : 6));
        drawLineByRect(*painter, rect.x() + rect.width() - 1, rect.y(),          1, (m_inserterGroup ? 4 : 6));
        // The left and right mid vertical lines:
        drawLineByRect(*painter, rect.x() + 1,                rect.y() + roundY, 1, (m_inserterGroup ? 3 : 4));
        drawLineByRect(*painter, rect.x() + rect.width() - 2, rect.y() + roundY, 1, (m_inserterGroup ? 3 : 4));
        // Draw the split as a feedback to know where is the limit between insert and group:
        if (m_inserterSplit) {
            int noteWidth = rect.width() + (m_inserterGroup ? qmlbnp::NoteProperties::HANDLE_WIDTH : 0);
            int xSplit = rect.x() - (m_inserterGroup ? qmlbnp::NoteProperties::HANDLE_WIDTH : 0) + noteWidth / 2;
            painter->setPen(mixColor(dark, light));
            painter->drawRect(xSplit - 2, rect.y() + lineY, 4, 2);
            painter->setPen(dark);
            painter->drawRect(xSplit - 1, rect.y() + lineY, 2, 2);
        }
}
