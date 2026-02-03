#include "GaugeQt/gaugebackground.h"
#include <QRadialGradient>
#include <QLinearGradient>

GaugeBackground::GaugeBackground()
    : m_outerColor(QColor(40, 40, 40))
    , m_innerColor(QColor(20, 20, 20))
    , m_useGradient(true)
{
}

QColor GaugeBackground::outerColor() const
{
    return m_outerColor;
}

void GaugeBackground::setOuterColor(const QColor &color)
{
    m_outerColor = color;
}

QColor GaugeBackground::innerColor() const
{
    return m_innerColor;
}

void GaugeBackground::setInnerColor(const QColor &color)
{
    m_innerColor = color;
}

bool GaugeBackground::useGradient() const
{
    return m_useGradient;
}

void GaugeBackground::setUseGradient(bool enabled)
{
    m_useGradient = enabled;
}

void GaugeBackground::paintCircular(QPainter &painter, const QRectF &rect)
{
    painter.save();

    if (m_useGradient) {
        QRadialGradient gradient(rect.center(), rect.width() / 2.0);
        gradient.setColorAt(0, m_innerColor);
        gradient.setColorAt(1, m_outerColor);
        painter.setBrush(gradient);
    } else {
        painter.setBrush(m_outerColor);
    }

    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect);

    painter.restore();
}

void GaugeBackground::paintRectangular(QPainter &painter, const QRectF &rect)
{
    painter.save();

    if (m_useGradient) {
        QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
        gradient.setColorAt(0, m_innerColor);
        gradient.setColorAt(1, m_outerColor);
        painter.setBrush(gradient);
    } else {
        painter.setBrush(m_outerColor);
    }

    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 10, 10);

    painter.restore();
}
