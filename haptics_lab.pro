# changed here
QT    += core
TARGET = haptic_lab
# chenged here
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
# changed here
# CONFIG -= qt
# changed here

SOURCES += Main.cpp \
    watergame.cpp \
    gamemap.cpp \
    wave.cpp \
    rock.cpp \
    iceberg.cpp \
    whirpool.cpp \
    current.cpp \
    exit.cpp
HEADERS += 1_HelloWorld.h 4_HapticWall.h Assignment.h 2_ReadDevicePosition.h 5_MagneticEffect.h 3_BasicForceEffects.h 6_HapticSphere.h \
    watergame.h \
    gamemap.h \
    wave.h \
    rock.h \
    iceberg.h \
    whirpool.h \
    current.h \
    exit.h


INCLUDEPATH += $$PWD/../chai3d-3.0.0/src
INCLUDEPATH += $$PWD/../chai3d-3.0.0/external/Eigen
INCLUDEPATH += $$PWD/../chai3d-3.0.0/external/glew/include

unix {
    DEFINES += LINUX
    QMAKE_CXXFLAGS += -std=c++0x -Wno-unused-variable
    LIBS += -L$$PWD/../chai3d-3.0.0/lib/release/lin-x86_64-cc/ -lchai3d
    #LIBS += -L$$PWD/../chai3d-3.0.0/lib/debug/lin-x86_64-cc/ -lchai3d
    LIBS += -L$$PWD/../chai3d-3.0.0/external/DHD/lib/lin-x86_64/ -ldrd
    LIBS += -lusb-1.0
    LIBS += -lpthread -lrt -ldl -lGL -lGLU -lglut
}



