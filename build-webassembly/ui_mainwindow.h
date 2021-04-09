/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *TerrorSplash;
    QPushButton *playButton;
    QWidget *page_2;
    QPushButton *onePlayerButton;
    QPushButton *noPlayerButton;
    QPushButton *twoPlayerButton;
    QPushButton *simuButton;
    QPushButton *Explanation;
    QWidget *page_3;
    QLabel *label_3;
    QLabel *label_20;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QPushButton *pauseMainMenu;
    QPushButton *pauseToGame;
    QWidget *page_4;
    QGraphicsView *graphicsViewArena;
    QLCDNumber *scoreNumber;
    QPushButton *pauseButton;
    QProgressBar *hpBarPlayer1;
    QProgressBar *hpBarPlayer2;
    QWidget *page_5;
    QLCDNumber *game1lcd;
    QLCDNumber *game3lcd;
    QLCDNumber *game4lcd;
    QLCDNumber *game5lcd;
    QLCDNumber *game6lcd;
    QLCDNumber *game7lcd;
    QLCDNumber *game8lcd;
    QLCDNumber *game9lcd;
    QLCDNumber *game10lcd;
    QLCDNumber *game2lcd;
    QPushButton *resultsMainMenu;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1920, 1080));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        TerrorSplash = new QLabel(page);
        TerrorSplash->setObjectName(QString::fromUtf8("TerrorSplash"));
        TerrorSplash->setGeometry(QRect(480, -70, 1100, 910));
        TerrorSplash->setPixmap(QPixmap(QString::fromUtf8("Terror.png")));
        playButton = new QPushButton(page);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(790, 810, 340, 130));
        playButton->setIconSize(QSize(32, 32));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        onePlayerButton = new QPushButton(page_2);
        onePlayerButton->setObjectName(QString::fromUtf8("onePlayerButton"));
        onePlayerButton->setGeometry(QRect(810, 430, 300, 170));
        noPlayerButton = new QPushButton(page_2);
        noPlayerButton->setObjectName(QString::fromUtf8("noPlayerButton"));
        noPlayerButton->setGeometry(QRect(330, 430, 300, 170));
        twoPlayerButton = new QPushButton(page_2);
        twoPlayerButton->setObjectName(QString::fromUtf8("twoPlayerButton"));
        twoPlayerButton->setGeometry(QRect(1290, 430, 300, 170));
        simuButton = new QPushButton(page_2);
        simuButton->setObjectName(QString::fromUtf8("simuButton"));
        simuButton->setGeometry(QRect(570, 710, 300, 170));
        Explanation = new QPushButton(page_2);
        Explanation->setObjectName(QString::fromUtf8("Explanation"));
        Explanation->setGeometry(QRect(1050, 710, 300, 170));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label_3 = new QLabel(page_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(230, 170, 111, 61));
        label_20 = new QLabel(page_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(700, 80, 531, 111));
        label_7 = new QLabel(page_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(230, 240, 111, 61));
        label_8 = new QLabel(page_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(230, 380, 111, 61));
        label_9 = new QLabel(page_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(230, 310, 111, 61));
        label_10 = new QLabel(page_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(230, 450, 111, 61));
        label_11 = new QLabel(page_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(230, 520, 111, 61));
        label_12 = new QLabel(page_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(230, 590, 111, 61));
        label_13 = new QLabel(page_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(280, 90, 111, 61));
        label_14 = new QLabel(page_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(1530, 90, 111, 61));
        label_15 = new QLabel(page_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(1490, 170, 111, 61));
        label_16 = new QLabel(page_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1490, 230, 111, 61));
        label_17 = new QLabel(page_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(1490, 360, 111, 61));
        label_18 = new QLabel(page_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(1490, 290, 111, 61));
        label_19 = new QLabel(page_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(1490, 420, 111, 61));
        label_21 = new QLabel(page_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(1490, 490, 111, 61));
        label_22 = new QLabel(page_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(1490, 560, 111, 61));
        label_33 = new QLabel(page_3);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(840, 270, 261, 61));
        label_34 = new QLabel(page_3);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(840, 370, 251, 61));
        label_35 = new QLabel(page_3);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(840, 480, 251, 61));
        label_36 = new QLabel(page_3);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(840, 190, 261, 61));
        pauseMainMenu = new QPushButton(page_3);
        pauseMainMenu->setObjectName(QString::fromUtf8("pauseMainMenu"));
        pauseMainMenu->setGeometry(QRect(680, 760, 231, 121));
        pauseToGame = new QPushButton(page_3);
        pauseToGame->setObjectName(QString::fromUtf8("pauseToGame"));
        pauseToGame->setGeometry(QRect(1050, 760, 231, 121));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        graphicsViewArena = new QGraphicsView(page_4);
        graphicsViewArena->setObjectName(QString::fromUtf8("graphicsViewArena"));
        graphicsViewArena->setGeometry(QRect(60, 10, 1800, 800));
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsViewArena->setBackgroundBrush(brush);
        scoreNumber = new QLCDNumber(page_4);
        scoreNumber->setObjectName(QString::fromUtf8("scoreNumber"));
        scoreNumber->setGeometry(QRect(740, 820, 440, 60));
        pauseButton = new QPushButton(page_4);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setGeometry(QRect(870, 920, 180, 71));
        hpBarPlayer1 = new QProgressBar(page_4);
        hpBarPlayer1->setObjectName(QString::fromUtf8("hpBarPlayer1"));
        hpBarPlayer1->setGeometry(QRect(60, 830, 220, 40));
        hpBarPlayer1->setValue(23);
        hpBarPlayer2 = new QProgressBar(page_4);
        hpBarPlayer2->setObjectName(QString::fromUtf8("hpBarPlayer2"));
        hpBarPlayer2->setGeometry(QRect(1640, 830, 220, 40));
        hpBarPlayer2->setValue(24);
        stackedWidget->addWidget(page_4);
        graphicsViewArena->raise();
        scoreNumber->raise();
        hpBarPlayer1->raise();
        hpBarPlayer2->raise();
        pauseButton->raise();
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        game1lcd = new QLCDNumber(page_5);
        game1lcd->setObjectName(QString::fromUtf8("game1lcd"));
        game1lcd->setGeometry(QRect(980, 70, 170, 58));
        game3lcd = new QLCDNumber(page_5);
        game3lcd->setObjectName(QString::fromUtf8("game3lcd"));
        game3lcd->setGeometry(QRect(980, 258, 170, 58));
        game4lcd = new QLCDNumber(page_5);
        game4lcd->setObjectName(QString::fromUtf8("game4lcd"));
        game4lcd->setGeometry(QRect(980, 352, 170, 58));
        game5lcd = new QLCDNumber(page_5);
        game5lcd->setObjectName(QString::fromUtf8("game5lcd"));
        game5lcd->setGeometry(QRect(980, 446, 170, 58));
        game6lcd = new QLCDNumber(page_5);
        game6lcd->setObjectName(QString::fromUtf8("game6lcd"));
        game6lcd->setGeometry(QRect(980, 540, 170, 58));
        game7lcd = new QLCDNumber(page_5);
        game7lcd->setObjectName(QString::fromUtf8("game7lcd"));
        game7lcd->setGeometry(QRect(980, 634, 170, 58));
        game8lcd = new QLCDNumber(page_5);
        game8lcd->setObjectName(QString::fromUtf8("game8lcd"));
        game8lcd->setGeometry(QRect(980, 728, 170, 58));
        game9lcd = new QLCDNumber(page_5);
        game9lcd->setObjectName(QString::fromUtf8("game9lcd"));
        game9lcd->setGeometry(QRect(980, 822, 170, 58));
        game10lcd = new QLCDNumber(page_5);
        game10lcd->setObjectName(QString::fromUtf8("game10lcd"));
        game10lcd->setGeometry(QRect(980, 916, 170, 58));
        game2lcd = new QLCDNumber(page_5);
        game2lcd->setObjectName(QString::fromUtf8("game2lcd"));
        game2lcd->setGeometry(QRect(980, 164, 170, 58));
        resultsMainMenu = new QPushButton(page_5);
        resultsMainMenu->setObjectName(QString::fromUtf8("resultsMainMenu"));
        resultsMainMenu->setGeometry(QRect(1180, 20, 721, 1011));
        label = new QLabel(page_5);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(519, 70, 351, 58));
        label_2 = new QLabel(page_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(700, 916, 170, 58));
        stackedWidget->addWidget(page_5);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        TerrorSplash->setText(QString());
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        onePlayerButton->setText(QCoreApplication::translate("MainWindow", "One Player", nullptr));
        noPlayerButton->setText(QCoreApplication::translate("MainWindow", "No Players", nullptr));
        twoPlayerButton->setText(QCoreApplication::translate("MainWindow", "Two Players", nullptr));
        simuButton->setText(QCoreApplication::translate("MainWindow", "CPU 10 Simulation Run", nullptr));
        Explanation->setText(QCoreApplication::translate("MainWindow", "Game Explanation", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Left : L", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Objective : Survive and kill as many zombies as you can. Your teammate and you work together.", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Right : ' (apostrophe)", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Up : P", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Down : ' (semi-colon)", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Shoot : , (comma)", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Change gun back : N", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Change gun front : M", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Player 1", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Player 2", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Left : F", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Right : H", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Up : T", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Down : G", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Shoot : C", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Change gun back : Z", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Change gun front : X", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "Green Power Up : + 50 hp", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Yellow Power Up: Double Speed", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Blue power up: Invincibility ", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Power Ups spawn every 30 seconds and last 7.5 ", nullptr));
        pauseMainMenu->setText(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        pauseToGame->setText(QCoreApplication::translate("MainWindow", "Game Screen", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        resultsMainMenu->setText(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Chronological Order downwards. Top score is last game that was played", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "10th to last game that was played", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
