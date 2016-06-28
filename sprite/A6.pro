#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T15:19:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A6
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    maineditor.cpp \
    preview.cpp \
    frames.cpp \
    startwindow.cpp

HEADERS  += mainwindow.h \
    maineditor.h \
    preview.h \
    frames.h \
    menubar.h \
    startwindow.h

FORMS    += mainwindow.ui \
    startwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    images/Stop Filled-50.png

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lMagick++
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lMagick++
else:unix: LIBS += -L$$PWD/./ -lMagick++

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lMagickCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lMagickCore
else:unix: LIBS += -L$$PWD/./ -lMagickCore

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
