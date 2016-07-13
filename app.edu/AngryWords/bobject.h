#ifndef BOBJECT_H
#define BOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <Box2D/Box2D.h>

/*
class BObject : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int m_type;
    int m_damage;
    b2Body* m_body;
    b2Fixture* m_fixture;

public:
    explicit BObject(QWidget *parent = 0);

public slots:
};
*/


class BObject
{
public:
    BObject(){}
    ~BObject();

    //AngryWord angryWord;
    QGraphicsPixmapItem* pixmapItem;
    int type;
    int damage;
    b2Body *body;
    b2Fixture *fixture;
};

#endif // BOBJECT_H
