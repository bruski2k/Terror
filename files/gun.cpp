#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QTimer>
#include <QDebug>

#include "gun.h"

// gun prototype constructor
gun::gun(int x, int y, int orientation, QColor colour) {

    x_ = x;
    y_ = y;
    orientation_ = orientation;
    in_flight_ = false;
    colour_ = colour;

}

// changes x depending on orientation
// returns truth value false if outside scene
bool gun::change_x() {
    prepareGeometryChange();
    if (-4 <= x_ && x_ <= 1804){
        switch (orientation_){

            //facing west
            case 0:
                x_ = x_ - speed_;
                break;

            //facing north-west
            case 1:
                x_ = x_ - (2*sqrt(speed_*speed_));
                break;

            //facing north
            case 2:
                break;

            //facing north-east
            case 3:
                x_ = x_ + (2*sqrt(speed_*speed_));
                break;

            //facing east
            case 4:
                x_ = x_ + speed_;
                break;

            //facing south-east
            case 5:
                x_ = x_ + (2*sqrt(speed_*speed_));
                break;

            //facing south
            case 6:
                break;

            //facing south-west
            case 7:
                x_ = x_ - (2*sqrt(speed_*speed_));
                break;

        }
        return false;
    }
    update();
    return true;
}

// changes y depending on orientation
// returns truth value false if outside scene
bool gun::change_y() {
    prepareGeometryChange();
    if (-4 <= y_ && y_ <= 804){
        switch (orientation_){

            //facing west
            case 0:
                break;


            //facing north-west
            case 1:
                y_ = y_ - (2*sqrt(speed_*speed_));
                break;

            //facing north
            case 2:
                y_ = y_ - speed_;
                break;

            //facing north-east
            case 3:
                y_ = y_ - (2*sqrt(speed_*speed_));
                break;

            //facing east
            case 4:
                break;

            //facing south-east
            case 5:
                y_ = y_ + (2*sqrt(speed_*speed_));
                break;

            //facing south
            case 6:
                y_ = y_ + speed_;
                break;

            //facing south-west
            case 7:
                y_ = y_ + (2*sqrt(speed_*speed_));
                break;

        }
        return false;
    }
    update();
    return true;
}


// wrapper function for change coordinates
// returns truth value false if outside scene
bool gun::move() {
    if (change_x() || change_y()){
        return true;
    }
    return false;
}




//paint object manipulators prototype
QRectF gun::boundingRect() const{

    switch (orientation_){

        //facing west
        case 0:
            return QRectF(get_x()-get_height(), get_y(), get_height(), get_width());

        //facing north-west
        case 1:
            return QRectF(get_x()-5, get_y()-5, 5, 5);

        //facing north
        case 2:
            return QRectF(get_x(), get_y(), get_width(), get_height());

        //facing north-east
        case 3:
            return QRectF(get_x(), get_y()-5, 5, 5);

        //facing east
        case 4:
            return QRectF(get_x(), get_y(), get_height(), get_width());

        //facing south-east
        case 5:
            return QRectF(get_x(), get_y(), 5, 5);

        //facing south
        case 6:
            return QRectF(get_x(), get_y(), get_width(), get_height());

        //facing south-west
        case 7:
            return QRectF(get_x()-5, get_y(), 5, 5);

    }
}

// hit box draw
QPainterPath gun::shape() const {
    QPainterPath path;
    QPolygon shape;
    switch (orientation_) {

        //facing west
        case 0:
            path.addRect(get_x(), get_y(), get_height(), get_width());
            break;

        //facing north-west
        case 1:
            shape << QPoint(get_x()-1, get_y());
            shape << QPoint(get_x()-5, get_y()-4);
            shape << QPoint(get_x()-4, get_y()-5);
            shape << QPoint(get_x(), get_y()-1);
            shape << QPoint(get_x()-1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

        //facing north
        case 2:
            path.addRect(get_x(), get_y(), get_width(), get_height());
            break;

        //facing north-east
        case 3:
            shape << QPoint(get_x()+1, get_y());
            shape << QPoint(get_x()+5, get_y()-4);
            shape << QPoint(get_x()+4, get_y()-5);
            shape << QPoint(get_x(), get_y()-1);
            shape << QPoint(get_x()+1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

        //facing east
        case 4:
            path.addRect(get_x(), get_y(), get_height(), get_width());
            break;

        //facing south-east
        case 5:
            shape << QPoint(get_x()+1, get_y());
            shape << QPoint(get_x()+5, get_y()+4);
            shape << QPoint(get_x()+4, get_y()+5);
            shape << QPoint(get_x(), get_y()+1);
            shape << QPoint(get_x()+1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

        //facing south
        case 6:
            path.addRect(get_x(), get_y(), get_width(), get_height());
            break;

        //facing south-west
        case 7:
            shape << QPoint(get_x()-1, get_y());
            shape << QPoint(get_x()-5, get_y()+4);
            shape << QPoint(get_x()-4, get_y()+5);
            shape << QPoint(get_x(), get_y()+1);
            shape << QPoint(get_x()-1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

    }

    return path;
}



// paints bullet
void gun::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    painter->setBrush(colour_);
    switch (get_orientation()){

        //facing west
        case 0:
            painter->drawRect(get_x()-get_height(), get_y(), get_height(), get_width());
            break;

        //facing north-west
        case 1:
            painter->drawLine(get_x()-1, get_y(), get_x()-5, get_y()-4);
            painter->drawLine(get_x(), get_y()-1, get_x()-4, get_y()-5);
            break;

        //facing north
        case 2:
            painter->drawRect(get_x()-get_width(), get_y()-get_height(), get_width(), get_height());
            break;

        //facing north-east
        case 3:
            painter->drawLine(get_x()+1, get_y(), get_x()+5, get_y()-4);
            painter->drawLine(get_x(), get_y()-1, get_x()+4, get_y()-5);
            break;

        //facing east
        case 4:
            painter->drawRect(get_x(), get_y()-get_width(), get_height(), get_width());
            break;

        //facing south-east
        case 5:
            painter->drawLine(get_x()+1, get_y(), get_x()+5, get_y()+4);
            painter->drawLine(get_x(), get_y()+1, get_x()+4, get_y()+5);
            break;

        //facing south
        case 6:
            painter->drawRect(get_x(), get_y(), get_width(), get_height());
            break;

        //facing south-west
        case 7:
            painter->drawLine(get_x()-1, get_y(), get_x()-5, get_y()+4);
            painter->drawLine(get_x(), get_y()+1, get_x()-4, get_y()+5);
            break;
    }
}


// pistol constructor
pistol::pistol(int x, int y, int o, QColor c) : gun(x,y,o,c) {}


// checks pistol collisions
bool pistol::check_collisions(std::vector<zombie*> zombies, std::vector<zombie*> &zo_to_erase) {
    prepareGeometryChange();
    update();
    for (int i = 0; i < zombies.size(); i++){
        if (collidesWithItem(zombies[i])){
            if (zombies[i]->change_hp(zombies[i]->get_hp() - dmg_)){
                zo_to_erase.push_back(zombies[i]);
            }
            return true;
        }
    }
    return false;

}


// constructor
ak::ak(int x, int y, int o, QColor c) : gun(x,y,o,c) {}

// checks ak collisions
bool ak::check_collisions(std::vector<zombie*> zombies, std::vector<zombie*> &zo_to_erase) {
    prepareGeometryChange();
    update();
    for (int i = 0; i < zombies.size(); i++){
        if (collidesWithItem(zombies[i])){
            if (zombies[i]->change_hp(zombies[i]->get_hp() - dmg_)){
                zo_to_erase.push_back(zombies[i]);
            }
            return true;
        }
    }
    return false;
}


// constructor
railgun::railgun(int x, int y, int o, QColor c) : gun(x,y,o,c) {}


// checks railgun collisions
bool railgun::check_collisions(std::vector<zombie*> zombies, std::vector<zombie*> &zo_to_erase) {
    bool hit = false;
    prepareGeometryChange();
    update();
    for (int i = 0; i < zombies.size(); i++){
        if (collidesWithItem(zombies[i])){
            if (zombies[i]->change_hp(zombies[i]->get_hp() - dmg_)){
                zo_to_erase.push_back(zombies[i]);
            }
            hit = true;
        }
    }
    return hit;
}


// bounding rectangle
QRectF railgun::boundingRect() const{
    switch (get_orientation()){

        //facing west
        case 0:
            return QRectF(get_x()-length_, get_y(), length_, get_width());

        //facing north-west
        case 1:
            return QRectF(get_x()-length_, get_y()-length_, length_, length_);

        //facing north
        case 2:
            return QRectF(get_x(), get_y()-length_, get_width(), length_);

        //facing north-east
        case 3:
            return QRectF(get_x(), get_y()-length_, length_, length_);

        //facing east
        case 4:
            return QRectF(get_x(), get_y(), length_, get_width());

        //facing south-east
        case 5:
            return QRectF(get_x(), get_y(), length_, length_);

        //facing south
        case 6:
            return QRectF(get_x(), get_y(), get_width(), length_);

        //facing south-west
        case 7:
            return QRectF(get_x()-length_, get_y(), length_, length_);

    }
}

// hitbox shape
QPainterPath railgun::shape() const {
    QPainterPath path;
    QPolygon shape;
    switch (get_orientation()) {

        //facing west
        case 0:
            path.addRect(get_x()-length_, get_y(), length_, get_width());
            break;

        //facing north-west
        case 1:
            shape << QPoint(get_x()-1, get_y());
            shape << QPoint(get_x()-length_, get_y()-length_+1);
            shape << QPoint(get_x()-length_+1, get_y()-length_);
            shape << QPoint(get_x(), get_y()-1);
            shape << QPoint(get_x()-1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

        //facing north
        case 2:
            path.addRect(get_x(), get_y()-length_, get_width(), length_);
            break;

        //facing north-east
        case 3:
            shape << QPoint(get_x()+1, get_y());
            shape << QPoint(get_x()+length_, get_y()-length_+1);
            shape << QPoint(get_x()+length_-1, get_y()-length_);
            shape << QPoint(get_x(), get_y()-1);
            shape << QPoint(get_x()+1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

        //facing east
        case 4:
            path.addRect(get_x(), get_y(), length_, get_width());
            break;

        //facing south-east
        case 5:
            shape << QPoint(get_x()+1, get_y());
            shape << QPoint(get_x()+length_, get_y()+length_-1);
            shape << QPoint(get_x()+length_-1, get_y()+length_);
            shape << QPoint(get_x(), get_y()+1);
            shape << QPoint(get_x()+1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

        //facing south
        case 6:
            path.addRect(get_x(), get_y(), get_width(), length_);
            break;

        //facing south-west
        case 7:
            shape << QPoint(get_x()-1, get_y());
            shape << QPoint(get_x()-length_, get_y()+length_-1);
            shape << QPoint(get_x()-length_+1, get_y()+length_);
            shape << QPoint(get_x(), get_y()+1);
            shape << QPoint(get_x()-1, get_y());
            path.addPolygon(shape);
            path.closeSubpath();
            break;

    }

    return path;
}

// paints on scene
void railgun::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    painter->setBrush(colour_);
    switch (get_orientation()){

        //facing west
        case 0:
            painter->drawRect(get_x()-length_, get_y(), length_, get_width());
            break;

        //facing north-west
        case 1:
            painter->drawLine(get_x()-1, get_y(), get_x()-length_, get_y()-length_+1);
            painter->drawLine(get_x(), get_y()-1, get_x()-length_+1, get_y()-length_);
            break;

        //facing north
        case 2:
            painter->drawRect(get_x(), get_y()-length_, get_width(), length_);
            break;

        //facing north-east
        case 3:
            painter->drawLine(get_x()+1, get_y(), get_x()+length_, get_y()-length_+1);
            painter->drawLine(get_x(), get_y()-1, get_x()+length_-1, get_y()-length_);
            break;

        //facing east
        case 4:
            painter->drawRect(get_x(), get_y(), length_, get_width());
            break;

        //facing south-east
        case 5:
            painter->drawLine(get_x()+1, get_y(), get_x()+length_, get_y()+length_-1);
            painter->drawLine(get_x(), get_y()+1, get_x()+length_-1, get_y()+length_);
            break;

        //facing south
        case 6:
            painter->drawRect(get_x(), get_y(), get_width(), length_);
            break;

        //facing south-west
        case 7:
            painter->drawLine(get_x()-1, get_y(), get_x()-length_, get_y()+length_-1);
            painter->drawLine(get_x(), get_y()+1, get_x()-length_+1, get_y()+length_);
            break;
    }
}

