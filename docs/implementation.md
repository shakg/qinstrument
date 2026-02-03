# Implementation Details

This library provides reusable Qt widgets for displaying gauge-style values (radial). It is designed to be embedded into other Qt applications as a UI component library.

## Architecture Overview

- GaugeWidget is the abstract base class for all gauges. It owns common state (value range, animation, needle, scale, background, zones) and defines the paint pipeline.
- Derived gauge (RadialGauge) implements the paintGauge() method to render a specific geometry.
- Subcomponents are small, focused classes:
  - GaugeNeedle: draws the pointer indicator and its cap.
  - GaugeScale: draws major/minor ticks and labels.
  - GaugeBackground: draws background shapes and borders.
  - GaugeZone: represents a value range with color and opacity (normal/warning/danger helpers included).

## Paint Pipeline

Paint happens in two layers:

1) QWidget::paintEvent() in GaugeWidget configures a QPainter with antialiasing and calls paintGauge().
2) Each concrete gauge draws:
   - background
   - zones
   - scale
   - needle (using the current display value)

All geometry is derived from the widget size and mapped into an internal coordinate space for consistent rendering.

## Value, Range, and Animation

- The public value is clamped to [minValue, maxValue].
- When animated, value changes are interpolated using a QPropertyAnimation on displayValue.
- displayValue is used for rendering, so the needle and scale move smoothly.
- Animation settings (duration, easing) are owned by GaugeWidget and affect all derived gauges uniformly.

## Zones and Redline Behavior

- Zones are user-configured ranges with color and opacity.
- Normal, warning, and danger zones can be created with helper factories on GaugeZone.
- The needle color is computed per paint based on the current value. If the value falls inside a red zone, the needle is painted red (redline behavior). Otherwise the configured needle color is used.
- This behavior is centralized in GaugeWidget so all radial gauges respond consistently.

## Extending the Library

To add a new gauge type:

1) Subclass GaugeWidget.
2) Implement paintGauge(QPainter &painter) and render background, zones, scale, and needle in the desired order.
3) Use GaugeMath helpers (if needed) for angle/value conversions.
4) Respect minValue/maxValue and use displayValue when rendering animated transitions.

## Integration Notes for Qt Apps

- All gauges are QWidget-based and can be placed in Qt Designer or created in code.
- Use the provided include headers under include/GaugeQt/ when linking against the library.
- The library is CMake-based; link against GaugeQt and include its headers in your application.
- Gauge customization is done through the GaugeWidget API (range, animation, zones) and subcomponent accessors (needle(), scale(), background()).

## Example: Dashboard Speedometer

This is adapted from `examples/dashboard/main.cpp` to show a typical usage pattern in a Qt app:

```cpp
// Single gauge: Speedometer
speedometer = new Speedometer(this);
speedometer->setMinimumSize(420, 420);
speedometer->scale()->setMajorTicks(2);
speedometer->scale()->setMinorTicks(1);
speedometer->scale()->setShowLabels(true);
speedometer->scale()->setLabelFormat("%.0f");
speedometer->scale()->setLabelColor(DashboardPalette::slate());
speedometer->scale()->setTickColor(Qt::transparent);
speedometer->needle()->setColor(QColor(236, 240, 245));
speedometer->background()->setInnerColor(DashboardPalette::night());
speedometer->background()->setOuterColor(DashboardPalette::deepNavy());
setRedlinePercent(75.0);

// Speed control
QSlider *speedSlider = new QSlider(Qt::Horizontal);
speedSlider->setRange(0, 240);
speedSlider->setValue(0);
connect(speedSlider, &QSlider::valueChanged, speedometer, &Speedometer::setValue);

// Redline zones
void applyRedlineZones()
{
    speedometer->clearZones();
    GaugeZone *normal = GaugeZone::createNormalZone(0, redlineStart);
    normal->setColor(DashboardPalette::slate());
    normal->setOpacity(0.45);
    speedometer->addZone(normal);

    GaugeZone *redline = GaugeZone::createDangerZone(redlineStart, 240);
    redline->setColor(QColor(217, 30, 54));
    redline->setOpacity(0.6);
    speedometer->addZone(redline);
}
```

## Threading and Updates

- All updates should happen on the GUI thread, as with standard Qt widgets.
- Calling setValue() triggers repaint and optional animation; no manual update() is required.
