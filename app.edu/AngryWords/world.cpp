#include "world.h"
#include <QPixmap>
#include <QPainter>

/*
 * Constructs new Box2D world
 *
 */
World::World(QWidget *parent) : _timerId(0)
{
    //p = new QPainter(this);

    m_server = new GameServer(this);
    m_server->newGame();
    m_server->getEntireDatabase();

    QTimer* timer = new QTimer(this);
    timer->setInterval(0);

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0,0,1000, 550);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();


    QWidget::grabKeyboard();

    //b2Vec2 gravity(0.0f, 0.0f);
    b2Vec2 gravity(0.0f, -10.0f);
    _world = new b2World(gravity);

    int dx = 25;
    int dy = 6;
    for(int i=0; i<20; i++) {
        //int dx = 50; //18 - qrand() % 36;
        dy += 5; // qrand() % 2;
        _bobjects.append(createBlock(b2Vec2(dx, dy),1.0f, new BObject));
    }

    _transform.scale(10.0f, -10.0f);
    _transform.translate(0.0f, -64.0f);
    qDebug() << _transform.map(QPointF(0.0f,0.0f));
    qDebug() << _transform.map(QPointF(36.0f,64.0f));
    _bobjects.append(createWorldBoundary(0.125f, 10.0f, 100.0f, 0.25f, 0, new BObject));   // bottom
    _bobjects.append(createWorldBoundary(0.125f, 10.0f, 0.25f, 50.0f, 0, new BObject));    // left
    _bobjects.append(createWorldBoundary(100.125f, 10.0f, 0.25f, 50.0f, 0, new BObject));  // right
    _bobjects.append(createWorldBoundary(0.125f, 60.0f, 100.0f, 0.25f, 0, new BObject));  // top

    m_view = new QGraphicsView(/*m_scene,*/ this);
    //m_box = new QVBoxLayout;
    //m_box->addWidget(m_view);
    m_view->setScene(m_scene);

    m_view->setBackgroundBrush(QBrush(QPixmap(":/graphics/graphics/angrywords_background.png").scaled(1000,550)));
    //m_view->setStyleSheet("background-color: transparent");
    //this->setLayout(m_box);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setWord();
}

World::BObject* World::createWorldBoundary(float32 x, float32 y, float32 w, float32 h, float32 angle, BObject *o) {
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

World::BObject* World::createBlock(const b2Vec2& pos, float32 dimension, BObject *o) {
    //BObject o; //Box2D Object

    // damage
    o->damage = 0;
    o->pixmapItem = new QGraphicsPixmapItem();
    o->pixmapItem->setPos(pos.x * 10.0, pos.y * (-10.0));
    //o->pixmapItem->setTransform(_transform);
    QPixmap myPixmap(":/graphics/graphics/rock_cracks0.png");
    myPixmap = myPixmap.scaled((dimension * 20.0),(dimension * 20.0));
    QPainter painter(&myPixmap);
    //painter.setTransform(_transform);
    painter.setFont(QFont("Arial",18,4));
    painter.setPen(QColor(255,255,255));
    painter.drawText(5, 18, "test");
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

/*
 * Updates the ui for Box2D objects. This includes the background, walls, and blocks
 */
void World::paintEvent(QPaintEvent *) {
    //QPainter p(this);

    foreach(const BObject* o, _bobjects) {
        switch(o->type) {
        case BlockObject:
            drawBlock(/*p,*/ o);
            break;
        case WallObject:
            ;//drawBoundary(&p, o);
        }
    }
}

/*
 * Helper methods for drawing world boundarys.
 */
void World::drawBoundary(QPainter *p, const BObject *o) {
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
void World::drawBlock(const BObject* o) {
    float32 x = o->body->GetPosition().x;
    float32 y = o->body->GetPosition().y;
    o->pixmapItem->setPos((10.0) * x, 580.0 + (-10.0) * y);
}

/*
 * Initialize world timer to 60 fps
 */
void World::start() {
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
void World::timerEvent(QTimerEvent *event) {
    if(event->timerId() == _timerId) {
        _world->Step(1.0f/60.0f, 8, 3);
        update();
    }
}

void World::enableGravity()
{
    b2Vec2 gravity(-10.0f, -10.0f);
    _world->SetGravity(gravity);

}
void World::keyPressEvent(QKeyEvent* e)
{
    //if the user presses space or enter, it checks their word and
    //gets a new one if its equal to the main word
    if(e->key() == Qt::Key_Space || e->key() == Qt::Key_Return)
    {
        int x = QString::compare(m_userWord, m_mainWord->word(), Qt::CaseInsensitive);
        if(x == 0)
        {
            m_scene->removeItem(m_mainWord);
            setWord();
            m_userWord = "";
        }
    }
    else if(e->key() == Qt::Key_Backspace) //backspace erases the user's word
    {
        m_userWord = "";
    }
    else
    {
        //use regualr expression to check if its a valid letter
        QRegExp re("\\w*");  // a word (\w), zero or more times (*)
        if (re.exactMatch(e->text()))
        {
            m_userWord = m_userWord + e->text();
        }
    }

//    //update the label on the GUI
//    ui->userWordLabel->setText(m_userWord);

}

void World::setWord()
{
    m_mainWord = new AngryWord(*(m_server->getWord()));
    m_scene->addItem(m_mainWord);
}


