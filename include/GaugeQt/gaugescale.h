#ifndef GAUGESCALE_H
#define GAUGESCALE_H

#include "gaugeqt_global.h"
#include <QColor>
#include <QPainter>
#include <QFont>

class GAUGEQT_EXPORT GaugeScale
{
public:
    GaugeScale();

    int majorTicks() const;
    void setMajorTicks(int count);

    int minorTicks() const;
    void setMinorTicks(int count);

    QColor tickColor() const;
    void setTickColor(const QColor &color);

    QColor labelColor() const;
    void setLabelColor(const QColor &color);

    QFont labelFont() const;
    void setLabelFont(const QFont &font);

    bool showLabels() const;
    void setShowLabels(bool show);

    QString labelFormat() const;
    void setLabelFormat(const QString &format);

    void paintRadial(QPainter &painter, const QPointF &center, qreal radius,
                    qreal startAngle, qreal spanAngle, qreal minValue, qreal maxValue);

    void paintLinear(QPainter &painter, const QRectF &rect, qreal minValue, qreal maxValue);

private:
    int m_majorTicks;
    int m_minorTicks;
    QColor m_tickColor;
    QColor m_labelColor;
    QFont m_labelFont;
    bool m_showLabels;
    QString m_labelFormat;
};

#endif // GAUGESCALE_H
