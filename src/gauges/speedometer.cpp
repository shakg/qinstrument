#include "GaugeQt/speedometer.h"
#include "GaugeQt/gaugeneedle.h"
#include "GaugeQt/gaugescale.h"
#include "GaugeQt/gaugezone.h"

Speedometer::Speedometer(QWidget *parent)
    : RadialGauge(parent)
{
    // Pre-configure as speedometer
    setRange(0, 240);
    setAnimated(true);
    setAnimationDuration(500);
    setEasingCurve(QEasingCurve::OutCubic);

    // Match dashboard dial: 7:30 to 4:30 sweep.
    setStartAngle(135);
    setSpanAngle(270);

    // Add typical speed zones
    addZone(GaugeZone::createNormalZone(0, 120));
    addZone(GaugeZone::createWarningZone(120, 180));
    addZone(GaugeZone::createDangerZone(180, 240));

    // Configure scale
    scale()->setMajorTicks(12);
    scale()->setMinorTicks(2);
    scale()->setLabelFormat("%.0f");

    // Configure needle
    needle()->setStyle(GaugeNeedle::Arrow);
    needle()->setColor(Qt::red);
    needle()->setWidth(4.0);
    needle()->setShadow(true);
}
