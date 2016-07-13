
#include "bobject.h"

/*
BObject::BObject(float32 x, float32 y, float32 w, float32 h, float32 angle, )
{
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
}*/

BObject::~BObject()
{
    delete this->pixmapItem;
}
