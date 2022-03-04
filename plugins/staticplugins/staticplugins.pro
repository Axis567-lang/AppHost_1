TEMPLATE      = lib
CONFIG       += plugin static
QT           += widgets
INCLUDEPATH  += ../../app-host
HEADERS += \
    cube.h \
    sphere.h

SOURCES += \
    cube.cpp \
    sphere.cpp

TARGET        = staticplugins
if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
   mac:TARGET = staticplugins_debug
   win32:TARGET = staticpluginsd
}

DESTDIR       = ../../plugins


