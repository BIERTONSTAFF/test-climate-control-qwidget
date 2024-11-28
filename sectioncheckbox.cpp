/*!
 * \file sectioncheckbox.cpp
 * \brief Файл реализации класса SectionCheckbox
 */

#include "sectioncheckbox.h"

SectionCheckBox::SectionCheckBox(QWidget *parent, const QString &text, const bool checked)
    : QWidget{parent}
{
    setMinimumHeight(48);

    auto layout = new QHBoxLayout(this);
    auto label = new QLabel(text, this);

    this->checkBox = new QCheckBox(this);

    this->checkBox->setChecked(checked);

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(this->checkBox);

    setLayout(layout);

    connect(
        this->checkBox,
        &QCheckBox::stateChanged,
        this,
        &SectionCheckBox::onCheckedChanged
    );
}

bool SectionCheckBox::checked() const
{
    return this->checkBox->checkState();
}

void SectionCheckBox::setChecked(bool state)
{
    this->checkBox->setChecked(state);
}

void SectionCheckBox::onCheckedChanged(int state)
{
    emit checkedChanged(state == Qt::Checked);
}
