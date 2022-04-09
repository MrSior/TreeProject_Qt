#include "rectangulartest.h"

RectangularTest::RectangularTest(int x, int y, int key) : QGraphicsItem()
{
    x_offset = x;
    y_offset = y;
    this->key = key;
    points[0] = QPoint(10 + x, 20 + y);
    points[1] = QPoint(10 + x, 60 + y);
    points[2] = QPoint(100 + x, 60 + y);
    points[3] = QPoint(100 + x, 20 + y);
}

void RectangularTest::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon pol;
    pol << QPoint(points[0]) << QPoint(points[1]) << QPoint(points[2]) << QPoint(points[3]);
    painter->setPen(QColor(105, 105, 105));
    painter->setBrush(QColor(155, 155, 155));
//    painter->drawPolygon(pol);
    painter->drawEllipse(points[0], 50, 25);
    painter->drawText(points[0], QString::fromStdString(std::to_string(key)));
}

QRectF RectangularTest::boundingRect() const
{
    return QRectF(QPointF(-30 + x_offset, -20 + y_offset), QSizeF(90, 60));
}
