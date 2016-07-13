#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
//#include <QSound>
#include "gamewindow.h"
#include <statspage.h>

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = 0);
    ~WelcomeScreen();

    bool eventFilter(QObject *obj, QEvent *event);
    void setButtonIcon(QPushButton *button, QString filename, int sizeX, int sizeY);
    void startGame(QString username);
    int getHighScore(QString player);

    //QSound themeSong;

    int difficultyOption;


public slots:
    void playButtonClicked();
    void guestButtonClicked();
    void statsButtonClicked();
    void showMainMenu();
    void teacherStatsButtonClicked();

signals:
    void playGame();
    void showStats();

private slots:
    void on_playButton_pressed();

    void on_usernameTextbox_textChanged(const QString &arg1);

    void on_teacherBox_stateChanged(int arg1);


    void on_studentBox_stateChanged(int arg1);

private:
    Ui::WelcomeScreen *ui;
    QGraphicsScene *scene;
    GameWindow *gameWindow;
    StatsPage statPage;
};

#endif // WELCOMESCREEN_H
