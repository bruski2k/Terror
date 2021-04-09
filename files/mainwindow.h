#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QMainWindow>
#include <vector>

#include "figure.h"
#include "gun.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


// main window header
class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    // timer and button slots
    private slots:
        // play button on title screen clicked
        void on_playButton_clicked();
        // no playerbutton (ai) in main menu clicked
        void on_noPlayerButton_clicked();
        // one player button in main menu clicked
        void on_onePlayerButton_clicked();
        // two player button in main menu clicked
        void on_twoPlayerButton_clicked();
        // timer for player movement
        void mcTimerPlayer();
        // this is the game tick rate timer
        void mcTimerBullet();
        // explanation button in main menu clicked
        void on_Explanation_clicked();
        // 10 simulation button in main menu clicked
        void on_simuButton_clicked();
        // main menu button in results screen clicked
        void on_resultsMainMenu_clicked();
        // main menu button in pause screen clicked
        void on_pauseMainMenu_clicked();
        // game screen button in pause menu clicked
        void on_pauseToGame_clicked();
        // pause button in game screen clicked
         void on_pauseButton_clicked();

    // private functions and game variables
    private:
        // spawns zombie randomnly just outside scene
        void spawnZombie();
        // spawns item randomly
        void spawnPickUp();
        // // I add keys to a map with a corresponding truth value, this allows me to press multiple keys simultaneously
        // adds key to map if pressed, and gives it true value
        void keyPressEvent(QKeyEvent *event);
        // gives false value in map, when key is released
        void keyReleaseEvent(QKeyEvent *event);
        // preps new game
        void newGame();
        // updates endgame chart with new results
        void updateChart();
        // resets game screen to a simulation of two cpu players
        void simulation();

        Ui::MainWindow *ui;
        QGraphicsScene *sceneArena;
        std::vector<player *> players_;
        std::vector<zombie *> zombies_;
        std::vector<pistol *> pistol_bullets_;
        std::vector<ak *> ak_bullets_;
        std::vector<int> scores_;
        pickUp* item_;
        int cd_pistol1_ = 0;
        int cd_pistol2_ = 0;
        double cd_ak1_ = 0;
        double cd_ak2_ = 0;
        int cd_railgun1_ = 0;
        int cd_railgun2_ = 0;
        int cd_zombie_spawn_ = 1;
        int cd_pickup_spawn_ = 0;
        railgun* rgbeam1_;
        railgun* rgbeam2_;
        QTimer* timer_player_= nullptr;
        QTimer* timer_bullet_= nullptr;
        QMap<int, bool> keys_;
        int ticks_;
        int score_;
        int games_;
        player* player1;
        player* player2;
        bool simulation_ = false;
        int sim_run_ = 0;
        int cd_weapon_change1_ = 100;
        int cd_weapon_change2_ = 100;

};
#endif // MAINWINDOW_H
