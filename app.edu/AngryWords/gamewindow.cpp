#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <connector.h>


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    _timerId(0)
{


    //this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    ui->setupUi(this);
    ui->pauseButton->setEnabled(true);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(unPauseGame()));
    connect(ui->pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseGame()));
    connect(ui->deathRestartButton, SIGNAL(clicked(bool)), this, SLOT(restartGame()));
    connect(ui->deathMenuButton, SIGNAL(clicked(bool)), this, SLOT(backToMainMenu()));
    connect(ui->pauseRestartButton, SIGNAL(clicked(bool)), this, SLOT(restartGame()));
    connect(ui->pauseMenuButton, SIGNAL(clicked(bool)), this, SLOT(backToMainMenu()));

    ui->powerupBar->setStyleSheet("QProgressBar::chunk {background-color: yellow;width: 1px;margin: 0px;}");

    // creating rock pixmaps
    _rockCracksPixmap.resize(0);
    _rockCracksPixmap.reserve(5);
    _rockCracksPixmap.push_back(QPixmap(":/graphics/graphics/rock_cracks0.png"));
    _rockCracksPixmap.push_back(QPixmap(":/graphics/graphics/rock_cracks1.png"));
    _rockCracksPixmap.push_back(QPixmap(":/graphics/graphics/rock_cracks2.png"));
    _rockCracksPixmap.push_back(QPixmap(":/graphics/graphics/rock_cracks3.png"));
    _rockCracksPixmap.push_back(QPixmap(":/graphics/graphics/rock_cracks4.png"));


    //SETTING UP OUR TIMERS THAT WILL BE USED THROUGHOUT GAMEPLAY
    birdTimer = new QTimer(this);
    birdTimer->setInterval(30000);

    powerupTimer = new QTimer(this);
    powerupTimer->setInterval(18000);

    slowTimer = new QTimer(this);
    slowTimer->setInterval(6000);

    progressBar = new QTimer(this);
    progressBar->setInterval(1);

    connect(birdTimer, SIGNAL(timeout()),this, SLOT(spawnAnAngryBird()));
    connect(powerupTimer, SIGNAL(timeout()),this, SLOT(enablePowerUp()));
    connect(slowTimer, SIGNAL(timeout()),this, SLOT(speedUpWords()));
    connect(progressBar, SIGNAL(timeout()),this, SLOT(updateProgressBar()));

    m_server = new GameServer(this);
    m_server->newGame();



    QTimer* timer = new QTimer(this);
    timer->setInterval(0);

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0,0,1000, 620);

    //m_scene->addWidget(QPushButton());
    playerHS = new QGraphicsTextItem;
    m_scene->addItem(playerHS);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();

    birdTimer = new QTimer(this);
    birdTimer->setInterval(30000);

    connect(birdTimer, SIGNAL(timeout()),this, SLOT(spawnAnAngryBird()));

    gamePaused = false;
    gameInProgress = false;

    //QWidget::grabKeyboard();

    //b2Vec2 gravity(0.0f, 0.0f);
    b2Vec2 gravity(0.0f, -10.0f);
    _world = new b2World(gravity);

    //createHP(b2Vec2(1, 56),2.5f, new BObject);


    _bobjects.append(createTypedLabel(b2Vec2(66, 56),2.5f, new BObject));

    _bobjects.append(createHP(b2Vec2(1, 56),2.5f, new BObject));

    _bobjects.append(createWoodDecor(b2Vec2(37, 61),2.5f, new BObject));
    _bobjects.append(createTitle(b2Vec2(39, 56),2.0f, new BObject));

    wordsTypedLabel = new QGraphicsTextItem;


    _transform.scale(10.0f, -10.0f);
    _transform.translate(0.0f, -64.0f);
    qDebug() << _transform.map(QPointF(0.0f,0.0f));
    qDebug() << _transform.map(QPointF(36.0f,64.0f));

    _borders.append(createWorldBoundary(0.125f, 10.0f, 100.0f, 0.25f, 0, new BObject));   // bottom
    _borders.append(createWorldBoundary(0.125f, 10.0f, 0.25f, 50.0f, 0, new BObject));    // left
    _borders.append(createWorldBoundary(100.125f, 10.0f, 0.25f, 50.0f, 0, new BObject));  // right
    _borders.append(createWorldBoundary(0.125f, 60.0f, 100.0f, 0.25f, 0, new BObject));  // top

    m_view = this->ui->graphicsView;

    m_view->setScene(m_scene);

    m_view->setBackgroundBrush(QBrush(QPixmap(":/graphics/graphics/angrywords_background.png").scaled(1000,620)));
    //m_view->setStyleSheet("background-color: transparent");
    //m_view->setFixedSize(1000,620);
    //m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //m_view->set
    //this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

//    QPixmap myPixmap(":/graphics/graphics/heart.png");
//    myPixmap = myPixmap.scaled(10, 10);
//    m_scene->addItem(myPixmap);


    // add static BObjects to the scene
    // no need to update their position each frame
    foreach(const BObject* o, _bobjects) {
        switch(o->type) {
        case BlockObject:
            drawBlock(/*p,*/ o);
            break;
        case WallObject:
            ;//drawBoundary(&p, o);
        }
    }

    connect(this->ui->actionPause, SIGNAL(toggled(bool)), this, SLOT(pauseWords(bool)));
    // our sound does not compile on travis and lab2, becuase of missing QtMultimedia
    //m_music  = new QSound(":/snd/saw800.wav",  this);
    //connect(this->ui->actionPlay_music, SIGNAL(triggered()), this, SLOT(playMusic()));
    //connect(this->ui->actionStop_music, SIGNAL(triggered()), this, SLOT(stopMusic()));

    instructions = new QGraphicsPixmapItem;
    instructions->setPos(250.0, 75.0);
    QPixmap myPixmap(":/graphics/graphics/instructions.png");
    myPixmap = myPixmap.scaled((500.0),(500.0));
    instructions->setPixmap(myPixmap);
    m_scene->addItem(instructions);
    //instructions->setPos(400.0, 400.0);


    gameOverText = new QGraphicsPixmapItem;
    m_scene->addItem(gameOverText);

    pausedText = new QGraphicsPixmapItem;
    m_scene->addItem(pausedText);

    powerupText = new QGraphicsPixmapItem();
    m_scene->addItem(powerupText);


    ui->powerupBar->hide();
    ui->label->hide();


    ui->label->setStyleSheet("QLabel { color : white; }");

    //startNewGame();

    setButtonIcon(ui->deathRestartButton,":/graphics/graphics/playagain_button.png",320,90);
    setButtonIcon(ui->deathMenuButton,":/graphics/graphics/menu_button.png",320,90);
    setButtonIcon(ui->pauseRestartButton,":/graphics/graphics/restart_button.png",180,50);
    setButtonIcon(ui->pauseMenuButton,":/graphics/graphics/menu_button.png",180,50);
    setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",155,60);

    ui->deathRestartButton->hide();
    ui->deathMenuButton->hide();
    ui->pauseRestartButton->hide();
    ui->pauseMenuButton->hide();
    ui->playButton->hide();


    //ui->deathRestartButton->installEventFilter(this);


    lWordHit = "";
    wordsHit = 0;
    wordsMissed = 0;
    streak = 0;
    longestStreak = 0;
    score = 0;
}

GameWindow::~GameWindow()
{
        delete ui;
}


void GameWindow::playMusic()
{
/*
    sf::Music music;

    if(!music.openFromFile("/snd/saw800.wav"))
    {

    }
    else
    {
        music.play();
    }*/

}

void GameWindow::stopMusic()
{
    //m_music->stop();
}

void GameWindow::setButtonIcon(QPushButton *button, QString filename, int sizeX, int sizeY)
{
    QPixmap pixmap(filename);
    pixmap = pixmap.scaled(sizeX,sizeY);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}

void GameWindow::startNewGame()
{
    lWordHit = "";
    wordsHit = 0;
    wordsMissed = 0;
    streak = 0;
    timePlayed.start();
    longestStreak = 0;
    score = 0;

    health = 3;
    wordsTyped = 0;
    wordSpeed = 1.3;
    wordAmount = 1;
    userTypedWord = false;
    gamePaused = false;
    spawnAngryBird =false;

    counter = 0;
    if(gamePaused)
    {
        m_scene->removeItem(wordsTypedLabel);
    }
    powerup = false;


    ui->label->show();

    m_userWord = "";

    m_scene->removeItem(wordsTypedLabel);

    setLabels();
    if(gameInProgress == false)
    {
        //m_scene->addItem(wordsTypedLabel);
    }

    gameInProgress = true;


    for(int i=0; i < _castle.size(); i++)
    {
        // remove BObject's body from world
        _world->DestroyBody(_castle[i]->body);
        // delete Bobject using BObject's destuctor
        delete _castle[i];
    }

    _castle.clear();

    for(int i = 0; i < onScreenWords.size(); i++)
    {
        m_scene->removeItem(onScreenWords[i]);
    }

    onScreenWords.clear();


    m_scene->removeItem(gameOverText);
    m_scene->removeItem(pausedText);

    b2Vec2 gravity(0.0f, -10.0f);
    _world->SetGravity(gravity);

    pauseWords(false);

    createCastle();

    resetHearts(health);

    //m_server->getDictionary();
    setWord();
    birdTimer->start();
    powerupTimer->start();

    ui->powerupBar->show();
    progressBar->start();

    setButtonIcon(ui->deathRestartButton,":/graphics/graphics/playagain_button.png",310,85);
    setButtonIcon(ui->deathMenuButton,":/graphics/graphics/menu_button.png",310,90);
    setButtonIcon(ui->pauseRestartButton,":/graphics/graphics/restart_button.png",180,50);
    setButtonIcon(ui->pauseMenuButton,":/graphics/graphics/menu_button.png",180,50);
    setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",155,60);
    setButtonIcon(ui->pauseButton,":/graphics/graphics/pause_button.png",105,45);

    ui->pauseButton->installEventFilter(this);
    ui->playButton->installEventFilter(this);
    ui->deathRestartButton->installEventFilter(this);
    ui->deathMenuButton->installEventFilter(this);
    ui->pauseRestartButton->installEventFilter(this);
    ui->pauseMenuButton->installEventFilter(this);

    //hide all the buttons we dont need right now
    ui->deathRestartButton->hide();
    ui->deathMenuButton->hide();
    ui->pauseRestartButton->hide();
    ui->pauseMenuButton->hide();
    ui->playButton->hide();

}


BObject* GameWindow::createWorldBoundary(float32 x, float32 y, float32 w, float32 h, float32 angle, BObject *o) {
    //BObject o; //Box2D Object
    // body
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = b2Vec2(x+w/2.0f, y+h/2.0f);
    bd.angle = angle * b2_pi;
    o->body = _world->CreateBody(&bd);
    // shape
    b2PolygonShape shape;
    shape.SetAsBox(w/2.0f, h/2.0f);
    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 0.1f;
    fd.friction = 0.3f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = WallObject;
    return o;
}

BObject* GameWindow::createBlock(const b2Vec2& pos, float32 dimension, BObject *o) {
    //BObject o; //Box2D Object

    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x * 10.0, pos.y * (-10.0));
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/rock_cracks0.png");
    myPixmap = myPixmap.scaled((dimension * 20.0),(dimension * 20.0));
    o->pixmapItem->setPixmap(myPixmap);
    m_scene->addItem(o->pixmapItem);

    // body
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);

    // shape
    b2PolygonShape shape;
    shape.SetAsBox(dimension, dimension);

    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = BlockObject;

    return o;
}

QGraphicsPixmapItem *GameWindow::createHeart(const b2Vec2& pos, float32 dimension, QGraphicsPixmapItem *pixmapItem) {
    pixmapItem = new QGraphicsPixmapItem();
    pixmapItem->setPos(pos.x * 10.0, pos.y * (-10.0));
    QPixmap myPixmap(":/graphics/graphics/heart.png");
    myPixmap = myPixmap.scaled((dimension * 20.0),(dimension * 20.0));
    pixmapItem->setPixmap(myPixmap);
    m_scene->addItem(pixmapItem);
    pixmapItem->setPos((10.0) * pos.x, 580.0 + (-10.0) * pos.y);

    return pixmapItem;
}

BObject *GameWindow::createHP(const b2Vec2& pos, float32 dimension, BObject *o) {
    //BObject o; //Box2D Object

    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x * 10.0, pos.y * (-10.0));
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/hp_text.png");
    myPixmap = myPixmap.scaled((dimension * 30.0),(dimension * 18.0));
    o->pixmapItem->setPixmap(myPixmap);
    m_scene->addItem(o->pixmapItem);



    // body
    b2BodyDef bd;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);

    // shape
    b2PolygonShape shape;
    shape.SetAsBox(dimension, dimension);

    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = BlockObject;

    return o;
}

BObject* GameWindow::createTitle(const b2Vec2& pos, float32 dimension, BObject *o) {
    //BObject o; //Box2D Object

    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x * 10.0, pos.y * (-10.0));
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/angrywords_title.png");
    myPixmap = myPixmap.scaled(200,35);
    o->pixmapItem->setPixmap(myPixmap);

    m_scene->addItem(o->pixmapItem);

    // body
    b2BodyDef bd;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);

    // shape
    b2PolygonShape shape;
    shape.SetAsBox(dimension, dimension);

    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = BlockObject;

    return o;
}

BObject* GameWindow::createTypedLabel(const b2Vec2& pos, float32 dimension, BObject *o) {
    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x * 10.0, pos.y * (-10.0));
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/wordstyped_text.png");
    myPixmap = myPixmap.scaled(250,40);
    o->pixmapItem->setPixmap(myPixmap);
    m_scene->addItem(o->pixmapItem);

    // body
    b2BodyDef bd;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);

    // shape
    b2PolygonShape shape;
    shape.SetAsBox(dimension, dimension);

    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = BlockObject;

    return o;
}

BObject* GameWindow::createWood(const b2Vec2& pos, float32 dimension, BObject *o) {
    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x, pos.y);
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/wood_block.png");
    myPixmap = myPixmap.scaled((dimension * 100.0),(dimension * 20.0));
    o->pixmapItem->setPixmap(myPixmap);
    m_scene->addItem(o->pixmapItem);

    // body
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);

    // shape
    b2PolygonShape shape;
    shape.SetAsBox(dimension * 5, dimension);

    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = BlockObject;

    return o;
}

BObject* GameWindow::createWoodDecor(const b2Vec2& pos, float32 dimension, BObject *o) {
    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x, pos.y);
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/wood_decor.png");
    myPixmap = myPixmap.scaled((dimension * 100.0),(dimension * 40.0));
    o->pixmapItem->setPixmap(myPixmap);
    m_scene->addItem(o->pixmapItem);

    // body
    b2BodyDef bd;
    //bd.type = b2_dynamicBody;
    bd.position = pos;
    o->body = _world->CreateBody(&bd);

    // shape
    b2PolygonShape shape;
    shape.SetAsBox(dimension * 5, dimension);

    // fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    o->fixture = o->body->CreateFixture(&fd);
    o->type = BlockObject;

    return o;
}


/*
 * Updates the ui for Box2D objects. This includes the background, walls, and blocks
 */
void GameWindow::paintEvent(QPaintEvent *) {
    //QPainter p(this);

    foreach(const BObject* o, _castle) {
        switch(o->type) {
        case BlockObject:
            drawBlock(/*p,*/ o); // it does not actually draw anything
                                 // it just updates BObjects positions
            break;
        case WallObject:
            ;//drawBoundary(&p, o);
        }
    }

}

/*
 * Helper methods for drawing world boundarys.
 */
void GameWindow::drawBoundary(QPainter *p, const BObject *o) {
    float32 x = o->body->GetPosition().x;
    float32 y = o->body->GetPosition().y;
    float32 angle = o->body->GetAngle();
    const b2PolygonShape *shape = dynamic_cast<b2PolygonShape*>(o->fixture->GetShape());
    float32 hx = shape->GetVertex(1).x;
    float32 hy = shape->GetVertex(2).y;
    QRectF r(x-hx, y-hy, 2*hx, 2*hy);
    p->save();
    p->translate(r.center());
    p->rotate(angle*180/b2_pi);
    p->translate(-r.center());
    p->drawRect(r);
    p->restore();
}

/*
 * Helper method for drawing wall blocks. Blocks have an associated body and damage.
 * Health ranges from 0-3 where the lower the healt the more damage it has taken
 * on until it is destroyed.
 */
// This function does not actually draw anything anymore
// It just updates BObjects positions
void GameWindow::drawBlock(const BObject* o) {
    float32 x = o->body->GetPosition().x;
    float32 y = o->body->GetPosition().y;
    o->pixmapItem->setPos((10.0) * x, 580.0 + (-10.0) * y);
}



void GameWindow::slowDownWords()
{
    if(gameInProgress)
    {
    powerupTimer->stop();
    slowTimer->start();
    ui->powerupBar->show();
    ui->label->show();
    progressBar->start();
    m_scene->removeItem(powerupText);

    goingSlow = true;

    for(int i=0; i < onScreenWords.size();i++)
    {
        //wordSpeed = wordSpeed - 0.9;
        onScreenWords[i]->speed = onScreenWords[i]->speed - 0.9;
    }

    powerup = false;
    }
}

void GameWindow::enablePowerUp()
{
    if(gameInProgress)
        powerup = true;
}

void GameWindow::speedUpWords()
{
    if(gameInProgress)
    {
    slowTimer->stop();
    powerupTimer->start();

    goingSlow = false;

    for(int i=0; i < onScreenWords.size();i++)
    {
        //wordSpeed = wordSpeed + 0.9;
        onScreenWords[i]->speed = onScreenWords[i]->speed + 0.9;
    }
    counter = 0;

    //progressBar->start();

    ui->powerupBar->setValue(0);

    ui->powerupBar->show();
    ui->label->show();
    }

}

void GameWindow::updateProgressBar()
{
    //wordsTyped = powerupTimer->interval()/15000;

    if(!goingSlow)
    {
     if(counter <= 18000)
     {
         int value;
             value  =counter++;
             //value = value /1000;
         ui->powerupBar->setValue(value);
     }
     else
     {
         progressBar->stop();


         m_scene->addItem(powerupText);
         powerupText->setPos(345.0, 570.0);
         QPixmap myPixmap2(":/graphics/graphics/powerup_message.png");
         myPixmap2 = myPixmap2.scaled((320.0),(25.0));
         powerupText->setPixmap(myPixmap2);

         ui->powerupBar->hide();
         ui->label->hide();
     }
    }
    else
    {
        //if(counter <= 18000)
        //{
            int value;
            counter= counter - 3;
            value = counter;
            ui->powerupBar->setValue(value);
        //}
    }
}

/*
 * Initialize world timer to 60 fps
 */
void GameWindow::startGame() {
    if(!_timerId) {
        _timerId = startTimer(1000/60); // 60fps
    }
}
/*
 * Maintains world timer
 * FPS: 60
 * Velocity: 8
 * Position: 3
 */
void GameWindow::timerEvent(QTimerEvent *event) {
    if(event->timerId() == _timerId) {
        _world->Step(1.0f/60.0f, 8, 3);
        update();

        for(int i=0; i < onScreenWords.size(); i++)
        {
            if(onScreenWords[i]->getPosX() < COLLIDE_POSITION && gameInProgress)
            {

                m_scene->removeItem(onScreenWords[i]);
                if(onScreenWords[i]->isAngryBird)
                {
                    onScreenWords.erase(onScreenWords.begin() + i);
                    wordCollided(true);
                }
                else
                {
                    onScreenWords.erase(onScreenWords.begin() + i);
                    wordCollided(false);
                }
            }
        }
    }
}

void GameWindow::wordCollided(bool angryBirdHit)
{
    if(angryBirdHit)
    {
        for(int i=0; i <health;i++)
        {
            delete _hearts.last();
            _hearts.pop_back();
        }

        health = 0;
        wordsMissed++;

        //_hearts.clear();
    }
    else {

        setWord();
        health--;
        wordsMissed++;
        streak = 0;


        //delete _hearts.last()->pixmapItem; // BObjects now have destructors
        //_world->DestroyBody(_hearts.last()->body); // Hearts do not have a body anymore
        delete _hearts.last();
        _hearts.pop_back();

    }



    if(health == 0)
    {
        ui->powerupBar->hide();
        ui->label->hide();
        progressBar->stop();

        birdTimer->stop();

        for(int i=0; i < 10; i++)
        {
            // remove BObject's body from world
            _world->DestroyBody(_castle[i]->body);
            // delete Bobject using BObject's destuctor
            delete _castle[i];
        }

        _castle.erase(_castle.begin(), _castle.begin()+10);

        for(int i = 0; i < onScreenWords.size(); i++)
        {
            m_scene->removeItem(onScreenWords[i]);
    //            onScreenWords.erase(onScreenWords.begin() + i);

        }
        onScreenWords.clear();

        m_userWord = "";
        if(userTypedWord == true)
        {
           m_scene->removeItem(userLabel);
           userTypedWord = false;
        }

        //gameInProgress = false;
        //m_scene->removeItem(wordsTypedLabel);

        b2Vec2 gravity(0.0f, -100.0f);
        _world->SetGravity(gravity);
        pauseWords(true);
        gamePaused =true;

        deathTimer = new QTimer(this);
        deathTimer->setInterval(4000);

        connect(deathTimer, SIGNAL(timeout()), this, SLOT(gameOver()));
        deathTimer->start();
        ui->pauseButton->hide();
        m_scene->removeItem(powerupText);

    }

    retextureCastle();

}

void GameWindow::gameOver()
{
    m_scene->removeItem(gameOverText);
    ui->deathRestartButton->show();
    ui->deathMenuButton->show();
    ui->powerupBar->setValue(0);

    gameOverText = new QGraphicsPixmapItem;
    gameOverText->setPos(290.0, 150.0);
    QPixmap myPixmap(":/graphics/graphics/game_over_text.png");
    myPixmap = myPixmap.scaled((400.0),(100.0));
    gameOverText->setPixmap(myPixmap);
    m_scene->addItem(gameOverText);

    gameInProgress = false;
    deathTimer->stop();

    if(user != "Guest")
    {
    if(!(user.isNull() || user.isEmpty()))
    {
        Connector c;
        c.updateStats(user, score, timePlayed.elapsed() / 1000, wordsHit, wordsMissed, lWordHit, longestStreak);
    }
    }

}

void GameWindow::setUsername(QString username, int hs)
{
    if(username == "")
    {
        user = "Guest";
        highScore = 0;
    }
    else
    {
        user = username;
        highScore = hs;
    }
}

void GameWindow::retextureCastle()
{
    int myPixmapIndex;
    // if (maxHealth - health) exceeds the number of available cracked rock textures
    // then use the most cracked one
    if((maxHealth - health) < _rockCracksPixmap.size())
        myPixmapIndex = maxHealth - health - 1;
    else
        myPixmapIndex = _rockCracksPixmap.size() - 1;

    foreach(const BObject *o, _castle)
        o->pixmapItem->setPixmap(_rockCracksPixmap[myPixmapIndex].scaled((2.0F * 20.0),(2.0F * 20.0)));
}

//pauses all words in the game
void GameWindow::pauseWords(bool paused)
{
    for(int i=0; i < onScreenWords.size(); i++)
    {
        onScreenWords[i]->pauseWord(paused);
    }
}

void GameWindow::resetHearts(int health)
{
    for(int i = 0; i < _hearts.size(); ++i)
    {
        delete _hearts[i];
    }
    _hearts.resize(health);

    const float y = 56.0;
    const float x = 10;
    const float dx = 5.0;
    for(int i = 0; i < health; ++i)
         _hearts[i] = createHeart(b2Vec2(x + i * dx, y),2.5f, new QGraphicsPixmapItem());
}

void GameWindow::createCastle()
{
    const int x = 25;
    const int dx = 5;
    const int y = 6;
    const int dy = 5;
    for(int i=1; i<5; i++) {
        for(int j = 0; j < 5; ++j)
            _castle.append(createBlock(b2Vec2(x - j * dx, y + i * dy),2.0f, new BObject));
    }
    for(int i=5; i<9; i++) {
        for(int j = 0; j < 4; ++j)
            _castle.append(createBlock(b2Vec2(x - (0.5 + j) * dx, y + i * dy),2.0f, new BObject));
    }
    for(int j = 0; j < 3; ++j)
        _castle.append(createBlock(b2Vec2(x - (1 + j) * dx, y + 9 * dy),2.0f, new BObject));
    //_castle.append(createBlock(b2Vec2(x - 17.5, y + 45),2.0f, new BObject));
    //_castle.append(createBlock(b2Vec2(x - 10, y + 45),2.0f, new BObject));

}

void GameWindow::setLabels()
{
    QFont tFont("Calibri",32,6);
    tFont.setBold(true);

    QFont uFont("Calibri",45,9);
    uFont.setBold(true);

    QFont vFont("Calibri",22,7);
    vFont.setBold(true);

    userLabel = new QGraphicsTextItem;
    userLabel->setPos(0,495);
    userLabel->setFont(uFont);
    userLabel->setTextWidth(1000);
    userLabel->document()->setDocumentMargin(0);
    userLabel->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    userLabel->setDefaultTextColor(QColor(Qt::white));

    wordsTypedLabel->setPos(900,15);
    wordsTypedLabel->setFont(tFont);
    wordsTypedLabel->setTextWidth(100);
    wordsTypedLabel->document()->setDocumentMargin(0);
    wordsTypedLabel->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    wordsTypedLabel->setDefaultTextColor(QColor(Qt::black));
    wordsTypedLabel->setPlainText(QString::number(wordsTyped));
    m_scene->addItem(wordsTypedLabel);



    QGraphicsPixmapItem* playerLabels = new QGraphicsPixmapItem;
    playerLabels->setPos(10.0, 555.0);
    QPixmap myPixmap2(":/graphics/graphics/player_highscore.png");
    myPixmap2 = myPixmap2.scaled((130.0),(50.0));
    playerLabels->setPixmap(myPixmap2);
    m_scene->addItem(playerLabels);

    playerName = new QGraphicsTextItem;
    playerName->setPos(106,547);
    playerName->setFont(vFont);
//    playerName->setTextWidth(1000);
//    playerName->document()->setDocumentMargin(0);
//    playerName->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    playerName->setDefaultTextColor(QColor(Qt::white));
    playerName->setPlainText(user);
    m_scene->addItem(playerName);


    playerHS->setPos(150,576);
    playerHS->setFont(vFont);
//    playerHS->setTextWidth(1000);
//    playerHS->document()->setDocumentMargin(0);
//    playerHS->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    playerHS->setDefaultTextColor(QColor(Qt::white));
    playerHS->setPlainText(QString::number(highScore));



}

void GameWindow::keyPressEvent(QKeyEvent* e)
{
    if(gameInProgress)
    {
        if(gamePaused == false)
        {
            //enableGravity();
            //if the user presses space or enter, it checks their word and
            //gets a new one if its equal to the main word
            if(e->key() == Qt::Key_Space || e->key() == Qt::Key_Return)
            {
                for(int i = 0; i < onScreenWords.size(); i++)
                {
                    int x = QString::compare(m_userWord, onScreenWords[i]->word(), Qt::CaseInsensitive);
                    if(x == 0)
                    {

                        if(onScreenWords[i]->word().size() > lWordHit.size())
                        {
                            lWordHit = onScreenWords[i]->word();
                        }

                        wordsHit++;
                        streak++;
                        score++;

                        if(streak > longestStreak)
                        {
                            longestStreak = streak;
                        }

                        m_scene->removeItem(onScreenWords[i]);
                        onScreenWords.erase(onScreenWords.begin() + i);
                        m_userWord = "";

                        if(userTypedWord == true)
                        {
                            m_scene->removeItem(userLabel);
                            userTypedWord = false;
                        }

                        wordsTyped++;

                        if(wordsTyped > highScore)
                        {;
                            m_scene->removeItem(playerHS);
                            highScore = wordsTyped;
                            playerHS->setPlainText(QString::number(highScore));
                            m_scene->addItem(playerHS);
                        }

                        setWord();

                        if(wordsTyped%5 == 0 && wordsTyped != 0)
                        {
                            setWord();
                        }

                        if(wordsTyped%20 ==0 && wordsTyped != 0)
                        {
                            if(health < maxHealth)
                            {
                                health++;
                                resetHearts(health);
                                retextureCastle();
                            }
                        }




                        //QString words = wordsTyped.toPlainText();
                        wordsTypedLabel->setPlainText(QString::number(wordsTyped));
                    }
                }
            }
            else if(e->key() == Qt::Key_Backspace) //backspace erases the user's word
            {
                m_userWord = "";

                if(userTypedWord == true)
                {
                    m_scene->removeItem(userLabel);
                    userTypedWord = false;
                }

            }else if(e->key() == Qt::Key_Shift) //slows down the words
            {
                if(powerup)
                {
                    slowDownWords();
                }
            }
            else if(e->key() == Qt::Key_Escape) //unpauses game
            {
               pauseGame();
            }
            else
            {
                //use regualr expression to check if its a valid letter
                QRegExp re("\\w*");  // a word (\w), zero or more times (*)
                if (re.exactMatch(e->text()))
                {
                    if(m_userWord.length() < 25)
                    {
                        m_userWord = m_userWord + e->text();

                        userLabel->setPlainText(m_userWord);

                        if(userTypedWord == false)
                        {
                            m_scene->addItem(userLabel);
                            userTypedWord = true;
                        }
                    }
                }

            }

        }
        else if(e->key() == Qt::Key_Escape) //pauses game
        {

            //pause words
            unPauseGame();
        }
    }
    else
    {
        if(e->key() == Qt::Key_Return) //backspace erases the user's word
        {
            //unpause words
            startNewGame();
            m_scene->removeItem(instructions);
        }
    }
}

void GameWindow::pauseGame()
{
    //pause words
    pauseWords(true);
    gamePaused = true;

    m_scene->removeItem(pausedText);

    ui->playButton->show();
    ui->pauseButton->hide();
    ui->pauseMenuButton->show();
    ui->pauseRestartButton->show();

    birdTimer->stop();
    progressBar->stop();
    powerupTimer->stop();

    pausedText = new QGraphicsPixmapItem;
    pausedText->setPos(290.0, 160.0);
    QPixmap myPixmap(":/graphics/graphics/paused_text.png");
    myPixmap = myPixmap.scaled((400.0),(100.0));
    pausedText->setPixmap(myPixmap);
    m_scene->addItem(pausedText);

}

void GameWindow::unPauseGame()
{
    //pause words
    pauseWords(false);
    gamePaused = false;

    birdTimer->start();
    progressBar->start();
    powerupTimer->start();

    ui->playButton->hide();
    ui->pauseButton->show();
    ui->pauseMenuButton->hide();
    ui->pauseRestartButton->hide();

    m_scene->removeItem(pausedText);

}

void GameWindow::playGame()
{

}

void GameWindow::restartGame()
{
    lWordHit = "";
    wordsHit = 0;
    wordsMissed = 0;
    streak = 0;
    longestStreak = 0;
    score = 0;

    m_scene->removeItem(userLabel);
    m_scene->removeItem(pausedText);
    m_scene->removeItem(gameOverText);
    startNewGame();
    ui->pauseButton->show();
    ui->pauseMenuButton->hide();
    ui->pauseRestartButton->hide();
    ui->deathMenuButton->hide();
    ui->deathRestartButton->hide();

}

void GameWindow::backToMainMenu()
{

    m_scene->removeItem(pausedText);
    m_scene->removeItem(gameOverText);
    ui->pauseMenuButton->hide();
    ui->pauseRestartButton->hide();
    ui->deathMenuButton->hide();
    ui->deathRestartButton->hide();
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

int GameWindow::getWordPosition()
{
    bool goodPosition = false;
    int toReturn = 0;

    if(onScreenWords.size()==0)
    {
        int random = rand() % 300 + 150;
        return random;
    }
    else {
        while(!goodPosition)
        {
            int random = rand() % 300 + 150;

            for(int i=0; i< onScreenWords.size();i++)
            {
                int otherWordPos = onScreenWords[i]->getPosY();

                if(random -100 < otherWordPos && random +100 > otherWordPos)
                {
                    goodPosition = false;
                }
                else
                {
                    goodPosition = true;
                    toReturn = random;
                }
            }
        }
    }

    return toReturn;
}

void GameWindow::setWord()
{
    int limit = 2;

    if(wordsTyped >= 15 && wordsTyped <= 25)
    {
        limit = 3;
    }
    else if(wordsTyped >= 25 && wordsTyped <= 50)
    {
        limit = 4;
    }
    else if(wordsTyped >= 50)
    {
        limit = 5;
    }


    if(onScreenWords.size() < limit)
    {
        //AngryWord m_mainWord = ;
        onScreenWords.append(new AngryWord(*(m_server->getWord()),getWordPosition(),spawnAngryBird));
        spawnAngryBird = false;

        m_scene->addItem(onScreenWords.back());

        if(wordsTyped%10 == 0 && wordsTyped != 0)
        {
            if(wordsTyped < 50)
            {
                wordSpeed = wordSpeed+0.15;
            }
            else {

                wordSpeed = wordSpeed+0.05;
            }
        }
        if(goingSlow)
        {
            onScreenWords.back()->speed = wordSpeed - 0.9;

        }
        else
        {
            onScreenWords.back()->speed = wordSpeed;
        }
    }
}

void GameWindow::spawnAnAngryBird()
{
    spawnAngryBird = true;
}

/*
 * animates the icon of each button in the game
*/
//event filter derived from
//http://stackoverflow.com/questions/9261175/how-to-do-that-when-the-mouse-pointer-hovers-over-a-qpushbutton-then-the-button
bool GameWindow::eventFilter(QObject *obj, QEvent *event)
{
    // This function repeatedly call for those QObjects
    // which have installed eventFilter (Step 2)

    if (obj == (QObject*)ui->pauseButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->pauseButton,":/graphics/graphics/pause_button.png",110,50);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->pauseButton,":/graphics/graphics/pause_button.png",105,45);
        }
        return QWidget::eventFilter(obj, event);
    } else if (obj == (QObject*)ui->playButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",165,65);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",155,60);
        }
        return QWidget::eventFilter(obj, event);
    } else if (obj == (QObject*)ui->deathRestartButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->deathRestartButton,":/graphics/graphics/playagain_button.png",320,90);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->deathRestartButton,":/graphics/graphics/playagain_button.png",310,85);
        }
        return QWidget::eventFilter(obj, event);
    } else if (obj == (QObject*)ui->deathMenuButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->deathMenuButton,":/graphics/graphics/menu_button.png",320,90);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->deathMenuButton,":/graphics/graphics/menu_button.png",310,85);
        }
        return QWidget::eventFilter(obj, event);
    } else if (obj == (QObject*)ui->pauseRestartButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->pauseRestartButton,":/graphics/graphics/restart_button.png",190,55);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->pauseRestartButton,":/graphics/graphics/restart_button.png",180,50);
        }
        return QWidget::eventFilter(obj, event);
    } else if (obj == (QObject*)ui->pauseMenuButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->pauseMenuButton,":/graphics/graphics/menu_button.png",190,55);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->pauseMenuButton,":/graphics/graphics/menu_button.png",180,50);
        }
        return QWidget::eventFilter(obj, event);
    }
}

