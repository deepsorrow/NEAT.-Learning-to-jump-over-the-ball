#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T19:35:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkAlgorhitm
TEMPLATE = app

SOURCES += main.cpp \
    environment.cpp \
    polygons.cpp \
    geneticalgorithm.cpp \
    neuralnet.cpp

HEADERS  += \
    environment.h \
    polygons.h \
    geneticalgorithm.h \
    neuralnet.h

unix:!macx|win32: LIBS += -L$$PWD/../testbed/ -lBox2D_Library

INCLUDEPATH += $$PWD/../testbed
DEPENDPATH += $$PWD/../testbed

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../testbed/Box2D_Library.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../testbed/libBox2D_Library.a

LIBS += -L"/home/rootuser/Desktop/SFML-master/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += "/home/rootuser/Desktop/SFML-master/include"
DEPENDPATH += "/home/rootuser/Desktop/SFML-master/include"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/release/ -lsfml-window-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/debug/ -lsfml-window-d
else:unix:!macx: LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/ -lsfml-window-d

INCLUDEPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include
DEPENDPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include

unix:!macx|win32: LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/ -lsfml-graphics-d

INCLUDEPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include
DEPENDPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include

unix:!macx|win32: LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/ -lsfml-audio-d

INCLUDEPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include
DEPENDPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include

unix:!macx|win32: LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/ -lsfml-network-d

INCLUDEPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include
DEPENDPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include

unix:!macx|win32: LIBS += -L$$PWD/../../../Desktop/sfmlbuild/SFML-master/lib/ -lsfml-system-d

INCLUDEPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include
DEPENDPATH += $$PWD/../../../Desktop/sfmlbuild/SFML-master/include

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ -lBox2D_Library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ -lBox2D_Libraryd
else:unix:!macx: LIBS += -L$$PWD/../ -lBox2D_Library

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
