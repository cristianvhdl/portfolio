/****************************************************************************
** Meta object code from reading C++ file 'welcomescreen.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AngryWords/welcomescreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'welcomescreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WelcomeScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   14,   14,   14, 0x0a,
      58,   14,   14,   14, 0x0a,
      79,   14,   14,   14, 0x0a,
     100,   14,   14,   14, 0x0a,
     115,   14,   14,   14, 0x0a,
     143,   14,   14,   14, 0x08,
     172,  167,   14,   14, 0x08,
     212,  167,   14,   14, 0x08,
     244,  167,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WelcomeScreen[] = {
    "WelcomeScreen\0\0playGame()\0showStats()\0"
    "playButtonClicked()\0guestButtonClicked()\0"
    "statsButtonClicked()\0showMainMenu()\0"
    "teacherStatsButtonClicked()\0"
    "on_playButton_pressed()\0arg1\0"
    "on_usernameTextbox_textChanged(QString)\0"
    "on_teacherBox_stateChanged(int)\0"
    "on_studentBox_stateChanged(int)\0"
};

void WelcomeScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WelcomeScreen *_t = static_cast<WelcomeScreen *>(_o);
        switch (_id) {
        case 0: _t->playGame(); break;
        case 1: _t->showStats(); break;
        case 2: _t->playButtonClicked(); break;
        case 3: _t->guestButtonClicked(); break;
        case 4: _t->statsButtonClicked(); break;
        case 5: _t->showMainMenu(); break;
        case 6: _t->teacherStatsButtonClicked(); break;
        case 7: _t->on_playButton_pressed(); break;
        case 8: _t->on_usernameTextbox_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_teacherBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_studentBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WelcomeScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WelcomeScreen::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WelcomeScreen,
      qt_meta_data_WelcomeScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WelcomeScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WelcomeScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WelcomeScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WelcomeScreen))
        return static_cast<void*>(const_cast< WelcomeScreen*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WelcomeScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void WelcomeScreen::playGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WelcomeScreen::showStats()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
