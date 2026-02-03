#ifndef GAUGEZONE_H
#define GAUGEZONE_H

#include "gaugeqt_global.h"
#include <QColor>
#include <QPainter>

class GAUGEQT_EXPORT GaugeZone
{
public:
    GaugeZone(qreal start, qreal end, const QColor &color);

    qreal start() const;
    void setStart(qreal value);

    qreal end() const;
    void setEnd(qreal value);

    QColor color() const;
    void setColor(const QColor &color);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    static GaugeZone* createNormalZone(qreal start, qreal end);
    static GaugeZone* createWarningZone(qreal start, qreal end);
    static GaugeZone* createDangerZone(qreal start, qreal end);

    void paintRadial(QPainter &painter, const QPointF &center, qreal innerRadius, qreal outerRadius,
                    qreal startAngle, qreal spanAngle, qreal minValue, qreal maxValue);

    void paintLinear(QPainter &painter, const QRectF &rect, qreal minValue, qreal maxValue);

private:
    qreal m_start;
    qreal m_end;
    QColor m_color;
    qreal m_opacity;
};

#endif // GAUGEZONE_H
