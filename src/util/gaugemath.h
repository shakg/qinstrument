#ifndef GAUGEMATH_H
#define GAUGEMATH_H

#include <QtMath>
#include <QPointF>

namespace GaugeMath {

inline qreal valueToAngle(qreal value, qreal minValue, qreal maxValue, qreal startAngle, qreal spanAngle)
{
    qreal ratio = (value - minValue) / (maxValue - minValue);
    return startAngle + ratio * spanAngle;
}

inline QPointF polarToCartesian(const QPointF &center, qreal angle, qreal radius)
{
    qreal radians = qDegreesToRadians(angle);
    return QPointF(
        center.x() + radius * qCos(radians),
        center.y() + radius * qSin(radians)
    );
}

inline qreal normalizeAngle(qreal angle)
{
    while (angle < 0) angle += 360;
    while (angle >= 360) angle -= 360;
    return angle;
}

} // namespace GaugeMath

#endif // GAUGEMATH_H
