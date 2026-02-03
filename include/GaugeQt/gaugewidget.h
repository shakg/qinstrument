#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include "gaugeqt_global.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QEasingCurve>

class GaugeNeedle;
class GaugeScale;
class GaugeZone;
class GaugeBackground;
class QColor;

class GAUGEQT_EXPORT GaugeWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(qreal displayValue READ displayValue WRITE setDisplayValue NOTIFY displayValueChanged)
    Q_PROPERTY(qreal minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(qreal maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated NOTIFY animatedChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)

public:
    explicit GaugeWidget(QWidget *parent = nullptr);
    ~GaugeWidget() override;

    qreal value() const;
    qreal displayValue() const;
    qreal minValue() const;
    qreal maxValue() const;
    bool isAnimated() const;
    int animationDuration() const;
    QEasingCurve::Type easingCurve() const;

    void setRange(qreal min, qreal max);
    void addZone(GaugeZone *zone);
    void clearZones();

    GaugeNeedle* needle() const;
    GaugeScale* scale() const;
    GaugeBackground* background() const;

public slots:
    void setValue(qreal value);
    void setDisplayValue(qreal value);
    void setMinValue(qreal min);
    void setMaxValue(qreal max);
    void setAnimated(bool animated);
    void setAnimationDuration(int duration);
    void setEasingCurve(QEasingCurve::Type curve);

signals:
    void valueChanged(qreal value);
    void displayValueChanged(qreal value);
    void minValueChanged(qreal min);
    void maxValueChanged(qreal max);
    void animatedChanged(bool animated);
    void animationDurationChanged(int duration);

protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void paintGauge(QPainter &painter) = 0;
    QColor needleColorForValue(qreal value) const;

    qreal m_value;
    qreal m_displayValue;
    qreal m_minValue;
    qreal m_maxValue;
    bool m_animated;
    int m_animationDuration;
    QEasingCurve::Type m_easingCurve;

    GaugeNeedle *m_needle;
    GaugeScale *m_scale;
    GaugeBackground *m_background;
    QList<GaugeZone*> m_zones;

    QPropertyAnimation *m_animation;
};

#endif // GAUGEWIDGET_H
