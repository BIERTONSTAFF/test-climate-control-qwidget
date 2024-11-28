/*!
 * \file block.cpp
 * \brief Файл реализации класса Block
 */

#include "block.h"
#include <QtGui/qbrush.h>

Block::Block(const QString &text, int x, int y, int width, int height, bool s) {
    this->block = new QGraphicsRectItem(x, y, width, height);

    auto label = new QGraphicsTextItem(text);

    block->setBrush(QColor(s ? "#00CC6A" : "#E74856"));
    this->addToGroup(block);

    label->setPos(
        x + width / 2 - label->boundingRect().width() / 2,
        y + height / 2 - label->boundingRect().height() / 2
    );

    this->addToGroup(label);
}

void Block::setEnabled(bool s)
{
    this->block->setBrush(QColor(s ? "#00CC6A" : "#E74856"));
}
