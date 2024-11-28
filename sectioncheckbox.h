#ifndef SECTIONCHECKBOX_H
#define SECTIONCHECKBOX_H

/*!
 * \file sectioncheckbox.h
 * \brief Заголовочный файл класса SectionCheckBox
 */

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>

/*!
 * \class SectionCheckBox
 * \brief Класс, реализующий секцию текст-чекбокс
 */
class SectionCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit SectionCheckBox(
        QWidget *parent = nullptr,
        const QString &text = nullptr,
        const bool checked = false
    );

    bool checked() const;
    void setChecked(bool state);
private:
    QCheckBox *checkBox;
signals:
    void checkedChanged(bool checked);
private slots:
    void onCheckedChanged(int state);
};

#endif // SECTIONCHECKBOX_H
