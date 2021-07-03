#-------------------------------------------------
#
# Project created by QtCreator 2020-11-23T02:49:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorldGenerator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Model/Landmark/building.cpp \
    Model/Landmark/item.cpp \
    Model/Landmark/manmade.cpp \
    Model/Landmark/mischance.cpp \
    Model/Landmark/realty.cpp \
    Model/Landmark/settlement.cpp \
    Model/Landmark/trail.cpp \
    Model/Landmark/unit.cpp \
    Model/Landmark/water.cpp \
    Model/hero.cpp \
    Model/ideology.cpp \
    Model/landmark.cpp \
    Model/location.cpp \
    Model/meeting.cpp \
    Model/resource.cpp \
    Model/union.cpp \
    Model/world.cpp \
    Model/worldlevel.cpp \
    View/buttonwidget.cpp \
    View/description.cpp \
    View/gamefield.cpp \
    View/gamescene.cpp \
    View/pixmapitem.cpp \
    View/statepanel.cpp \
    View/statescene.cpp \
    game.cpp \
    main.cpp \
    useraction.cpp \
    view.cpp

HEADERS += \
    Model/Landmark/building.h \
    Model/Landmark/item.h \
    Model/Landmark/manmade.h \
    Model/Landmark/mischance.h \
    Model/Landmark/realty.h \
    Model/Landmark/settlement.h \
    Model/Landmark/trail.h \
    Model/Landmark/unit.h \
    Model/Landmark/water.h \
    Model/hero.h \
    Model/ideology.h \
    Model/landmark.h \
    Model/location.h \
    Model/meeting.h \
    Model/resource.h \
    Model/union.h \
    Model/world.h \
    Model/worldlevel.h \
    View/buttonwidget.h \
    View/description.h \
    View/gamefield.h \
    View/gamescene.h \
    View/pixmapitem.h \
    View/statepanel.h \
    View/statescene.h \
    game.h \
    useraction.h \
    view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ВВЕДЕНИЕ \
    Заметки \
    СПРАВКА \
    мысли_о_юнитах
