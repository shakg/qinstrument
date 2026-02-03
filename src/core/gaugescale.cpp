#include "GaugeQt/gaugescale.h"
#include "../util/gaugemath.h"
#include <QFontMetricsF>
#include <QPen>

GaugeScale::GaugeScale()
    : m_majorTicks(10)
    , m_minorTicks(5)
    , m_tickColor(Qt::white)
    , m_labelColor(Qt::white)
    , m_labelFont("Arial", 10)
    , m_showLabels(true)
    , m_labelFormat("%.0f")
{
}

int GaugeScale::majorTicks() const
{
    return m_majorTicks;
}

void GaugeScale::setMajorTicks(int count)
{
    m_majorTicks = count;
}

int GaugeScale::minorTicks() const
{
    return m_minorTicks;
}

void GaugeScale::setMinorTicks(int count)
{
    m_minorTicks = count;
}

QColor GaugeScale::tickColor() const
{
    return m_tickColor;
}

void GaugeScale::setTickColor(const QColor &color)
{
    m_tickColor = color;
}

QColor GaugeScale::labelColor() const
{
    return m_labelColor;
}

void GaugeScale::setLabelColor(const QColor &color)
{
    m_labelColor = color;
}

QFont GaugeScale::labelFont() const
{
    return m_labelFont;
}

void GaugeScale::setLabelFont(const QFont &font)
{
    m_labelFont = font;
}

bool GaugeScale::showLabels() const
{
    return m_showLabels;
}

void GaugeScale::setShowLabels(bool show)
{
    m_showLabels = show;
}

QString GaugeScale::labelFormat() const
{
    return m_labelFormat;
}

void GaugeScale::setLabelFormat(const QString &format)
{
    m_labelFormat = format;
}

void GaugeScale::paintRadial(QPainter &painter, const QPointF &center, qreal radius,
                            qreal startAngle, qreal spanAngle, qreal minValue, qreal maxValue)
{
    painter.save();

    QPen pen(m_tickColor);
    painter.setPen(pen);

    int totalMinorTicks = m_majorTicks * m_minorTicks;

    // Draw minor ticks
    for (int i = 0; i <= totalMinorTicks; ++i) {
        qreal ratio = static_cast<qreal>(i) / totalMinorTicks;
        qreal angle = startAngle + ratio * spanAngle;

        bool isMajor = (i % m_minorTicks == 0);
        qreal tickLength = isMajor ? 15.0 : 8.0;
        qreal tickWidth = isMajor ? 2.0 : 1.0;

        pen.setWidthF(tickWidth);
        painter.setPen(pen);

        QPointF outer = GaugeMath::polarToCartesian(center, angle, radius);
        QPointF inner = GaugeMath::polarToCartesian(center, angle, radius - tickLength);

        painter.drawLine(outer, inner);
    }

    // Draw labels
    if (m_showLabels) {
        painter.setFont(m_labelFont);
        painter.setPen(m_labelColor);

        for (int i = 0; i <= m_majorTicks; ++i) {
            qreal ratio = static_cast<qreal>(i) / m_majorTicks;
            qreal angle = startAngle + ratio * spanAngle;
            qreal value = minValue + ratio * (maxValue - minValue);

            QString label = QString::asprintf(m_labelFormat.toUtf8().constData(), value);

            QPointF labelPos = GaugeMath::polarToCartesian(center, angle, radius - 18);
            QPointF devicePos = painter.transform().map(labelPos);

            painter.save();
            painter.resetTransform();
            painter.setFont(m_labelFont);
            painter.setPen(m_labelColor);

            QFontMetricsF fm(m_labelFont);
            QSizeF textSize = fm.size(Qt::TextSingleLine, label);
            QRectF labelRect(devicePos.x() - textSize.width() / 2.0,
                             devicePos.y() - textSize.height() / 2.0,
                             textSize.width(),
                             textSize.height());

            painter.drawText(labelRect, Qt::AlignCenter, label);
            painter.restore();
        }
    }

    painter.restore();
}

void GaugeScale::paintLinear(QPainter &painter, const QRectF &rect, qreal minValue, qreal maxValue)
{
    painter.save();

    QPen pen(m_tickColor);
    painter.setPen(pen);

    int totalMinorTicks = m_majorTicks * m_minorTicks;
    qreal width = rect.width();

    // Draw ticks
    for (int i = 0; i <= totalMinorTicks; ++i) {
        qreal ratio = static_cast<qreal>(i) / totalMinorTicks;
        qreal x = rect.left() + ratio * width;

        bool isMajor = (i % m_minorTicks == 0);
        qreal tickLength = isMajor ? 15.0 : 8.0;
        qreal tickWidth = isMajor ? 2.0 : 1.0;

        pen.setWidthF(tickWidth);
        painter.setPen(pen);

        painter.drawLine(QPointF(x, rect.bottom()),
                        QPointF(x, rect.bottom() - tickLength));
    }

    // Draw labels
    if (m_showLabels) {
        painter.setFont(m_labelFont);
        painter.setPen(m_labelColor);

        for (int i = 0; i <= m_majorTicks; ++i) {
            qreal ratio = static_cast<qreal>(i) / m_majorTicks;
            qreal x = rect.left() + ratio * width;
            qreal value = minValue + ratio * (maxValue - minValue);

            QString label = QString::asprintf(m_labelFormat.toUtf8().constData(), value);
            QRectF labelRect(x - 30, rect.bottom() - 35, 60, 20);

            painter.drawText(labelRect, Qt::AlignCenter, label);
        }
    }

    painter.restore();
}
