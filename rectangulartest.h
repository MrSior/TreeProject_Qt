#ifndef RECTANGULARTEST_H
#define RECTANGULARTEST_H

#include "QGraphicsItem"
#include "QPainter"

class RectangularTest : public QGraphicsItem
{
public:
    RectangularTest(int x, int y, int key);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    int x_offset, y_offset;
    int key;
    QPoint points[4];
};

#endif // RECTANGULARTEST_H
