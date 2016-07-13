#include "level.h"


Level::Level()
{

    b2Vec2 Gravity(0.f, 9.8f);
    World = new b2World(Gravity);
    createGround(400.f, 500.f);

    QTimer* timer = new QTimer(this);
    timer->setInterval(60);

    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->start();

    //boxScene = new QGraphicsScene();
}


// some of the following code from https://veendeta.wordpress.com/2012/02/16/tutorial-getting-started-with-box2d/
// we do not take credit for code taken from the above source

void Level::createGround(float X, float Y)
{
    b2BodyDef Ground;
    Ground.position = b2Vec2(X/30.f, Y/30.f);
    Ground.type = b2_staticBody;
    b2Body* Body = World->CreateBody(&Ground);
    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef Fixture;
    Fixture.density = 0.f;  // Sets the density of the body
    Fixture.shape = &Shape; // Sets the shape
    Body->CreateFixture(&Fixture); // Apply the fixture definition
}


void Level::createBox(int PositionX, int PositionY)
{
        b2BodyDef BodyDef;
        BodyDef.position =  b2Vec2(PositionX/SCALE, PositionY/SCALE);
        BodyDef.type = b2_dynamicBody;
        b2Body* Body = World->CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);

}

void Level::step()
{
        World->Step(1/60.f, 8, 3);

        for (b2Body* BodyIterator = World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
               {
                   if (BodyIterator->GetType() == b2_dynamicBody)
                   {
                       //setPos(700,100);
                       QPixmap myPixmap(":/graphics/graphics/word_background.png");
                       myPixmap = myPixmap.scaled(10,10);
//                       QPainter painter(&myPixmap);
//                       painter.setFont(QFont("Arial",letterHeight,4));
//                       painter.setPen(QColor(255,255,255));
//                       painter.drawText(5, 18, m_word);
                       //setPixmap(myPixmap);

                       //Render Code
                   }
                }
}

void Level::damaged()
{

}



