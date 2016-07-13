#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <iostream>
//#include <QtMultimedia/QSound>
//#include "welcomescreen.h"

#include "dictionary.h"
#include "gameserver.h"
#include "angryword.h"
#include "level.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include <QtGui>
#include <Box2D/Box2D.h>
#include "bobject.h"
#include <QLabel>
#include <QLayout>
#include <QGraphicsView>
#include <QApplication>
#include <QMessageBox>
#include <QProcess>


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    GameServer* m_server; //dictionary is private to m_server
    enum
    {
        BlockObject,
        WallObject,
    } BObjects;

/*
    // We use BObject class instead
    // It allows to have its destuctor to properly destroy poiners
    struct BObject
    {
        //AngryWord angryWord;
        QGraphicsPixmapItem* pixmapItem;
        int type;
        int damage;
        b2Body *body;
        b2Fixture *fixture;
    };
*/

  bool eventFilter(QObject *obj, QEvent *event);

  QLabel* userWordLabel;

  BObject* createWorldBoundary(float32 x, float32 y, float32 w, float32 h, float32 angle, BObject* ptr);//angle=0
  BObject* createWood(const b2Vec2& pos, float32 dimension, BObject *o);
  BObject* createBlock(const b2Vec2& pos, float32 radius, BObject* ptr);
  QGraphicsPixmapItem* createHeart(const b2Vec2& pos, float32 dimension, QGraphicsPixmapItem *pixmapItem);
  BObject* createHP(const b2Vec2& pos, float32 dimension, BObject *o);
  BObject* createTitle(const b2Vec2& pos, float32 dimension, BObject *o);
  BObject* createTypedLabel(const b2Vec2& pos, float32 dimension, BObject *o);
  BObject* createWoodDecor(const b2Vec2& pos, float32 dimension, BObject *o);
  void paintEvent(QPaintEvent *);
  void keyPressEvent(QKeyEvent* e);
  void drawBoundary(QPainter *p, const BObject* o);
  void drawBlock(const BObject *o);
  void timerEvent(QTimerEvent *event);
  void setWord();

  QTimer* deathTimer;
  QTimer* progressBar;

  void setButtonIcon(QPushButton *button, QString filename, int sizeX, int sizeY);

  void wordCollided(bool angryBirdHit);
  void retextureCastle();
  int getWordPosition();
  void setUsername(QString username, int hs);

  void startNewGame();

  bool gamePaused;

  int health;
  int wordsTyped;
  double wordSpeed;
  int wordAmount;
  bool userTypedWord;
  int highScore;

  bool gameInProgress;\

  QTimer* birdTimer;
  bool spawnAngryBird;

  QTimer* slowTimer;
  QTimer* powerupTimer;

  bool goingSlow = false;

  int counter =0;

  bool powerup;



  int COLLIDE_POSITION = 280; //the position at which the word "collides" with the castle

  QString user;
  QTime timePlayed;
  QString lWordHit;
  int wordsHit;
  int wordsMissed;
  int streak;
  int longestStreak;
  int score;

private slots:
  void pauseWords(bool paused);
  void playMusic();
  void stopMusic();

public slots:
  void slowDownWords();
  void updateProgressBar();

  void enablePowerUp();

  void speedUpWords();
  void startGame();
  void gameOver();

  void pauseGame();

  void unPauseGame();

  void playGame();

  void restartGame();

  void backToMainMenu();

  void spawnAnAngryBird();


signals:
  void mainMenu();

private:
    Ui::GameWindow *ui;

    static const int maxHealth = 5;

    b2World *_world;
    int _timerId;
    QTransform _transform;

    QVector<QPixmap> _rockCracksPixmap;

    QVector<BObject*> _bobjects;
    QVector<BObject*> _castle;
    QVector<BObject*> _borders;
    QVector<QGraphicsPixmapItem*> _hearts;


    QVector<AngryWord*> onScreenWords;
    QGraphicsTextItem * userLabel;
    QGraphicsTextItem * wordsTypedLabel;
    QGraphicsTextItem * playerName;
    QGraphicsTextItem * playerHS;
    QGraphicsPixmapItem *instructions;
    QGraphicsPixmapItem *gameOverText;
    QGraphicsPixmapItem *pausedText;
    QGraphicsPixmapItem *powerupText;
    AngryWord* m_mainWord;
    QString m_userWord;
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QPainter* p;

    void resetHearts(int health);
    void createCastle();

    void setLabels();

};

#endif // GAMEWINDOW_H
