QT       += core gui widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gamecubeobject.cpp \
    gameearthobject.cpp \
    gamemoonobject.cpp \
    gameobject.cpp \
    gamescene.cpp \
    gamesunobject.cpp \
    gameterrainobject.cpp \
    transform.cpp

SOURCES +=

HEADERS += \
    ProceduralLib/Noise.h \
    ProceduralLib/Vector3.h \
    gamecubeobject.h \
    gameearthobject.h \
    gamemoonobject.h \
    gameobject.h \
    gamescene.h \
    gamesunobject.h \
    gameterrainobject.h \
    transform.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target
