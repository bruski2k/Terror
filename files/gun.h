#ifndef GUN_H
#define GUN_H

#include <QColor>
#include <QGraphicsItem>
#include "figure.h"

class gun : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        //constructor
        gun(int x, int y, int orientation, QColor colour);
        int get_x() const { return x_; }  // inline member function
        int get_y() const { return y_; }  // inline member
        int get_width() const { return width_; } // inline member
        int get_height() const { return height_; } // inline member
        int get_orientation() const { return orientation_;} // inline member
        // changes x depending on orientation
        // returns truth value false if outside scene
        bool change_x();
        // changes x depending on orientation
        // returns truth value false if outside scene
        bool change_y();
        // wrapper function for change coordinates
        bool move();

        // // these are overriden by the railgun class
        // draws bounding rectangle
        virtual QRectF boundingRect() const override;
        // draws hit box
        virtual QPainterPath shape() const override;
        // draws item on scene
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
        //virtual clone
        virtual gun* clone(int x, int y, int orientation, QColor colour) = 0;


    private:
        int speed_ = 10;
        int x_;
        int y_;
        static const int width_ = 2;
        static const int height_= 4;
        bool in_flight_;
        int orientation_;
        QColor colour_;

};


class pistol : public gun {

    Q_OBJECT

    public:
        // constructor
        pistol(int x, int y, int orientation, QColor colour);
        // returns firing rate
        int get_rate() const { return rate_; }
        // checks pistol collisions
        bool check_collisions(std::vector<zombie*> zombies, std::vector<zombie*> &zo_to_erase);
        //prototype clone method
        gun* clone(int x, int y, int orientation, QColor colour) { return new pistol(x, y, orientation, colour); }

    private:
        QString name_ = "TOKAREV";
        int rate_ = 25;
        int dmg_ = 100;

};


class ak : public gun {

    Q_OBJECT

    public:
        // constructor
        ak(int x, int y, int orientation, QColor colour);
        // returns firing rate
        double get_rate() const { return rate_; }
        // checks ak collisions
        bool check_collisions(std::vector<zombie*> zombies, std::vector<zombie*> &zo_to_erase);
        //prototype clone method
        gun* clone(int x, int y, int orientation, QColor colour) { return new ak(x, y, orientation, colour); }

    private:
        QString name_ = "AK-47";
        double rate_ = .6;
        int dmg_ = 40;

};

class railgun : public gun {

    Q_OBJECT

    public:
        // constructor
        railgun(int x, int y, int orientation, QColor colour);
        // returns firing rate
        int get_rate() const { return rate_; }
        // checks railgun collisions
        bool check_collisions(std::vector<zombie*> zombies, std::vector<zombie*> &zo_to_erase);
        //prototype clone method
        gun* clone(int x, int y, int orientation, QColor colour) { return new railgun(x, y, orientation, colour); }

        // overriden virtual paint, hitbox and rectangle manipulators
        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    private:
        QString name_ = "BF Railgun";
        int rate_ = 100;
        int length_= 1800;
        QColor colour_ = QColor(255, 0, 0);
        int dmg_ = 75;

};


#endif // GUN_H
