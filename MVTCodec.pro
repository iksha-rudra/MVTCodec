TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH = /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lprotobuf
LIBS += -lpthread

SOURCES += main.cpp \
    VectorTile.cpp \
    vector_tile.pb.cc \
    geometrycodec.cpp \
    point2di.cpp

HEADERS += \
    VectorTile.h \
    vector_tile.pb.h \
    geometrycodec.h \
    mvtcommon.h \
    point2di.h

DISTFILES += \
    vector_tile21/vector_tile.proto

