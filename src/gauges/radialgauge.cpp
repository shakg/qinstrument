#include "GaugeQt/radialgauge.h"
#include "GaugeQt/gaugeneedle.h"
#include "GaugeQt/gaugescale.h"
#include "GaugeQt/gaugezone.h"
#include "GaugeQt/gaugebackground.h"
#include "../util/gaugemath.h"
#include <QPainter>

RadialGauge::RadialGauge(QWidget *parent)
    : GaugeWidget(parent)
    , m_startAngle(225)
    , m_spanAngle(270)
{
    setMinimumSize(200, 200);
}

qreal RadialGauge::startAngle() const
{
    return m_startAngle;
}

void RadialGauge::setStartAngle(qreal angle)
{
    if (qFuzzyCompare(m_startAngle, angle))
        return;

    m_startAngle = angle;
    emit startAngleChanged(m_startAngle);
    update();
}

qreal RadialGauge::spanAngle() const
{
    return m_spanAngle;
}

void RadialGauge::setSpanAngle(qreal angle)
{
    if (qFuzzyCompare(m_spanAngle, angle))
        return;

    m_spanAngle = angle;
    emit spanAngleChanged(m_spanAngle);
    update();
}

void RadialGauge::paintGauge(QPainter &painter)
{
    int side = qMin(width(), height());
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);

    QPointF center(0, 0);
    qreal radius = 45;
    QRectF gaugeRect(-radius, -radius, radius * 2, radius * 2);

    // Paint background
    m_background->paintCircular(painter, gaugeRect);

    // Paint zones
    for (GaugeZone *zone : m_zones) {
        zone->paintRadial(painter, center, radius - 20, radius - 5,
                         m_startAngle, m_spanAngle, m_minValue, m_maxValue);
    }

    // Paint scale
    m_scale->paintRadial(painter, center, radius, m_startAngle, m_spanAngle,
                        m_minValue, m_maxValue);

    // Paint needle
    qreal angle = GaugeMath::valueToAngle(m_displayValue, m_minValue, m_maxValue,
                                         m_startAngle, m_spanAngle);
    QColor needleColor = needleColorForValue(m_displayValue);
    QColor originalColor = m_needle->color();
    if (needleColor != originalColor)
        m_needle->setColor(needleColor);
    m_needle->paint(painter, center, angle, radius - 10);
    if (needleColor != originalColor)
        m_needle->setColor(originalColor);
}

QSize RadialGauge::sizeHint() const
{
    return QSize(300, 300);
}
