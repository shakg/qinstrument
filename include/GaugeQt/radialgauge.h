#ifndef RADIALGAUGE_H
#define RADIALGAUGE_H

#include "gaugeqt_global.h"
#include "gaugewidget.h"

class GAUGEQT_EXPORT RadialGauge : public GaugeWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal spanAngle READ spanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)

public:
    explicit RadialGauge(QWidget *parent = nullptr);

    qreal startAngle() const;
    void setStartAngle(qreal angle);

    qreal spanAngle() const;
    void setSpanAngle(qreal angle);

signals:
    void startAngleChanged(qreal angle);
    void spanAngleChanged(qreal angle);

protected:
    void paintGauge(QPainter &painter) override;
    QSize sizeHint() const override;

private:
    qreal m_startAngle;
    qreal m_spanAngle;
};

#endif // RADIALGAUGE_H
