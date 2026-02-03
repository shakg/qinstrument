#ifndef GAUGENEEDLE_H
#define GAUGENEEDLE_H

#include "gaugeqt_global.h"
#include <QColor>
#include <QPainter>

class GAUGEQT_EXPORT GaugeNeedle
{
public:
    enum Style {
        Arrow,
        Triangle,
        Line,
        Indicator
    };

    GaugeNeedle();

    Style style() const;
    void setStyle(Style style);

    QColor color() const;
    void setColor(const QColor &color);

    qreal width() const;
    void setWidth(qreal width);

    bool hasShadow() const;
    void setShadow(bool enabled);

    void paint(QPainter &painter, const QPointF &center, qreal angle, qreal length);

private:
    Style m_style;
    QColor m_color;
    qreal m_width;
    bool m_shadow;
};

#endif // GAUGENEEDLE_H
