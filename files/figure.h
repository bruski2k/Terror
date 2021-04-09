#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QLine>
#include <QDebug>
#include <vector>

#include "arenaObject.h"

// forward declaration
class gun;
class pistol;
class ak;
class railgun;


// prototype
class figure : public QObject, public QGraphicsItem {

    Q_OBJECT

    public:
        //constructor
        figure(int x, int y);

        // return x coordinate
        int get_x() const { return x_; }  // inline member function
        // returns y coordinate
        int get_y() const { return y_; }  // inline member
        // returns bounding rectangle width
        int get_width() const { return width_; } // inline member
        // returns figure orientation
        int get_orientation() const { return orientation_;} // inline member
        void change_orientation(int orientation) { orientation_ = orientation; }
        // changes x coordinate of figure, hinders player to leave scene
        void change_x(int x, bool zombie);
        // changes y coordinate of figure, hinders player to leave scene
        void change_y(int y, bool zombie);

        //paint object manipulators
        virtual QRectF boundingRect() const override;
        //hit box definer
        virtual QPainterPath shape() const override;

    private:
        int x_;
        int y_;
        static const int width_ = 32;
        int orientation_;

};

class zombie;
class player : public figure {

    Q_OBJECT

    public:
        //constructor
        player(int x, int y, bool ai, QColor q);

        //paint object manipulator
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
        // returns gun x coordinate in hand
        int get_gun_x() const { return gun_x_; }  // inline member function
        // returns gun y coordinate in hand
        int get_gun_y() const { return gun_y_; }  // inline member
        // returns current gun type
        int get_gun() const { return gun_; }
        // return hp
        int get_hp() const { return hp_; }
        // returns player command type
        bool get_ai() const { return ai_; }
        // updates gun position (hand orientation), this was thought to be good for when I make player models
        void updateGunPosition();
        // returns player speed
        int get_speed() const { return speed_; }
        // changes player hp
        void change_hp(int hp) { hp_ = hp; }
        // changes player speed
        void change_speed(int speed) { speed_ = speed; }
        // switches gun forward
        void change_gun_forwards() { if (gun_ != 2){ gun_++; }}
        // switches gun backward
        void change_gun_backwards() { if (gun_ != 0){ gun_--; }}
        // moves cpu player
        void move_ai();
        // updates path for cpu players
        void updateLine(std::vector<zombie*> zombies);
        // checks collisions and changes player state accordingly
        bool check_collisions(std::vector<zombie*> zombies, pickUp* item);
        // restores player to original state
        void restore_from_pickUp();

    private:

        int hp_;
        int speed_;
        QColor colours_[3];
        static const int width_ = 32;
        int gun_x_;
        int gun_y_;
        int gun_;
        currentPickUp current_;
        bool ai_;
        QLine* path_to_nearest_zombie_;

};

class zombie : public figure {

    Q_OBJECT

    public:
        //constructor
        zombie(int x, int y);

        //paint object manipulator
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
        // returns zombie speed
        int get_speed() const { return speed_; }
        // returns zombie hp
        int get_hp() const { return hp_; }
        // updates zombie path
        void updateLine(std::vector<player*> players);
        // changes hp
        bool change_hp(int hp);
        // changes speed
        void change_speed(int speed) { speed_ = speed; }
        // moves zombie
        void move();


    private:

        int hp_;
        int speed_;
        QLine* path_to_nearest_player_;
        QColor colours_[3];
        static const int width_ = 32;

};


#endif // FIGURE_H
