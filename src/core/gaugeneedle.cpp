#include "GaugeQt/gaugeneedle.h"
#include <QPainterPath>
#include <QtMath>

GaugeNeedle::GaugeNeedle()
    : m_style(Arrow)
    , m_color(Qt::red)
    , m_width(4.0)
    , m_shadow(true)
{
}

GaugeNeedle::Style GaugeNeedle::style() const
{
    return m_style;
}

void GaugeNeedle::setStyle(Style style)
{
    m_style = style;
}

QColor GaugeNeedle::color() const
{
    return m_color;
}

void GaugeNeedle::setColor(const QColor &color)
{
    m_color = color;
}

qreal GaugeNeedle::width() const
{
    return m_width;
}

void GaugeNeedle::setWidth(qreal width)
{
    m_width = width;
}

bool GaugeNeedle::hasShadow() const
{
    return m_shadow;
}

void GaugeNeedle::setShadow(bool enabled)
{
    m_shadow = enabled;
}

void GaugeNeedle::paint(QPainter &painter, const QPointF &center, qreal angle, qreal length)
{
    painter.save();
    painter.translate(center);
    painter.rotate(angle);

    QPainterPath path;

    switch (m_style) {
    case Arrow: {
        qreal halfWidth = m_width / 2.0;
        path.moveTo(0, -halfWidth);
        path.lineTo(length - 10, -halfWidth);
        path.lineTo(length, 0);
        path.lineTo(length - 10, halfWidth);
        path.lineTo(0, halfWidth);
        path.closeSubpath();
        break;
    }
    case Triangle: {
        qreal halfWidth = m_width;
        path.moveTo(0, -halfWidth);
        path.lineTo(length, 0);
        path.lineTo(0, halfWidth);
        path.closeSubpath();
        break;
    }
    case Line: {
        qreal halfWidth = m_width / 2.0;
        path.addRect(0, -halfWidth, length, m_width);
        break;
    }
    case Indicator: {
        qreal halfWidth = m_width / 2.0;
        path.moveTo(0, -halfWidth);
        path.lineTo(length * 0.8, -halfWidth);
        path.lineTo(length, 0);
        path.lineTo(length * 0.8, halfWidth);
        path.lineTo(0, halfWidth);
        path.closeSubpath();
        break;
    }
    }

    if (m_shadow) {
        painter.translate(2, 2);
        painter.fillPath(path, QColor(0, 0, 0, 80));
        painter.translate(-2, -2);
    }

    painter.fillPath(path, m_color);

    // Draw center cap
    painter.setBrush(m_color.darker(120));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(0, 0), m_width * 1.5, m_width * 1.5);

    painter.restore();
}
