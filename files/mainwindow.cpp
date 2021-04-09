#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QLine>

#include "mainwindow.h"
#include "ui_mainwindow.h"


// main window constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFocusPolicy(Qt::StrongFocus);
    rgbeam1_ = nullptr;
    rgbeam2_ = nullptr;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    sceneArena = new QGraphicsScene;
    QGraphicsView* arenaView = ui->graphicsViewArena;
    arenaView->setScene(sceneArena);
    QRect rcontent_grid = arenaView->contentsRect();
    arenaView->setSceneRect(0, 0, rcontent_grid.width(), rcontent_grid.height());
    item_ = nullptr;
    player1 = nullptr;
    player2 = nullptr;
    ticks_ = 0;
    score_ = 0;
}

// main window desctructor
MainWindow::~MainWindow(){
    delete ui;
}

// play button on title screen clicked
void MainWindow::on_playButton_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}

// no playerbutton (ai) in main menu clicked
void MainWindow::on_noPlayerButton_clicked(){
    simulation();
}

// one player button in main menu clicked
void MainWindow::on_onePlayerButton_clicked(){
    newGame();
    player1 = new player(884, 384, false, QColor(255,0,0));
    players_.push_back(player1);
    sceneArena->addItem(player1);
    ui->stackedWidget->setCurrentIndex(3);
    timer_player_ = new QTimer(this);
    timer_player_->start(1000/50);
    timer_bullet_ = new QTimer(this);
    timer_bullet_->start(10);
    connect(timer_player_, SIGNAL(timeout()), this, SLOT(mcTimerPlayer()));
    connect(timer_bullet_, SIGNAL(timeout()), this, SLOT(mcTimerBullet()));

}

// two player button in main menu clicked
void MainWindow::on_twoPlayerButton_clicked(){
    newGame();
    player1 = new player(1184, 384, false, QColor(255,0,0));
    player2 = new player(584, 384, false, QColor(0,0,255));
    sceneArena->addItem(player1);
    sceneArena->addItem(player2);
    players_.push_back(player1);
    players_.push_back(player2);
    ui->stackedWidget->setCurrentIndex(3);
    timer_player_ = new QTimer(this);
    timer_player_->start(1000/50);
    timer_bullet_ = new QTimer(this);
    timer_bullet_->start(10);
    connect(timer_player_, SIGNAL(timeout()), this, SLOT(mcTimerPlayer()));
    connect(timer_bullet_, SIGNAL(timeout()), this, SLOT(mcTimerBullet()));
}

// explanation button in main menu clicked
void MainWindow::on_Explanation_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

// 10 simulation button in main menu clicked
void MainWindow::on_simuButton_clicked(){
    simulation_ = true;
    sim_run_ = 0;
    simulation();
}

// main menu button in results screen clicked
void MainWindow::on_resultsMainMenu_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

// main menu button in pause screen clicked
void MainWindow::on_pauseMainMenu_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}

// game screen button in pause menu clicked
void MainWindow::on_pauseToGame_clicked(){
    if (timer_bullet_ != nullptr && timer_player_ != nullptr){
        timer_player_->start(1000/50);
        timer_bullet_->start(10);
         ui->stackedWidget->setCurrentIndex(3);
    }
}

// pause button in game screen clicked
void MainWindow::on_pauseButton_clicked(){
    timer_bullet_->stop();
    timer_player_->stop();
    ui->stackedWidget->setCurrentIndex(2);
}

// // I add keys to a map with a corresponding truth value, this allows me to press multiple keys simultaneously
// adds key to map if pressed, and gives it true value
void MainWindow::keyPressEvent(QKeyEvent *event) {
    keys_[event->key()] = true;
    QWidget::keyPressEvent(event);
}


// gives false value in map, when key is released
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    keys_[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}

// preps new game
void MainWindow::newGame(){
    sceneArena->clear();
    score_ = 0;
    ticks_ = 0;
    cd_pistol1_ = 0;
    cd_pistol2_ = 0;
    cd_ak1_ = 0;
    cd_ak2_ = 0;
    cd_railgun1_ = 0;
    cd_railgun2_ = 0;
    cd_zombie_spawn_ = 0;
    cd_pickup_spawn_ = 0;
    players_.clear();
    zombies_.clear();
    pistol_bullets_.clear();
    ak_bullets_.clear();

}

// updates endgame chart with new results
void MainWindow::updateChart(){
    for (int i = 0; i < scores_.size(); i++){
        QString lcd = "game" + QString::number(i+1) + "lcd";
        qDebug() << lcd;
        ui->page_5->findChild<QLCDNumber*>(lcd)->display(scores_[i]);
    }
}

// resets game screen to a simulation of two cpu players
void MainWindow::simulation(){
    newGame();
    spawnZombie();
    player1 = new player(1184, 384, true, QColor(0,255,0));
    player2 = new player(584, 384, true, QColor(0,255,0));
    sceneArena->addItem(player1);
    sceneArena->addItem(player2);
    players_.push_back(player1);
    players_.push_back(player2);
    ui->stackedWidget->setCurrentIndex(3);
    timer_player_ = new QTimer(this);
    timer_player_->start(1000/50);
    timer_bullet_ = new QTimer(this);
    timer_bullet_->start(10);
    connect(timer_player_, SIGNAL(timeout()), this, SLOT(mcTimerPlayer()));
    connect(timer_bullet_, SIGNAL(timeout()), this, SLOT(mcTimerBullet()));
}

// timer for player movement
void MainWindow::mcTimerPlayer(){
    // spawns item every 30 seconds
    if (cd_pickup_spawn_ == 1500 && item_ == nullptr){
        spawnPickUp();
    }
    //restores player state after 7.5 seconds
    if (cd_pickup_spawn_ == 350){
        for (int i = 0; i < players_.size(); i++){
            players_[i]->restore_from_pickUp();
        }
    }
    // checks player collisions
    for (int i = 0; i < players_.size(); i++){
        if (players_[i]->check_collisions(zombies_, item_)){
            sceneArena->removeItem(item_);
            item_ = nullptr;
            cd_pickup_spawn_ = 1;
        }
    }
    // item cooldown
    if (cd_pickup_spawn_ < 1500){
        cd_pickup_spawn_++;
    }
    // updates zombie path
    for (int i = 0; i < zombies_.size(); i++){
        zombies_[i]->updateLine(players_);
        zombies_[i]->move();
    }

    // this if statement reacts to key presses and move human players
    // if players are not human it moves and updates paths for cpu
    if (player1 != nullptr || player2 != nullptr){
        ui->page_4->findChild<QLCDNumber*>("scoreNumber")->display(score_);
        if (player1 != nullptr){
            ui->page_4->findChild<QProgressBar*>("hpBarPlayer1")->setValue(player1->get_hp());
            int speed1 = player1->get_speed();
            if (!player1->get_ai()){
                if (keys_[Qt::Key_L]){
                    player1->change_x(players_[0]->get_x() - speed1, false);
                    player1->change_orientation(0);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_Apostrophe]){
                    player1->change_x(players_[0]->get_x() + speed1, false);
                    player1->change_orientation(4);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_P]){
                    player1->change_y(players_[0]->get_y() - speed1, false);
                    player1->change_orientation(2);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_Semicolon]){
                    player1->change_y(players_[0]->get_y() + speed1, false);
                    player1->change_orientation(6);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_L] && keys_[Qt::Key_P]){
                    player1->change_orientation(1);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_Semicolon] && keys_[Qt::Key_Apostrophe]){
                    player1->change_orientation(5);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_L] && keys_[Qt::Key_Semicolon]){
                    player1->change_orientation(7);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_P] && keys_[Qt::Key_Apostrophe]){
                    player1->change_orientation(3);
                    player1->updateGunPosition();
                }
                if (keys_[Qt::Key_Comma]){
                    int o = player1->get_orientation();
                    int x = player1->get_gun_x();
                    int y = player1->get_gun_y();
                    pistol* pistolshot = new pistol(x, y, o, QColor(100,100,100));
                    ak* akshot = new ak(x, y, o, QColor(100,70,70));
                    railgun* rgshot = new railgun(x, y, o, QColor(255,0,0));
                    switch (player1->get_gun()){

                    case 0:
                        if (cd_pistol1_ >= pistolshot->get_rate()){
                            sceneArena->addItem(pistolshot);
                            pistol_bullets_.push_back(pistolshot);
                            cd_pistol1_ = 0;
                            delete akshot;
                            delete rgshot;
                        }
                        break;

                    case 1:
                        if (cd_ak1_ >= akshot->get_rate()){
                            sceneArena->addItem(akshot);
                            ak_bullets_.push_back(akshot);
                            cd_ak1_ = 0;
                            delete pistolshot;
                            delete rgshot;
                        }
                        break;

                    case 2:
                        if (cd_railgun1_ >= rgshot->get_rate()){
                            rgbeam1_ = rgshot;
                            sceneArena->addItem(rgshot);
                            cd_railgun1_ = 0;
                            delete pistolshot;
                            delete akshot;
                        }
                        break;

                    }
                }
                if(keys_[Qt::Key_M] && cd_weapon_change1_ >= 100){
                    player1->change_gun_forwards();
                    cd_weapon_change1_ = 0;
                }
                if(keys_[Qt::Key_N] && cd_weapon_change1_ >= 100){
                    player1->change_gun_backwards();
                    cd_weapon_change1_ = 0;
                }
            }
            else {
                player1->updateLine(zombies_);
                player1->updateGunPosition();
                int o = player1->get_orientation();
                int x = player1->get_gun_x();
                int y = player1->get_gun_y();
                pistol* pistolshot = new pistol(x, y, o, QColor(100,100,100));
                ak* akshot = new ak(x, y, o, QColor(100,70,70));
                railgun* rgshot = new railgun(x, y, o, QColor(255,0,0));
                switch (player1->get_gun()){

                case 0:
                    if (cd_pistol1_ >= pistolshot->get_rate()){
                        sceneArena->addItem(pistolshot);
                        pistol_bullets_.push_back(pistolshot);
                        cd_pistol1_ = 0;
                        delete akshot;
                        delete rgshot;
                    }
                    break;

                case 1:
                    if (cd_ak1_ >= akshot->get_rate()){
                        sceneArena->addItem(akshot);
                        ak_bullets_.push_back(akshot);
                        cd_ak1_ = 0;
                        delete pistolshot;
                        delete rgshot;
                    }
                    break;

                case 2:
                    if (cd_railgun1_ >= rgshot->get_rate()){
                        rgbeam1_ = rgshot;
                        sceneArena->addItem(rgshot);
                        cd_railgun1_ = 0;
                        delete pistolshot;
                        delete akshot;
                    }
                    break;
                }
                player1->move_ai();
            }
        }

        if (player2 != nullptr){
            ui->page_4->findChild<QProgressBar*>("hpBarPlayer2")->setValue(player2->get_hp());
            int speed2 = player2->get_speed();
            if (!player2->get_ai()){
                if (keys_[Qt::Key_F]){
                    player2->change_x(players_[1]->get_x() - speed2, false);
                    player2->change_orientation(0);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_H]){
                    player2->change_x(players_[1]->get_x() + speed2, false);
                    player2->change_orientation(4);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_T]){
                    player2->change_y(players_[1]->get_y() - speed2, false);
                    player2->change_orientation(2);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_G]){
                    player2->change_y(players_[1]->get_y() + speed2, false);
                    player2->change_orientation(6);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_F] && keys_[Qt::Key_T]){
                    player2->change_orientation(1);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_G] && keys_[Qt::Key_H]){
                    player2->change_orientation(5);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_F] && keys_[Qt::Key_G]){
                    player2->change_orientation(7);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_T] && keys_[Qt::Key_H]){
                    player2->change_orientation(3);
                    player2->updateGunPosition();
                }
                if (keys_[Qt::Key_C]){
                    int o = player2->get_orientation();
                    int x = player2->get_gun_x();
                    int y = player2->get_gun_y();

                    pistol* pistolshot = new pistol(x, y, o, QColor(100,100,100));
                    ak* akshot = new ak(x, y, o, QColor(100,70,70));
                    railgun* rgshot = new railgun(x, y, o, QColor(255,0,0));

                    switch (player2->get_gun()){

                        case 0:
                            if (cd_pistol2_ >= pistolshot->get_rate()){
                                sceneArena->addItem(pistolshot);
                                pistol_bullets_.push_back(pistolshot);
                                cd_pistol2_ = 0;
                                delete akshot;
                                delete rgshot;
                            }
                            break;

                        case 1:
                            if (cd_ak2_ >= akshot->get_rate()){
                                sceneArena->addItem(akshot);
                                ak_bullets_.push_back(akshot);
                                cd_ak2_ = 0;
                                delete pistolshot;
                                delete rgshot;
                            }
                                break;

                        case 2:
                            if (cd_railgun2_ >= rgshot->get_rate()){
                                rgbeam2_ = rgshot;
                                sceneArena->addItem(rgshot);
                                cd_railgun2_ = 0;
                                delete pistolshot;
                                delete akshot;
                            }
                            break;
                    }
                }
                if(keys_[Qt::Key_X] && cd_weapon_change2_ >= 100){
                    player2->change_gun_forwards();
                    cd_weapon_change2_ = 0;
                }
                if(keys_[Qt::Key_Z] && cd_weapon_change2_ >= 100){
                    player2->change_gun_backwards();
                    cd_weapon_change2_ = 0;
                }
            }
            else {
                player2->updateLine(zombies_);
                player2->updateGunPosition();
                int o = player2->get_orientation();
                int x = player2->get_gun_x();
                int y = player2->get_gun_y();

                pistol* pistolshot = new pistol(x, y, o, QColor(100,100,100));
                ak* akshot = new ak(x, y, o, QColor(100,70,70));
                railgun* rgshot = new railgun(x, y, o, QColor(255,0,0));
                switch (player2->get_gun()){

                    case 0:
                        if (cd_pistol2_ >= pistolshot->get_rate()){
                            sceneArena->addItem(pistolshot);
                            pistol_bullets_.push_back(pistolshot);
                            cd_pistol2_ = 0;
                            delete akshot;
                            delete rgshot;
                        }
                        break;

                    case 1:
                        if (cd_ak2_ >= akshot->get_rate()){
                            sceneArena->addItem(akshot);
                            ak_bullets_.push_back(akshot);
                            cd_ak2_ = 0;
                            delete pistolshot;
                            delete rgshot;
                        }
                        break;

                    case 2:
                        if (cd_railgun2_ >= rgshot->get_rate()){
                            rgbeam2_ = rgshot;
                            sceneArena->addItem(rgshot);
                            cd_railgun2_ = 0;
                            delete pistolshot;
                            delete akshot;
                        }
                        break;
                }
                player2->move_ai();
            }
        }
        else {
            ui->page_4->findChild<QProgressBar*>("hpBarPlayer2")->setValue(0);
        }
    }
    // cautionary scene redraw
    sceneArena->update(0,0,1800,800);
}

// this is the game tick rate timer
void MainWindow::mcTimerBullet() {
    // spawns zombies
    if (cd_zombie_spawn_ % 100 == 0){
        spawnZombie();
    }

    // vectors that will hold QGraphicItems to be deleted this tick
    std::vector<zombie *> zo_to_erase;
    std::vector<int> pi_to_erase;
    std::vector<pistol*> pi_bullets_to_erase;
    std::vector<int> ak_to_erase;
    std::vector<ak*> ak_bullets_to_erase;

    // moves and checks collisions of all pistol bullets
    for (int i = 0; i < pistol_bullets_.size(); i++){
        if (pistol_bullets_[i]->move()){
            pi_bullets_to_erase.push_back(pistol_bullets_[i]);
            pi_to_erase.push_back(i);
        }
        if (pistol_bullets_[i]->check_collisions(zombies_, zo_to_erase)){
            pi_bullets_to_erase.push_back(pistol_bullets_[i]);
            pi_to_erase.push_back(i);
        }
    }

    // removes all pistol bullets that hit
    for (int i = 0; i < pi_to_erase.size(); i++){
        sceneArena->removeItem(pi_bullets_to_erase[i]);
        pistol_bullets_[pi_to_erase[i]] = nullptr;

    }
    pistol_bullets_.erase(std::remove(pistol_bullets_.begin(), pistol_bullets_.end(), nullptr), pistol_bullets_.end());

    // moves and checks collisions of all ak bullets
    for (int i = 0; i < ak_bullets_.size(); i++){
        if (ak_bullets_[i]->move()){
            ak_bullets_to_erase.push_back(ak_bullets_[i]);
            ak_to_erase.push_back(i);
        }

        if (ak_bullets_[i]->check_collisions(zombies_, zo_to_erase)){
            ak_bullets_to_erase.push_back(ak_bullets_[i]);
            ak_to_erase.push_back(i);
        }
    }

    // removes all ak bullets that hit
    for (int i = 0; i < ak_to_erase.size(); i++){
        sceneArena->removeItem(ak_bullets_to_erase[i]);
        ak_bullets_[ak_to_erase[i]] = nullptr;
    }
    ak_bullets_.erase(std::remove(ak_bullets_.begin(), ak_bullets_.end(), nullptr), ak_bullets_.end());


    // checks collisions of rail gun beams
    if (rgbeam1_ != nullptr && cd_railgun1_ >= 12){
        rgbeam1_->check_collisions(zombies_, zo_to_erase);
        sceneArena->removeItem(rgbeam1_);
        rgbeam1_ = nullptr;
    }
    if (rgbeam2_ != nullptr && cd_railgun2_ >= 12){
        rgbeam2_->check_collisions(zombies_, zo_to_erase);
        sceneArena->removeItem(rgbeam2_);
        rgbeam2_ = nullptr;
    }

    // deletes all zombies that hit 0 hp this tick
    if (zo_to_erase.size() != 0){
        for(int i = 0; i < zo_to_erase.size(); i++){
            sceneArena->removeItem(zo_to_erase[i]);
            score_ += 100;
            std::vector<zombie *>::iterator it;
            it = std::find(zombies_.begin(), zombies_.end(), zo_to_erase[i]);
            zombies_[std::distance(zombies_.begin(), it)] = nullptr;
        }
        zombies_.erase(std::remove(zombies_.begin(), zombies_.end(), nullptr), zombies_.end());
    }

    // tick advance of all cooldown timers
    cd_pistol1_++;
    cd_pistol2_++;
    cd_ak1_ += 0.3;
    cd_ak2_ += 0.3;
    cd_railgun1_++;
    cd_railgun2_++;
    cd_weapon_change1_++;
    cd_weapon_change2_++;
    cd_zombie_spawn_++;
    ticks_ += 1;

    // removes players if 0 is hit
    for (int i = 0; i < players_.size(); i++){
        if (players_[i]->get_hp() <= 0){
            sceneArena->removeItem(players_[i]);
            players_[i] = nullptr;
        }
        else {
            players_[i]->update();
        }
    }
    players_.erase(std::remove(players_.begin(), players_.end(), nullptr), players_.end());

    // updates paths for zombies and updates them on the scene precautionary, could probably be deleted
    // but I had problems at one point
    for (int i = 0; i < zombies_.size(); i++){
        zombies_[i]->updateLine(players_);
        zombies_[i]->update();
    }

    // adds score every 100ms
    if (ticks_ % 10 == 0){
        score_ += 1;
    }

    // if all players are dead checks for end game conditions
    if (players_.size() == 0){
        timer_bullet_->stop();
        timer_player_->stop();
        if (scores_.size() < 10){
            scores_.insert(scores_.begin(), 1, score_);
        }
        else {
            scores_.erase(scores_.begin());
            scores_.push_back(score_);
        }
        if (simulation_ && sim_run_ < 10){
            qDebug() << "hey";
            simulation();
            sim_run_++;
        }
        else if (sim_run_ == 10){
            simulation_ = false;
            updateChart();
            ui->stackedWidget->setCurrentIndex(4);
        }
        else {
            simulation_ = false;
            updateChart();
            ui->stackedWidget->setCurrentIndex(4);
        }
    }

    // calls pause screen if escape is pressed
    if (keys_[Qt::Key_Escape]){
        timer_bullet_->stop();
        timer_player_->stop();
        ui->stackedWidget->setCurrentIndex(2);
    }
}

// spawns zombie randomnly just outside scene
void MainWindow::spawnZombie() {
    int side = rand() % 4;
    int x;
    int y;
    if (side == 0){
        x = -33;
        y = rand() % 800 + 1;
    }
    else if (side == 1){
        x = 1801;
        y = rand() % 800 + 1;
    }
    else if (side == 2){
        x = rand() % 1800 + 1;
        y = -33;
    }
    else {
        x = rand() % 1800 + 1;
        y = 801;
    }
    zombie* zom = new zombie(x, y);
    sceneArena->addItem(zom);
    zombies_.push_back(zom);
}

// spawns item randomly
void MainWindow::spawnPickUp(){

    int x;
    int y;
    int p;

    x = rand() % 1777;
    y = rand() % 877;
    p = rand() % 3;

    if (p == 0){
        pickUp* item = new pickUp(x, y, currentPickUp::speedUp, QColor(255,255,0));
        sceneArena->addItem(item);
        item_ = item;
    }
    else if (p == 1){
        pickUp* item = new pickUp(x, y, currentPickUp::healUp, QColor(0,255,0));
        sceneArena->addItem(item);
        item_ = item;
    }
    else {
        pickUp* item = new pickUp(x, y, currentPickUp::invincibility, QColor(0,0,255));
        sceneArena->addItem(item);
        item_ = item;
    }
}



