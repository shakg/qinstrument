#ifndef GAUGEBACKGROUND_H
#define GAUGEBACKGROUND_H

#include "gaugeqt_global.h"
#include <QColor>
#include <QPainter>

class GAUGEQT_EXPORT GaugeBackground
{
public:
    GaugeBackground();

    QColor outerColor() const;
    void setOuterColor(const QColor &color);

    QColor innerColor() const;
    void setInnerColor(const QColor &color);

    bool useGradient() const;
    void setUseGradient(bool enabled);

    void paintCircular(QPainter &painter, const QRectF &rect);
    void paintRectangular(QPainter &painter, const QRectF &rect);

private:
    QColor m_outerColor;
    QColor m_innerColor;
    bool m_useGradient;
};

#endif // GAUGEBACKGROUND_H
