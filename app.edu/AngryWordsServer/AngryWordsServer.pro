#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T11:21:31
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AngryWordsServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SFML = ../SFML-2.3.2 # change this to point to SFML

#LIBS = -I$(SFML)/include -L$(SFML)/lib -lsfml-audio-s -lsfml-window-s -lsfml-graphics-s -lsfml-network-s -lsfml-system-s

#LIBS += -L"../../lib"
#LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += main.cpp \
    gameserver.cpp \
    connector.cpp

HEADERS += \
    gameserver.h \
    connector.h

unix:!macx: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-network-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-network-s.a

unix:!macx: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-system-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-system-s.a

unix:!macx: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-window-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-window-s.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/lib/release/ -lmysqlclient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/lib/debug/ -lmysqlclient
else:unix: LIBS += -L$$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/include
DEPENDPATH += $$PWD/../../../mysql-5.7.12-linux-glibc2.5-x86_64/include
