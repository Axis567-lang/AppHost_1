TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
INCLUDEPATH  += ../../app-host

TARGET        = prisma
DESTDIR       = ../../plugins

HEADERS += \
    prisma.h

SOURCES += \
    prisma.cpp
