#ifndef SENSOR_H
#define SENSOR_H

/*!
 * \file sensor.h
 * \brief Заголовочный файл класса Sensor
 */

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

/*!
 * \class Sensor
 * \brief Класс, реализующий секцию текст-текст
 */
class Sensor : public QWidget
{
    Q_OBJECT
public:
    explicit Sensor(
        QWidget *parent = nullptr,
        const QString &l = nullptr,
        const QString &v = nullptr
    );

    void update(const QString &v);

private:
    QLabel *value;
signals:
};

#endif // SENSOR_H
