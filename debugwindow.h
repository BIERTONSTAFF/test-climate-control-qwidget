#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

/*!
 * \file debugwindow.h
 * \brief Заголовочный файл класса DebugWindow
 */

#include <QDialog>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>

/*!
 * \class DebugWindow
 * \brief Класс, реализующий окно отладки
 */
class DebugWindow : public QDialog
{
    Q_OBJECT
public:
    DebugWindow(
        double t,
        int h,
        double p
    );

signals:
    void save(double t, int h, double p);
};

#endif // DEBUGWINDOW_H
