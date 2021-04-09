#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include <arenaObject.h>

// item constructor
pickUp::pickUp(int x, int y, currentPickUp s, QColor c) {

    x_ = x;
    y_ = y;
    current_ = s;
    color_ = c;

}

// creates bounding rectangle
QRectF pickUp::boundingRect() const{
    return QRectF(x_, y_, width_, width_);
}


// creates hitbox
QPainterPath pickUp::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

// paints object into scene
void pickUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(color_);
    painter->drawRect(get_x(), get_y(), get_width(), get_width());
}



