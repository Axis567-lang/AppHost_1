TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
INCLUDEPATH  += ../../app-host

TARGET        = dynamicplugins
DESTDIR       = ../../plugins

HEADERS += \
    cylinder.h

SOURCES += \
    cylinder.cpp
