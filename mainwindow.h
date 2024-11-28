#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file mainwindow.h
 * \brief Заголовочный файл класса MainWindow
 */

#include <QMainWindow>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QStyleFactory>
#include <QPalette>

#include "sensor.h"
#include "settings.h"
#include "system.h"
#include "sectioncombobox.h"
#include "sectioncheckbox.h"
#include "block.h"
#include "debugwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \class MainWindow
 * \brief Класс, реализующий главное окно приложения
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса MainWindow
     * \param parent Родительский QWidget
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Деструктор класса MainWindow
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui; /*!< Интерфейс пользователя */
    Settings *settings; /*!< Настройки приложения */
    System *system; /*!< Управление системой кондиционирования */
    DebugWindow *debugWindow; /*!< Окно отладки */

    double t = 0; /*!< Текущая температура */
    double h = 0; /*!< Текущая влажность */
    double p = 700; /*!< Текущее давление */
    int currentTUnits = 0; /*!< Единицы измерения температуры */
    int currentPUnits = 0; /*!< Единицы измерения давления */
    int airFlowDirection = 0; /*!< Направление воздушного потока */
    bool isDarkTheme = false; /*!< Состояние тёмной темы */
    const QStringList
        tUnits = {"°C", "°F", "K"}, /*!< Список единиц измерения температуры */
        pUnits = {"мм.рт.ст.", "Па"}, /*!< Список единиц измерения давления */
        airFlowDirections = {"Выдув", "Вдув"}, /*!< Список направлений потока воздуха */
        blockColors = {"#E74856", "#00CC6A"}; /*!< Цвета блоков для отображения их статуса */

    Sensor *systemStatus, /*!< Индикатор статуса системы */
        *tSensor, /*!< Индикатор температуры */
        *hSensor, /*!< Индикатор влажности */
        *pSensor; /*!< Индикатор давления */

    SectionComboBox *tSelect, /*!< Виджет выбора единиц измерения температуры */
        *pSelect; /*!< Виджет выбора единиц измерения давления */
    SectionCheckBox *isDarkThemeCheckBox; /*!< Виджет выбора темы интерфейса */

    QList<Block *> *blocks; /*!< Список условных блоков системы */
    QPushButton *debugButton; /*!< Кнопка открытия окна отладки */

    /*!
     * \brief Обработчик события отображения окна
     * \param e Событие отображения
     */
    void showEvent(QShowEvent *e) override;

    /*!
     * \brief Обработчик события закрытия окна
     * \param e Событие закрытия
     */
    void closeEvent(QCloseEvent *e) override;

    /*!
     * \brief Конвертирует значение температуры в выбранные единицы
     * \param value Значение температуры
     * \param units Выбранные единицы
     * \return Конвертированное значение температуры
     */
    double convertTUnits(double value, int units);

    /*!
     * \brief Конвертирует значение давления в выбранные единицы
     * \param value Значение давления
     * \param units Выбранные единицы
     * \return Конвертированное значение давления
     */
    double convertPUnits(double value, int units);

    /*!
     * \brief Переключает тему интерфейса
     * \param s true, если нужна тёмная тема
     */
    void setDarkTheme(bool s);

private slots:
    /*!
     * \brief Обработчик загрузки настроек
     */
    void onSettingsLoaded(int currentTUnit, int currentPUnit, bool isDarkTheme);

    /*!
     * \brief Обработчик изменения выбора единиц измерения температуры
     */
    void onTSelectIdxChanged(int idx);

    /*!
     * \brief Обработчик изменения выбора единиц измерения давления
     */
    void onPSelectIdxChanged(int idx);

    /*!
     * \brief Обработчик изменения статуса тёмной темы
     */
    void onIsDarkCheckChanged(bool checked);

    /*!
     * \brief Обработчик изменения статуса питания системы
     */
    void onPowerCheckChanged(bool checked);

    /*!
     * \brief Обработчик изменения направления воздушного потока
     */
    void onAirFlowDirectionChanged(int idx);

    /*!
     * \brief Обработчик сохранения данных в окне отладки
     */
    void onDebugWindowSave(double t, int h, double p);

    // Сигналы от системы
    void onSystemPowerStatusChanged(bool s);
    void onSystemAirFlowDirectionChanged(uint d);
    void onSystemTChanged(double t);
    void onSystemHChanged(uint h);
    void onSystemPChanged(double p);
    void onSystemBlockStatusChanged(uint b, bool s);
};

#endif // MAINWINDOW_H
