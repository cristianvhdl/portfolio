/****************************************************************************
** Meta object code from reading C++ file 'gamewindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AngryWords/gamewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   23,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x0a,
      87,   11,   11,   11, 0x0a,
     107,   11,   11,   11, 0x0a,
     123,   11,   11,   11, 0x0a,
     138,   11,   11,   11, 0x0a,
     150,   11,   11,   11, 0x0a,
     161,   11,   11,   11, 0x0a,
     173,   11,   11,   11, 0x0a,
     187,   11,   11,   11, 0x0a,
     198,   11,   11,   11, 0x0a,
     212,   11,   11,   11, 0x0a,
     229,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GameWindow[] = {
    "GameWindow\0\0mainMenu()\0paused\0"
    "pauseWords(bool)\0playMusic()\0stopMusic()\0"
    "slowDownWords()\0updateProgressBar()\0"
    "enablePowerUp()\0speedUpWords()\0"
    "startGame()\0gameOver()\0pauseGame()\0"
    "unPauseGame()\0playGame()\0restartGame()\0"
    "backToMainMenu()\0spawnAnAngryBird()\0"
};

void GameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameWindow *_t = static_cast<GameWindow *>(_o);
        switch (_id) {
        case 0: _t->mainMenu(); break;
        case 1: _t->pauseWords((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->playMusic(); break;
        case 3: _t->stopMusic(); break;
        case 4: _t->slowDownWords(); break;
        case 5: _t->updateProgressBar(); break;
        case 6: _t->enablePowerUp(); break;
        case 7: _t->speedUpWords(); break;
        case 8: _t->startGame(); break;
        case 9: _t->gameOver(); break;
        case 10: _t->pauseGame(); break;
        case 11: _t->unPauseGame(); break;
        case 12: _t->playGame(); break;
        case 13: _t->restartGame(); break;
        case 14: _t->backToMainMenu(); break;
        case 15: _t->spawnAnAngryBird(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GameWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GameWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GameWindow,
      qt_meta_data_GameWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameWindow))
        return static_cast<void*>(const_cast< GameWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void GameWindow::mainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
