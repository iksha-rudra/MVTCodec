TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH = /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lprotobuf
LIBS += -lpthread

SOURCES += main.cpp \
    vector_tile.pb.cc \
    cgmvectortile.cpp \
    cgmvtlayer.cpp \
    cgmvtfeature.cpp \
    cgmvtgeometry.cpp

HEADERS += \
    vector_tile.pb.h \
    cgmvectortile.h \
    cgmvtlayer.h \
    cgmvtfeature.h \
    cgmvtcommon.h \
    cgmvtgeometry.h

DISTFILES += \
    vector_tile.proto

