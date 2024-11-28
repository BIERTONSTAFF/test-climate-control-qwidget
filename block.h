#ifndef BLOCK_H
#define BLOCK_H

/*!
 * \file block.h
 * \brief Заголовочный файл класса Block
 */

#include <QGraphicsItemGroup>

/*!
 * \class Block
 * \brief Класс, реализующий условный блок системы
 */
class Block : public QGraphicsItemGroup
{
public:
    Block(
        const QString &text,
        int x,
        int y,
        int width,
        int height,
        bool s
    );

    void setEnabled(bool s);

private:
    QGraphicsRectItem *block;
};

#endif // BLOCK_H
