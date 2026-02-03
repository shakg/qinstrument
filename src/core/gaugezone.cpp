#include "GaugeQt/gaugezone.h"
#include "../util/gaugemath.h"
#include <QPainterPath>

GaugeZone::GaugeZone(qreal start, qreal end, const QColor &color)
    : m_start(start)
    , m_end(end)
    , m_color(color)
    , m_opacity(0.3)
{
}

qreal GaugeZone::start() const
{
    return m_start;
}

void GaugeZone::setStart(qreal value)
{
    m_start = value;
}

qreal GaugeZone::end() const
{
    return m_end;
}

void GaugeZone::setEnd(qreal value)
{
    m_end = value;
}

QColor GaugeZone::color() const
{
    return m_color;
}

void GaugeZone::setColor(const QColor &color)
{
    m_color = color;
}

qreal GaugeZone::opacity() const
{
    return m_opacity;
}

void GaugeZone::setOpacity(qreal opacity)
{
    m_opacity = opacity;
}

GaugeZone* GaugeZone::createNormalZone(qreal start, qreal end)
{
    return new GaugeZone(start, end, QColor(0, 200, 0));
}

GaugeZone* GaugeZone::createWarningZone(qreal start, qreal end)
{
    return new GaugeZone(start, end, QColor(255, 200, 0));
}

GaugeZone* GaugeZone::createDangerZone(qreal start, qreal end)
{
    return new GaugeZone(start, end, QColor(255, 0, 0));
}

void GaugeZone::paintRadial(QPainter &painter, const QPointF &center, qreal innerRadius, qreal outerRadius,
                           qreal startAngle, qreal spanAngle, qreal minValue, qreal maxValue)
{
    if (m_end <= minValue || m_start >= maxValue)
        return;

    painter.save();

    qreal clampedStart = qMax(m_start, minValue);
    qreal clampedEnd = qMin(m_end, maxValue);

    qreal startRatio = (clampedStart - minValue) / (maxValue - minValue);
    qreal endRatio = (clampedEnd - minValue) / (maxValue - minValue);

    qreal zoneStartAngle = startAngle + startRatio * spanAngle;
    qreal zoneSpanAngle = (endRatio - startRatio) * spanAngle;

    QColor zoneColor = m_color;
    zoneColor.setAlphaF(m_opacity);

    QPainterPath path;
    QRectF outerRect(center.x() - outerRadius, center.y() - outerRadius,
                     outerRadius * 2, outerRadius * 2);
    QRectF innerRect(center.x() - innerRadius, center.y() - innerRadius,
                     innerRadius * 2, innerRadius * 2);

    path.arcMoveTo(outerRect, -zoneStartAngle);
    path.arcTo(outerRect, -zoneStartAngle, -zoneSpanAngle);

    QPointF outerEnd = path.currentPosition();
    path.arcTo(innerRect, -(zoneStartAngle + zoneSpanAngle), zoneSpanAngle);
    path.closeSubpath();

    painter.fillPath(path, zoneColor);

    painter.restore();
}

void GaugeZone::paintLinear(QPainter &painter, const QRectF &rect, qreal minValue, qreal maxValue)
{
    if (m_end <= minValue || m_start >= maxValue)
        return;

    painter.save();

    qreal clampedStart = qMax(m_start, minValue);
    qreal clampedEnd = qMin(m_end, maxValue);

    qreal startRatio = (clampedStart - minValue) / (maxValue - minValue);
    qreal endRatio = (clampedEnd - minValue) / (maxValue - minValue);

    qreal x = rect.left() + startRatio * rect.width();
    qreal width = (endRatio - startRatio) * rect.width();

    QColor zoneColor = m_color;
    zoneColor.setAlphaF(m_opacity);

    painter.fillRect(QRectF(x, rect.top(), width, rect.height()), zoneColor);

    painter.restore();
}
