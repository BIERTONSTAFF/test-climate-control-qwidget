/*!
 * \file mainwindow.cpp
 * \brief Файл реализации класса MainWindow
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "block.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settings = new Settings(nullptr, QDir::currentPath() + "/settings.xml");
    this->system = new System();

    setMinimumSize(800, 600);
    setMaximumSize(1024, 768);
    setWindowTitle("Управление кондиционированием");

    auto widget = new QWidget(this);
    auto mainLayout = new QVBoxLayout(widget);

    setCentralWidget(widget);

    auto monitoringGroup = new QGroupBox("Мониторинг", widget);
    auto monitoringLayout = new QVBoxLayout(monitoringGroup);

    this->tSensor = new Sensor(widget, "Температура", QString::number(this->t) + this->tUnits[currentTUnits]);
    this->hSensor = new Sensor(widget, "Влажность", QString::number(this->h) + "%");
    this->pSensor = new Sensor(widget, "Давление", QString::number(this->p) + this->pUnits[currentPUnits]);

    monitoringLayout->addWidget(this->tSensor);
    monitoringLayout->addWidget(this->hSensor);
    monitoringLayout->addWidget(this->pSensor);

    auto displayGroup = new QGroupBox("Отображение", widget);
    auto displayLayout = new QVBoxLayout(displayGroup);

    this->tSelect = new SectionComboBox(widget, "Шкала температуры", &this->tUnits);
    this->pSelect = new SectionComboBox(widget, "Ед. изм. давления", &this->pUnits);
    this->isDarkThemeCheckBox = new SectionCheckBox(widget, "Темная тема", this->isDarkTheme);

    connect(this->tSelect, &SectionComboBox::idxChanged, this, &MainWindow::onTSelectIdxChanged);
    connect(this->pSelect, &SectionComboBox::idxChanged, this, &MainWindow::onPSelectIdxChanged);
    connect(this->isDarkThemeCheckBox, &SectionCheckBox::checkedChanged, this, &MainWindow::onIsDarkCheckChanged);

    displayLayout->addWidget(tSelect);
    displayLayout->addWidget(pSelect);
    displayLayout->addWidget(this->isDarkThemeCheckBox);

    auto systemGroup = new QGroupBox("Система", widget);
    auto systemLayout = new QVBoxLayout(systemGroup);

    auto powerCheck = new SectionCheckBox(widget, "Питание", false);
    auto airFlowDirectionSelect = new SectionComboBox(widget, "Направление подачи воздуха", &this->airFlowDirections);

    this->systemStatus = new Sensor(widget, "Состояние системы", "Неактивна");

    connect(powerCheck, &SectionCheckBox::checkedChanged, this, &MainWindow::onPowerCheckChanged);
    connect(airFlowDirectionSelect, &SectionComboBox::idxChanged, this, &MainWindow::onAirFlowDirectionChanged);

    systemLayout->addWidget(powerCheck);
    systemLayout->addWidget(airFlowDirectionSelect);
    systemLayout->addWidget(this->systemStatus);

    auto scene = new QGraphicsScene(widget);
    auto view = new QGraphicsView(scene, widget);

    view->setMaximumSize(this->maximumWidth(), 38);

    int blockWidth = (this->width() - 24) / 3;

    this->blocks = new QList{
        new Block("Блок 1", 0, 50, blockWidth, 32, false),
        new Block("Блок 2", blockWidth, 50, blockWidth, 32, false),
        new Block("Блок 3", blockWidth * 2, 50, blockWidth, 32, false)
    };

    for (Block *block : *this->blocks) {
        scene->addItem(block);
    }

    this->debugButton = new QPushButton("Отладка", this);

    this->debugButton->setEnabled(false);

    connect(this->debugButton, &QPushButton::clicked, this, [&]() {
        this->debugWindow = new DebugWindow(t, h, p);
        connect(this->debugWindow, &DebugWindow::save, this, &MainWindow::onDebugWindowSave);

        this->debugWindow->show();
    });

    mainLayout->addWidget(monitoringGroup);
    mainLayout->addWidget(displayGroup);
    mainLayout->addWidget(systemGroup);
    mainLayout->addWidget(view);
    mainLayout->addWidget(this->debugButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e) {
    QWidget::showEvent(e);

    connect(settings, &Settings::loaded, this, &MainWindow::onSettingsLoaded);
    connect(system, &System::powerStatusChanged, this, &MainWindow::onSystemPowerStatusChanged);
    connect(system, &System::airFlowDirectionChanged, this, &MainWindow::onSystemAirFlowDirectionChanged);
    connect(system, &System::temperatureChanged, this, &MainWindow::onSystemTChanged);
    connect(system, &System::humidityChanged, this, &MainWindow::onSystemHChanged);
    connect(system, &System::pressureChanged, this, &MainWindow::onSystemPChanged);
    connect(system, &System::blockStatusChanged, this, &MainWindow::onSystemBlockStatusChanged);

    this->settings->load();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    this->settings->save(this->currentTUnits, this->currentPUnits, this->isDarkTheme);

    QWidget::closeEvent(e);
}

void MainWindow::onSettingsLoaded(int currentTUnit, int currentPUnit, bool isDarkTheme)
{
    this->currentTUnits = currentTUnit;
    this->currentPUnits = currentPUnit;
    this->isDarkTheme = isDarkTheme;

    this->tSelect->setCurrentIdx(this->currentTUnits);
    this->pSelect->setCurrentIdx(this->currentPUnits);
    this->isDarkThemeCheckBox->setChecked(this->isDarkTheme);

    this->setDarkTheme(this->isDarkTheme);
}

double MainWindow::convertTUnits(double value, int units)
{
    switch (units) {
    case 1: return (value * 9 / 5) + 32;
    case 2: return value + 273.15;
    default: return value;
    }
}

double MainWindow::convertPUnits(double value, int units)
{
    return units == 1 ? value * 133.332 : value;
}

void MainWindow::setDarkTheme(bool isDark)
{
    QPalette p = style()->standardPalette();

    if (isDark) {
        struct Color
        {
            QPalette::ColorRole r;
            QColor c;
        };

        const std::vector<Color> colors {
            {QPalette::Window, QColor(53, 53, 53)},
            {QPalette::WindowText, Qt::white},
            {QPalette::Base, QColor(25, 25, 25)},
            {QPalette::AlternateBase, QColor(53, 53, 53)},
            {QPalette::ToolTipBase, Qt::white},
            {QPalette::ToolTipText, Qt::white},
            {QPalette::Text, Qt::white},
            {QPalette::Button, QColor(53, 53, 53)},
            {QPalette::ButtonText, Qt::white},
            {QPalette::BrightText, Qt::red},
            {QPalette::Link, QColor(42, 130, 218)},
            {QPalette::Highlight, QColor(42, 130, 218)},
            {QPalette::HighlightedText, Qt::black}
        };

        for (const auto &c : colors) {
            p.setColor(c.r, c.c);
        }
    }

    qApp->setPalette(p);
}

void MainWindow::onTSelectIdxChanged(int idx)
{
    this->currentTUnits = idx;
    this->tSensor->update(
        QString::number(
            convertTUnits(this->t, this->currentTUnits)
            ) + this->tUnits[currentTUnits]
        );
}

void MainWindow::onPSelectIdxChanged(int idx)
{
    this->currentPUnits = idx;
    this->pSensor->update(
        QString::number(
            convertPUnits(this->p, this->currentPUnits)
            ) + this->pUnits[currentPUnits]
        );
}

void MainWindow::onIsDarkCheckChanged(bool checked)
{
    this->isDarkTheme = checked;
    this->setDarkTheme(this->isDarkTheme);
}

void MainWindow::onPowerCheckChanged(bool checked)
{
    this->system->power(checked);
}

void MainWindow::onAirFlowDirectionChanged(int idx)
{
    this->system->airFlowDirection(idx);
}

void MainWindow::onDebugWindowSave(double t, int h, double p)
{
    this->t = t;
    this->h = h;
    this->p = p;
    this->tSensor->update(
        QString::number(
            convertTUnits(this->t, this->currentTUnits)
            ) + this->tUnits[currentTUnits]
        );
    this->hSensor->update(QString::number(this->h) + "%");
    this->pSensor->update(
        QString::number(
            convertPUnits(this->p, this->currentPUnits)
            ) + this->pUnits[currentPUnits]
        );
}

void MainWindow::onSystemPowerStatusChanged(bool s)
{
    this->debugButton->setEnabled(s);
    this->systemStatus->update(s ? "Активна" : "Неактивна");
}

void MainWindow::onSystemAirFlowDirectionChanged(uint d)
{
    this->airFlowDirection = d;
}

void MainWindow::onSystemTChanged(double t)
{
    this->t = t;
    this->tSensor->update(
        QString::number(
            convertTUnits(this->t, this->currentTUnits)
            ) + this->tUnits[currentTUnits]
        );
}

void MainWindow::onSystemHChanged(uint h)
{
    this->h = h;
    this->tSensor->update(QString::number(this->h) + "%");
}

void MainWindow::onSystemPChanged(double p)
{
    this->p = p;
    this->pSensor->update(
        QString::number(
            convertPUnits(this->p, this->currentPUnits)
            ) + this->pUnits[currentPUnits]
        );
}

void MainWindow::onSystemBlockStatusChanged(uint b, bool s)
{
    this->blocks->at(b)->setEnabled(s);
}
