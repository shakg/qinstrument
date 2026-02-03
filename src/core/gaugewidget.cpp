#include "GaugeQt/gaugewidget.h"
#include "GaugeQt/gaugeneedle.h"
#include "GaugeQt/gaugescale.h"
#include "GaugeQt/gaugezone.h"
#include "GaugeQt/gaugebackground.h"
#include <QPainter>

GaugeWidget::GaugeWidget(QWidget *parent)
    : QWidget(parent)
    , m_value(0)
    , m_displayValue(0)
    , m_minValue(0)
    , m_maxValue(100)
    , m_animated(true)
    , m_animationDuration(500)
    , m_easingCurve(QEasingCurve::OutCubic)
{
    m_needle = new GaugeNeedle();
    m_scale = new GaugeScale();
    m_background = new GaugeBackground();

    m_animation = new QPropertyAnimation(this, "displayValue", this);
    m_animation->setDuration(m_animationDuration);
    m_animation->setEasingCurve(m_easingCurve);
}

GaugeWidget::~GaugeWidget()
{
    delete m_needle;
    delete m_scale;
    delete m_background;
    qDeleteAll(m_zones);
}

qreal GaugeWidget::value() const
{
    return m_value;
}

qreal GaugeWidget::displayValue() const
{
    return m_displayValue;
}

qreal GaugeWidget::minValue() const
{
    return m_minValue;
}

qreal GaugeWidget::maxValue() const
{
    return m_maxValue;
}

bool GaugeWidget::isAnimated() const
{
    return m_animated;
}

int GaugeWidget::animationDuration() const
{
    return m_animationDuration;
}

QEasingCurve::Type GaugeWidget::easingCurve() const
{
    return m_easingCurve;
}

void GaugeWidget::setValue(qreal value)
{
    value = qBound(m_minValue, value, m_maxValue);
    if (qFuzzyCompare(m_value, value))
        return;

    m_value = value;
    emit valueChanged(m_value);

    if (m_animated) {
        m_animation->stop();
        m_animation->setStartValue(m_displayValue);
        m_animation->setEndValue(m_value);
        m_animation->start();
    } else {
        setDisplayValue(m_value);
    }
}

void GaugeWidget::setDisplayValue(qreal value)
{
    if (qFuzzyCompare(m_displayValue, value))
        return;

    m_displayValue = value;
    emit displayValueChanged(m_displayValue);
    update();
}

void GaugeWidget::setMinValue(qreal min)
{
    if (qFuzzyCompare(m_minValue, min))
        return;

    m_minValue = min;
    emit minValueChanged(m_minValue);
    update();
}

void GaugeWidget::setMaxValue(qreal max)
{
    if (qFuzzyCompare(m_maxValue, max))
        return;

    m_maxValue = max;
    emit maxValueChanged(m_maxValue);
    update();
}

void GaugeWidget::setAnimated(bool animated)
{
    if (m_animated == animated)
        return;

    m_animated = animated;
    emit animatedChanged(m_animated);
}

void GaugeWidget::setAnimationDuration(int duration)
{
    if (m_animationDuration == duration)
        return;

    m_animationDuration = duration;
    m_animation->setDuration(duration);
    emit animationDurationChanged(m_animationDuration);
}

void GaugeWidget::setEasingCurve(QEasingCurve::Type curve)
{
    m_easingCurve = curve;
    m_animation->setEasingCurve(curve);
}

void GaugeWidget::setRange(qreal min, qreal max)
{
    setMinValue(min);
    setMaxValue(max);
}

void GaugeWidget::addZone(GaugeZone *zone)
{
    m_zones.append(zone);
    update();
}

void GaugeWidget::clearZones()
{
    qDeleteAll(m_zones);
    m_zones.clear();
    update();
}

GaugeNeedle* GaugeWidget::needle() const
{
    return m_needle;
}

GaugeScale* GaugeWidget::scale() const
{
    return m_scale;
}

GaugeBackground* GaugeWidget::background() const
{
    return m_background;
}

void GaugeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    paintGauge(painter);
}

QColor GaugeWidget::needleColorForValue(qreal value) const
{
    bool inRedZone = false;
    for (const GaugeZone *zone : m_zones) {
        qreal zoneStart = zone->start();
        qreal zoneEnd = zone->end();
        if (!((value >= zoneStart && value <= zoneEnd) ||
              (value >= zoneEnd && value <= zoneStart)))
            continue;

        if (zone->color() == Qt::red) {
            inRedZone = true;
            break;
        }
    }

    if (inRedZone)
        return Qt::red;

    return m_needle->color();
}
