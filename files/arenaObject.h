#ifndef ARENAOBJECT_H
#define ARENAOBJECT_H

#include <QColor>
#include <QGraphicsItem>

// enumerated item type, which is then stored within item class
enum class currentPickUp { none, speedUp, healUp, invincibility };


class pickUp : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        //constructor
        pickUp(int x, int y, currentPickUp s, QColor c);

        int get_x() const { return x_; }  // inline member function
        int get_y() const { return y_; }  // inline member
        int get_width() const { return width_; } // inline member
        currentPickUp get_pickUp() { return current_; } // returns item type


        //paint object manipulators
        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        int x_;
        int y_;
        static const int width_ = 12;
        int timer_ = 1500;
        currentPickUp current_;
        QColor color_;


};



#endif // ARENAOBJECT_H
