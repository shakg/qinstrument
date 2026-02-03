#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QEvent>
#include <QSpinBox>
#include <GaugeQt/GaugeQt>

class DashboardPalette
{
public:
    static QColor deepNavy() { return QColor("#06141B"); }
    static QColor night() { return QColor("#11212D"); }
    static QColor slate() { return QColor("#253745"); }
};

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    DashboardWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("GaugeQt Dashboard Demo");
        resize(700, 700);

        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setContentsMargins(16, 16, 16, 16);
        mainLayout->setSpacing(16);

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
        setLeadingRedlinePercent(0.0);
        mainLayout->addWidget(speedometer, 1);

        speedValueLabel = new QLabel(speedometer);
        speedValueLabel->setAlignment(Qt::AlignCenter);
        speedValueLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        speedValueLabel->setStyleSheet("color: #ECF0F5; font-size: 78px; font-weight: bold; font-family: Monospace;");
        speedValueLabel->setText(formatSpeedValue(0));
        speedometer->installEventFilter(this);

        speedLabel = new QLabel("Speed", speedometer);
        speedLabel->setAlignment(Qt::AlignCenter);
        speedLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        speedLabel->setStyleSheet("color: #9AA7B2; font-size: 24px; font-weight: 600; letter-spacing: 1px;");

        // Control panel
        QHBoxLayout *controlLayout = new QHBoxLayout();

        // Speed control
        QVBoxLayout *speedControl = new QVBoxLayout();
        speedControl->addWidget(new QLabel("Speed"));
        QSlider *speedSlider = new QSlider(Qt::Horizontal);
        speedSlider->setRange(0, 240);
        speedSlider->setValue(0);
        connect(speedSlider, &QSlider::valueChanged, speedometer, &Speedometer::setValue);
        connect(speedSlider, &QSlider::valueChanged, this, [this](int value) {
            speedValueLabel->setText(formatSpeedValue(value));
        });
        speedControl->addWidget(speedSlider);
        controlLayout->addLayout(speedControl);

        // Redline control
        QVBoxLayout *redlineControl = new QVBoxLayout();
        redlineControl->addWidget(new QLabel("Trailing Redline %"));
        QSpinBox *redlineSpin = new QSpinBox();
        redlineSpin->setRange(0, 100);
        redlineSpin->setValue(75);
        connect(redlineSpin, &QSpinBox::valueChanged, this, [this](int value) {
            setRedlinePercent(static_cast<qreal>(value));
        });
        redlineControl->addWidget(redlineSpin);
        controlLayout->addLayout(redlineControl);

        // Leading redline control
        QVBoxLayout *leadingRedlineControl = new QVBoxLayout();
        leadingRedlineControl->addWidget(new QLabel("Leading Redline %"));
        QSpinBox *leadingRedlineSpin = new QSpinBox();
        leadingRedlineSpin->setRange(0, 100);
        leadingRedlineSpin->setValue(0);
        connect(leadingRedlineSpin, &QSpinBox::valueChanged, this, [this](int value) {
            setLeadingRedlinePercent(static_cast<qreal>(value));
        });
        leadingRedlineControl->addWidget(leadingRedlineSpin);
        controlLayout->addLayout(leadingRedlineControl);

        mainLayout->addLayout(controlLayout);
        mainLayout->setStretch(0, 1);
        mainLayout->setStretch(1, 0);

    }

private:
    static QString formatSpeedValue(int value)
    {
        return QString("%1").arg(value, 6, 10, QChar('0'));
    }

    void updateSpeedLabelStyle(int height)
    {
        const QString style = QString(
            "color: #ECF0F5;"
            "font-size: %1px;"
            "font-weight: bold;"
            "font-family: Monospace;")
                                  .arg(qMax(16, static_cast<int>(height * 0.75)));
        speedValueLabel->setStyleSheet(style);
    }

    void setRedlinePercent(qreal percent)
    {
        percent = qBound(0.0, percent, 100.0);
        if (percent < leadingRedlinePercent)
            percent = leadingRedlinePercent;
        trailingRedlinePercent = percent;
        qreal minV = speedometer->minValue();
        qreal maxV = speedometer->maxValue();
        trailingRedlineStart = minV + (maxV - minV) * (percent / 100.0);
        applyRedlineZones();
    }

    void setLeadingRedlinePercent(qreal percent)
    {
        percent = qBound(0.0, percent, 100.0);
        if (percent > trailingRedlinePercent)
            percent = trailingRedlinePercent;
        leadingRedlinePercent = percent;
        qreal minV = speedometer->minValue();
        qreal maxV = speedometer->maxValue();
        leadingRedlineEnd = minV + (maxV - minV) * (percent / 100.0);
        applyRedlineZones();
    }

    void applyRedlineZones()
    {
        speedometer->clearZones();
        if (leadingRedlineEnd > speedometer->minValue()) {
            GaugeZone *leadingRedline = GaugeZone::createDangerZone(speedometer->minValue(), leadingRedlineEnd);
            leadingRedline->setColor(QColor(217, 30, 54));
            leadingRedline->setOpacity(0.6);
            speedometer->addZone(leadingRedline);
        }

        GaugeZone *normal = GaugeZone::createNormalZone(leadingRedlineEnd, trailingRedlineStart);
        normal->setColor(DashboardPalette::slate());
        normal->setOpacity(0.45);
        speedometer->addZone(normal);

        if (trailingRedlineStart < speedometer->maxValue()) {
            GaugeZone *trailingRedline = GaugeZone::createDangerZone(trailingRedlineStart, speedometer->maxValue());
            trailingRedline->setColor(QColor(217, 30, 54));
            trailingRedline->setOpacity(0.6);
            speedometer->addZone(trailingRedline);
        }
    }

    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (watched == speedometer && event->type() == QEvent::Resize) {
            QRect r = speedometer->rect();
            const int valueWidth = static_cast<int>(r.width() * 0.44);
            const int valueHeight = static_cast<int>(r.height() * 0.13);
            const int valueX = (r.width() - valueWidth) / 2;
            const int valueY = static_cast<int>(r.height() * 0.66) + 30;
            speedValueLabel->setGeometry(valueX, valueY, valueWidth, valueHeight);
            speedValueLabel->setAlignment(Qt::AlignCenter);
            updateSpeedLabelStyle(valueHeight);

            const int textHeight = qMax(14, static_cast<int>(r.height() * 0.045));
            const int textWidth = static_cast<int>(r.width() * 0.4);
            const int textX = (r.width() - textWidth) / 2;
            const int textY = valueY - textHeight - static_cast<int>(r.height() * 0.01) + 15;
            speedLabel->setGeometry(textX, textY, textWidth, textHeight);
        }
        return QMainWindow::eventFilter(watched, event);
    }

    Speedometer *speedometer;
    QLabel *speedValueLabel;
    QLabel *speedLabel;
    qreal leadingRedlinePercent = 0.0;
    qreal trailingRedlinePercent = 75.0;
    qreal leadingRedlineEnd = 0.0;
    qreal trailingRedlineStart = 0.0;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DashboardWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
