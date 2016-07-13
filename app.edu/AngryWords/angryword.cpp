#include <QTimer>
#include <QPainter>
#include "angryword.h"

AngryWord::AngryWord(QString word, int yPos, bool spawnAngryBird)
{

    m_word = word;
    speed = 1.0;

    const int letterWidth = 20;
    const int letterHeight = 22;

    timer = new QTimer(this);

    if(!spawnAngryBird)
    {

    QFont font("Calibri",24,4);
    font.setBold(true);
    QFontMetrics fm(font);
    int pixelsWide = fm.width(word);

    setPos(1000,yPos);
    QPixmap myPixmap(":/graphics/graphics/word_block.png");
    myPixmap = myPixmap.scaled(letterWidth + pixelsWide + 10, letterHeight + 16);
    QPainter painter(&myPixmap);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255));
    painter.drawText(14, 27, m_word);
    setPixmap(myPixmap);

    isAngryBird = false;
    }
    else
    {
        isAngryBird = true;

        QFont font("Calibri",letterHeight,4);
        font.setBold(true);
        QFontMetrics fm(font);
        int pixelsWide = fm.width(word);


        setPos(1000,yPos);
        QPixmap myPixmap(":/graphics/graphics/angry_bird.png");
        myPixmap = myPixmap.scaled(2*(20+word.length()*2) + pixelsWide, letterHeight + 22);
        QPainter painter(&myPixmap);
        painter.setFont(font);
        painter.setPen(QColor(255,255,255));
        painter.drawText(20+word.length()*3, 30, m_word);
        setPixmap(myPixmap);
    }

    /*
    QMovie myMovie(":/graphics/graphics/explosion.gif");
    myMovie = myMovie.scaled(letterWidth + pixelsWide + 70, letterHeight + 30);
    QPainter painter(&myPixmap);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255));
    painter.drawText(50, 30, m_word);
    setMovie(myMovie);*/

    timer->setInterval(25);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start();

    m_type = 0;
    m_damage = 0;
    m_body = 0;
    m_fixture = 0;

    // body
    /*
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);
    */

}

void AngryWord::typedWord(QString word)
{
    if(word == m_word)
    {
        delete this;
    }
}

QString AngryWord::word()
{
    return m_word;
}

void AngryWord::move()
{
    setPos(x()-speed,y());
}

int AngryWord::getPosX()
{
    return x();
}

int AngryWord::getPosY()
{
    return y();
}

void AngryWord::pauseWord(bool paused)
{
    if(paused)
    {
        timer->stop();
    }
    else
    {
        timer->start();
    }
}
