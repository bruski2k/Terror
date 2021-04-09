#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QTimer>
#include <QDebug>

#include "figure.h"
#include "gun.h"

// figure prototype constructor
figure::figure(int x, int y) {
    x_ = x;
    y_ = y;
    orientation_ = 2;
    setZValue(2);
}


// changes x coordinate of figure, hinders player to leave scene
void figure::change_x(int x, bool zombie) {
    prepareGeometryChange();
    if (!zombie){
        if (0 <= x && x <= 1768) {
            x_ = x;
        }
    }
    else {
        x_ = x;
    }
    update();
}

// changes y coordinate of figure, hinders player to leave scene
void figure::change_y(int y, bool zombie) {
    prepareGeometryChange();
    if (!zombie){
        if (0 <= y && y <= 768) {
            y_ = y;
        }
    }
    else {
        y_ = y;
    }
    update();
}

//paint object manipulators prototype
QRectF figure::boundingRect() const{
    return QRectF(get_x(), get_y(), get_width(), get_width());
}

// hitbox definition
QPainterPath figure::shape() const {
    QPainterPath path;
    QPolygon shape;
    shape << QPoint(get_x() + 8, get_y() + 8);
    shape << QPoint(get_x() + 24, get_y() + 8);
    shape << QPoint(get_x() + 24, get_y() + 12);
    shape << QPoint(get_x() + 32, get_y() + 12);
    shape << QPoint(get_x() + 32, get_y() + 20);
    shape << QPoint(get_x() + 24, get_y() + 20);
    shape << QPoint(get_x() + 24, get_y() + 24);
    shape << QPoint(get_x() + 8, get_y() + 24);
    shape << QPoint(get_x() + 8, get_y() + 20);
    shape << QPoint(get_x() + 0, get_y() + 20);
    shape << QPoint(get_x() + 0, get_y() + 12);
    shape << QPoint(get_x() + 8, get_y() + 12);
    shape << QPoint(get_x() + 8, get_y() + 8);
    path.addPolygon(shape);
    path.closeSubpath();
    return path;
}

// player constructor
player::player(int x, int y, bool ai, QColor q) : figure(x,y){

    hp_ = 100;
    speed_ = 6.0;
    colours_[0] = QColor(255,195,170);
    colours_[1] = q;
    colours_[2] = QColor(0,0,0);
    gun_ = 1;
    ai_ = ai;

    current_ = currentPickUp::none;
}


//paint object player
void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget)

    //shoulders
    painter->setBrush(colours_[1]);
    painter->drawRect(get_x() + 8, get_y() + 8, 16, 16);

    //hands
    painter->setBrush(colours_[0]);
    painter->drawRect(get_x(), get_y() + 12, 8, 8);
    painter->drawRect(get_x() + 24, get_y() + 12, 8, 8);


}

// updates gun position (hand orientation), this was thought to be good for when I make player models
void player::updateGunPosition() {
    switch(get_orientation()) {

        //facing west
        case 0:
            gun_x_ = get_x()-1;
            gun_y_ = get_y()+6;
            break;

        //facing north-west
        case 1:


        //facing north
        case 2:
            gun_x_ = get_x()+26;
            gun_y_ = get_y()-10;
            break;

        //facing north-east
        case 3:


        //facing east
        case 4:
            gun_x_ = get_x()+33;
            gun_y_ = get_y()+26;
            break;

        //facing south-east
        case 5:


        //facing south
        case 6:
            gun_x_ = get_x()+6;
            gun_y_ = get_y()+33;
            break;

        //facing south-west
        case 7:
            break;

    }
}

// updates path for cpu players
void player::updateLine(std::vector<zombie*> zombies){
    std::vector<QLine*> paths;
    for (int i = 0; i < zombies.size(); i++){
        int zombie_x = zombies[i]->get_x();
        int zombie_y = zombies[i]->get_y();
        if (paths.empty()){
            paths.push_back(new QLine(get_x(), get_y(), zombie_x, zombie_y));
        }
        else {
            QLine* current = new QLine(get_x(), get_y(), zombie_x, zombie_y);
            int current_length = sqrt(((zombie_y-get_y())*(zombie_y-get_y())) + ((zombie_x-get_x())*(zombie_x-get_x())));
            int shortest = sqrt((paths[0]->dy()*paths[0]->dy()) + (paths[0]->dx()*paths[0]->dx()));
            if (current_length <= shortest){
                paths.insert(paths.begin(), current);
            }
            else {
                paths.push_back(current);
            }
        }
    }
    if (paths.size() >= 2){
        if ((abs(paths[0]->dx()) <= abs(paths[1]->dx()) && (abs(paths[0]->dx()) >= abs(paths[1]->dx()-2)))
             || (abs(paths[0]->dy()) <= abs(paths[1]->dy()) && abs(paths[0]->dy()) <= abs(paths[1]->dy()-2))){
            int dir = rand() % 2;
            if (dir == 0){
                path_to_nearest_zombie_ = new QLine(get_x(), get_y(), -(get_y() - paths[0]->dy()), get_x() - paths[0]->dx());
            }
            else {
                path_to_nearest_zombie_ = new QLine(get_x(), get_y(), (get_y() - paths[0]->dy()), -(get_x() - paths[0]->dx()));
            }
            return;
        }
    }
    path_to_nearest_zombie_ = paths[0];
}

// checks collisions and changes player state accordingly
bool player::check_collisions(std::vector<zombie *> zombies, pickUp* item){
    bool zombie = false;
    for (int i = 0; i < zombies.size(); i++){
        if (collidesWithItem(zombies[i])){
            zombie = true;
        }
    }
    if (zombie && current_ != currentPickUp::invincibility ){
        hp_ -= 1;
    }
    if (item != nullptr){
        if (collidesWithItem(item)){
            if (item->get_pickUp() == currentPickUp::healUp){
                hp_ += 50;
                if (hp_ > 100){
                    hp_ = 100;
                }
                current_ = currentPickUp::healUp;
            }
            if (item->get_pickUp() == currentPickUp::speedUp){
                speed_ = 20;
                current_ = currentPickUp::speedUp;
            }
            if (item->get_pickUp() == currentPickUp::invincibility){
                current_ = currentPickUp::invincibility;
            }
            return true;
        }
    }
    return false;
}


// restores player to original state
void player::restore_from_pickUp(){
    speed_ = 6;
    current_ = currentPickUp::none;
}


// moves cpu player
void player::move_ai(){
    prepareGeometryChange();
    int dx = path_to_nearest_zombie_->dx();
    int dy = path_to_nearest_zombie_->dy();
    if (dx < 0 && dy < 0){
        if (abs(dx) > abs(dy)){
            change_orientation(4);
        }
        if (abs(dx) < abs(dy)){
            change_orientation(6);
        }
        if (abs(dx) == abs(dy)){
            change_orientation(5);
        }
    }
    if (dx < 0 && dy > 0){
        if (abs(dx) > abs(dy)){
            change_orientation(4);
        }
        if (abs(dx) < abs(dy)){
            change_orientation(2);
        }
        if (abs(dx) == abs(dy)){
            change_orientation(3);
        }
    }
    if (dx > 0 && dy > 0){
        if (abs(dx) > abs(dy)){
            change_orientation(0);
        }
        if (abs(dx) < abs(dy)){
            change_orientation(2);
        }
        if (abs(dx) == abs(dy)){
            change_orientation(1);
        }
    }
    if (dx > 0 && dy < 0){
        if (abs(dx) > abs(dy)){
            change_orientation(0);
        }
        if (abs(dx) < abs(dy)){
            change_orientation(6);
        }
        if (abs(dx) == abs(dy)){
            change_orientation(7);
        }
    }

    double dis = sqrt((dx*dx) + (dy*dy));
    double perce = ((double)(speed_))/dis;
    change_x(get_x() - (int)(perce*dx), false);
    change_y(get_y() - (int)(perce*dy), false);
    update();
}

// zombies constructor
zombie::zombie(int x, int y) : figure(x,y){

    hp_ = 100;
    speed_ = 3.0;
    colours_[0] = QColor(220,220,220);
    colours_[1] = QColor(150,150,255);
}


//paint object player
void zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path;
    QPolygon shape;

    Q_UNUSED(widget)

    //shoulders
    painter->setBrush(colours_[1]);
    painter->drawRect(get_x() + 8, get_y() + 8, 16, 16);

    //hands
    painter->setBrush(colours_[0]);
    painter->drawRect(get_x(), get_y() + 12, 8, 8);
    painter->drawRect(get_x() + 24, get_y() + 12, 8, 8);

}

// updates zombie path
void zombie::updateLine(std::vector<player*> players){
    std::vector<QLine*> paths;
    if (players.size() > 0){
        for (int i = 0; i < players.size(); i++){
            int player_x = players[i]->get_x();
            int player_y = players[i]->get_y();
            if (paths.empty()){
                paths.push_back(new QLine(get_x(), get_y(), player_x, player_y));
            }
            else {
                QLine* current = new QLine(get_x(), get_y(), player_x, player_y);
                double current_length = sqrt(((player_y-get_y())*(player_y-get_y())) + ((player_x-get_x())*(player_x-get_x())));
                double shortest = sqrt((paths[0]->dy()*paths[0]->dy()) + (paths[0]->dx()*paths[0]->dx()));
                if (current_length <= shortest){
                    paths.insert(paths.begin(), current);
                }
                else {
                    paths.push_back(current);
                }
            }
        }
        path_to_nearest_player_ = paths[0];
    }
}

// changes hp
bool zombie::change_hp(int hp){
    hp_ = hp;
    if (hp_ <= 0){
        return true;
    }
    return false;
}


// moves zombie
void zombie::move(){
    prepareGeometryChange();
    if (path_to_nearest_player_ != nullptr){
        int dx = path_to_nearest_player_->dx();
        int dy = path_to_nearest_player_->dy();

        double dis = sqrt((dx*dx) + (dy*dy));
        double perce = ((double)(speed_))/dis;
        change_x(get_x() + (int)(perce*dx), true);
        change_y(get_y() + (int)(perce*dy), true);
    }
    update();
}
