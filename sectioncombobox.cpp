/*!
 * \file sectioncombobox.cpp
 * \brief Файл реализации класса SectionCombobox
 */

#include "sectioncombobox.h"

SectionComboBox::SectionComboBox(QWidget *parent, const QString &text, const QStringList *options)
    : QWidget{parent}
{
    setMinimumHeight(48);

    auto layout = new QHBoxLayout(this);
    auto label = new QLabel(text, this);

    this->comboBox = new QComboBox(this);

    this->comboBox->addItems(*options);

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(this->comboBox);

    setLayout(layout);

    connect(
        this->comboBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &SectionComboBox::onIdxChanged
    );
}

int SectionComboBox::currentIdx() const
{
    return comboBox->currentIndex();
}

void SectionComboBox::setCurrentIdx(int idx)
{
    this->comboBox->setCurrentIndex(idx);
}

void SectionComboBox::onIdxChanged(int idx)
{
    emit idxChanged(idx);
}
