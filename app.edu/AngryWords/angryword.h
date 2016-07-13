#ifndef ANGRYWORD_H
#define ANGRYWORD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <Box2D/Box2D.h>

class AngryWord : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString m_word;
    int m_type;
    int m_damage;
    b2Body* m_body;
    b2Fixture* m_fixture;


    QTimer* timer;
public:
    explicit AngryWord(QString word, int yPos, bool angryBird);

    void typedWord(QString word);
    QString word();
    int getPosX();
    int getPosY();
    void pauseWord(bool paused);
    double speed;
    bool isAngryBird;


public slots:
    void move();
};

#endif // ANGRYWORD_H
