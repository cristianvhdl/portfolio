#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T12:07:37
#
#-------------------------------------------------

QT       += core gui
QT        += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets #multimedia

TARGET = AngryWords
TEMPLATE = app

SFML = ../SFML-2.3.2 # change this to point to SFML

# add '-std=c++11' to properly compile some libraries
CONFIG += c++11

SOURCES += main.cpp\
        gamewindow.cpp \
    dictionary.cpp \
    player.cpp \
    gameserver.cpp \
    angryword.cpp \
    welcomescreen.cpp \
    level.cpp \
    bobject.cpp \
    connector.cpp \
    statspage.cpp

#INCLUDEPATH += ../../include

HEADERS  += gamewindow.h \
    dictionary.h \
    player.h \
    gameserver.h \
    angryword.h \
    welcomescreen.h \
    level.h \
    bobject.h \
    connector.h \
    statspage.h

FORMS    += gamewindow.ui \
    welcomescreen.ui \
    statspage.ui

RESOURCES += \
    sounds.qrc


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/release/ -lsfml-audio-s
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/debug/ -lsfml-audio-s
#else:unix: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-audio-s

#INCLUDEPATH += $$PWD/../SFML-2.3.2/include
#DEPENDPATH += $$PWD/../SFML-2.3.2/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/libsfml-audio-s.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/libsfml-audio-s.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/sfml-audio-s.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/sfml-audio-s.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-audio-s.a

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/release/ -lsfml-graphics-s
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/debug/ -lsfml-graphics-s
#else:unix: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-graphics-s

#INCLUDEPATH += $$PWD/../SFML-2.3.2/include
#DEPENDPATH += $$PWD/../SFML-2.3.2/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/libsfml-graphics-s.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/libsfml-graphics-s.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/sfml-graphics-s.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/sfml-graphics-s.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-graphics-s.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/release/ -lsfml-network-s
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/debug/ -lsfml-network-s
else:unix: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-network-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/libsfml-network-s.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/libsfml-network-s.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/sfml-network-s.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/sfml-network-s.lib
else:unix: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-network-s.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/release/ -lsfml-system-s
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/debug/ -lsfml-system-s
else:unix: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-system-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/libsfml-system-s.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/libsfml-system-s.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/sfml-system-s.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/sfml-system-s.lib
else:unix: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-system-s.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/release/ -lsfml-window-s
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib/debug/ -lsfml-window-s
else:unix: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-window-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/libsfml-window-s.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/libsfml-window-s.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/release/sfml-window-s.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/debug/sfml-window-s.lib
else:unix: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-window-s.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2D-master/Box2D/Box2D/release/ -lBox2D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2D-master/Box2D/Box2D/debug/ -lBox2D
else:unix: LIBS += -L$$PWD/Box2D-master/Box2D/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/Box2D-master/Box2D
DEPENDPATH += $$PWD/Box2D-master/Box2D

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/Box2D/Box2D/release/libBox2D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/Box2D/Box2D/debug/libBox2D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/Box2D/Box2D/release/Box2D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/Box2D/Box2D/debug/Box2D.lib
else:unix: PRE_TARGETDEPS += $$PWD/Box2D-master/Box2D/Box2D/libBox2D.a

DISTFILES += \
    graphics/instructions.png \
    graphics/menu_button.png \
    graphics/music_button.png \
    graphics/pause_button.png \
    graphics/paused_text.png \
    graphics/playagain_button.png \
    graphics/play_button.png \
    graphics/restart_button.png \
    graphics/sound_button.png \
    graphics/stats_button.png

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/lib/release/ -lmysqlclient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/lib/debug/ -lmysqlclient
else:unix: LIBS += -L$$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/include
DEPENDPATH += $$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/include

unix:!macx: LIBS += -L$$PWD/../../../../Desktop/mysql-5.7.12-linux-glibc2.5-x86_64/lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../../../../Desktop/mysql-5.7.12-linux-glibc2.5-x86_64/include
DEPENDPATH += $$PWD/../../../../Desktop/mysql-5.7.12-linux-glibc2.5-x86_64/include
