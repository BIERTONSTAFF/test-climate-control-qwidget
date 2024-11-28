#ifndef SECTIONCOMBOBOX_H
#define SECTIONCOMBOBOX_H

/*!
 * \file sectioncombobox.h
 * \brief Заголовочный файл класса SectionComboBox
 */

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

/*!
 * \class SectionComboBox
 * \brief Класс, реализующий секцию текст-комбобокс
 */
class SectionComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit SectionComboBox(
        QWidget *parent = nullptr,
        const QString &text = nullptr,
        const QStringList *options = nullptr
    );

    int currentIdx() const;
    void setCurrentIdx(int idx);
private:
    QComboBox *comboBox;
signals:
    void idxChanged(int idx);
private slots:
    void onIdxChanged(int idx);
};

#endif // SECTIONCOMBOBOX_H
