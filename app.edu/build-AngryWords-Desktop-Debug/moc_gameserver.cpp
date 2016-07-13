/****************************************************************************
** Meta object code from reading C++ file 'gameserver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AngryWords/gameserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      22,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x0a,
      43,   11,   11,   11, 0x0a,
      64,   11,   55,   11, 0x0a,
      85,   74,   11,   11, 0x0a,
     111,   11,  104,   11, 0x0a,
     138,  131,   11,   11, 0x0a,
     232,   11,  208,   11, 0x0a,
     269,  267,  252,   11, 0x0a,
     291,  288,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GameServer[] = {
    "GameServer\0\0newGame()\0endGame()\0"
    "newEnemy()\0checkWord()\0QString*\0"
    "getWord()\0difficulty\0getDictionary(int)\0"
    "string\0receiveFromServer()\0,,,,,,\0"
    "sendToServer(QString,QString,QString,QString,QString,QString,QString)\0"
    "vector<vector<string> >\0getEntireDatabase()\0"
    "vector<string>\0,\0split(string,char)\0"
    ",,\0split(string,char,vector<string>&)\0"
};

void GameServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameServer *_t = static_cast<GameServer *>(_o);
        switch (_id) {
        case 0: _t->newGame(); break;
        case 1: _t->endGame(); break;
        case 2: _t->newEnemy(); break;
        case 3: _t->checkWord(); break;
        case 4: { QString* _r = _t->getWord();
            if (_a[0]) *reinterpret_cast< QString**>(_a[0]) = _r; }  break;
        case 5: _t->getDictionary((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { string _r = _t->receiveFromServer();
            if (_a[0]) *reinterpret_cast< string*>(_a[0]) = _r; }  break;
        case 7: _t->sendToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 8: { vector<vector<string> > _r = _t->getEntireDatabase();
            if (_a[0]) *reinterpret_cast< vector<vector<string> >*>(_a[0]) = _r; }  break;
        case 9: { vector<string> _r = _t->split((*reinterpret_cast< const string(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< vector<string>*>(_a[0]) = _r; }  break;
        case 10: _t->split((*reinterpret_cast< const string(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2])),(*reinterpret_cast< vector<string>(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GameServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GameServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GameServer,
      qt_meta_data_GameServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameServer))
        return static_cast<void*>(const_cast< GameServer*>(this));
    return QObject::qt_metacast(_clname);
}

int GameServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
