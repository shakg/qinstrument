#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "gaugeqt_global.h"
#include "radialgauge.h"

class GAUGEQT_EXPORT Speedometer : public RadialGauge
{
    Q_OBJECT

public:
    explicit Speedometer(QWidget *parent = nullptr);
};

#endif // SPEEDOMETER_H
