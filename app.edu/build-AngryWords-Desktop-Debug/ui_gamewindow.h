/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionEnd_Game;
    QAction *actionQuit;
    QAction *actionPlay_music;
    QAction *actionStop_music;
    QAction *actionPause;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGraphicsView *graphicsView;
    QPushButton *pauseButton;
    QPushButton *deathRestartButton;
    QPushButton *deathMenuButton;
    QPushButton *playButton;
    QPushButton *pauseRestartButton;
    QPushButton *pauseMenuButton;
    QLabel *label;
    QProgressBar *powerupBar;
    QMenuBar *menuBar;
    QMenu *menuAbout_Angry_Words;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->resize(1014, 658);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/graphics/graphics/rock_cracks2.png"), QSize(), QIcon::Normal, QIcon::Off);
        GameWindow->setWindowIcon(icon);
        actionNew_Game = new QAction(GameWindow);
        actionNew_Game->setObjectName(QString::fromUtf8("actionNew_Game"));
        actionEnd_Game = new QAction(GameWindow);
        actionEnd_Game->setObjectName(QString::fromUtf8("actionEnd_Game"));
        actionQuit = new QAction(GameWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionPlay_music = new QAction(GameWindow);
        actionPlay_music->setObjectName(QString::fromUtf8("actionPlay_music"));
        actionStop_music = new QAction(GameWindow);
        actionStop_music->setObjectName(QString::fromUtf8("actionStop_music"));
        actionPause = new QAction(GameWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setCheckable(true);
        centralWidget = new QWidget(GameWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(17);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(1000, 620));
        widget->setMaximumSize(QSize(1000, 620));
        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(0, 0, 1000, 620));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pauseButton = new QPushButton(widget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setEnabled(true);
        pauseButton->setGeometry(QRect(860, 550, 121, 51));
        pauseButton->setAutoDefault(false);
        pauseButton->setDefault(false);
        pauseButton->setFlat(true);
        deathRestartButton = new QPushButton(widget);
        deathRestartButton->setObjectName(QString::fromUtf8("deathRestartButton"));
        deathRestartButton->setGeometry(QRect(330, 250, 330, 100));
        deathRestartButton->setFlat(true);
        deathMenuButton = new QPushButton(widget);
        deathMenuButton->setObjectName(QString::fromUtf8("deathMenuButton"));
        deathMenuButton->setGeometry(QRect(330, 350, 321, 100));
        deathMenuButton->setFlat(true);
        playButton = new QPushButton(widget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(400, 270, 181, 71));
        playButton->setFlat(true);
        pauseRestartButton = new QPushButton(widget);
        pauseRestartButton->setObjectName(QString::fromUtf8("pauseRestartButton"));
        pauseRestartButton->setGeometry(QRect(280, 340, 201, 71));
        pauseRestartButton->setFlat(true);
        pauseMenuButton = new QPushButton(widget);
        pauseMenuButton->setObjectName(QString::fromUtf8("pauseMenuButton"));
        pauseMenuButton->setGeometry(QRect(500, 340, 201, 71));
        pauseMenuButton->setFlat(true);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(450, 590, 101, 21));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        powerupBar = new QProgressBar(widget);
        powerupBar->setObjectName(QString::fromUtf8("powerupBar"));
        powerupBar->setGeometry(QRect(400, 570, 201, 20));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        powerupBar->setFont(font1);
        powerupBar->setMaximum(18000);
        powerupBar->setValue(0);
        powerupBar->setAlignment(Qt::AlignCenter);
        powerupBar->setOrientation(Qt::Horizontal);
        powerupBar->setInvertedAppearance(false);

        horizontalLayout->addWidget(widget);

        GameWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1014, 27));
        menuAbout_Angry_Words = new QMenu(menuBar);
        menuAbout_Angry_Words->setObjectName(QString::fromUtf8("menuAbout_Angry_Words"));
        GameWindow->setMenuBar(menuBar);

        menuBar->addAction(menuAbout_Angry_Words->menuAction());

        retranslateUi(GameWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), GameWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Angry Words", 0, QApplication::UnicodeUTF8));
        actionNew_Game->setText(QApplication::translate("GameWindow", "New Game", 0, QApplication::UnicodeUTF8));
        actionEnd_Game->setText(QApplication::translate("GameWindow", "End Game", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("GameWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionPlay_music->setText(QApplication::translate("GameWindow", "Play music", 0, QApplication::UnicodeUTF8));
        actionStop_music->setText(QApplication::translate("GameWindow", "Stop music", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("GameWindow", "Pause", 0, QApplication::UnicodeUTF8));
        pauseButton->setText(QString());
        deathRestartButton->setText(QString());
        deathMenuButton->setText(QString());
        playButton->setText(QString());
        pauseRestartButton->setText(QString());
        pauseMenuButton->setText(QString());
        label->setText(QApplication::translate("GameWindow", "Powerup", 0, QApplication::UnicodeUTF8));
        powerupBar->setFormat(QString());
        menuAbout_Angry_Words->setTitle(QApplication::translate("GameWindow", "About Angry Words", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
