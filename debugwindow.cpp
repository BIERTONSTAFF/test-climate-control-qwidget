/*!
 * \file debugwindow.cpp
 * \brief Файл реализации класса DebugWindow
 */

#include "debugwindow.h"

DebugWindow::DebugWindow(
    double t,
    int h,
    double p
) {
    setWindowTitle("Отладка");
    setMinimumSize(300, 300);

    auto layout = new QVBoxLayout(this);
    auto tInput = new QDoubleSpinBox(this);

    tInput->setRange(-50, 50);
    tInput->setSuffix("°C");
    tInput->setValue(t);

    auto hInput = new QDoubleSpinBox(this);

    hInput->setRange(0, 100);
    hInput->setSuffix("%");
    hInput->setValue(h);

    auto pInput = new QDoubleSpinBox(this);

    pInput->setRange(700, 800);
    pInput->setSuffix("мм.рт.ст.");
    pInput->setValue(p);

    auto saveButton = new QPushButton("Сохранить", this);

    connect(saveButton, &QPushButton::clicked, this, [this, tInput, hInput, pInput]() {
        emit save(tInput->value(), hInput->value(), pInput->value());

        this->close();
    });

    layout->addWidget(tInput);
    layout->addWidget(hInput);
    layout->addWidget(pInput);
    layout->addWidget(saveButton);
}
