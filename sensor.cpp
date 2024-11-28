/*!
 * \file sensor.cpp
 * \brief Файл реализации класса Sensor
 */

#include "sensor.h"

Sensor::Sensor(QWidget *parent, const QString &l, const QString &v)
    : QWidget{parent}
{
    setMinimumHeight(48);

    auto layout = new QHBoxLayout(this);
    auto label = new QLabel(l, this);
    this->value = new QLabel(v, this);

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(this->value);

    setLayout(layout);
}

void Sensor::update(const QString &v)
{
    this->value->setText(v);
}
