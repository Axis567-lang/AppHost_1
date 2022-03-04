TARGET = myapp-host
DESTDIR = ..

QT += widgets core gui openglwidgets

LIBS           = -L../plugins -lstaticplugins

if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
   mac:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)_debug
   win32:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)d
}

HEADERS += \
    blenderdialog.h \
    interfaces.h \
    mayadialog.h \
    vertexdata.h \
    geometry.h \
    mainwidget.h \
    MainWindow.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

FORMS += \
    MainWindow.ui \
    blenderdialog.ui \
    mayadialog.ui

SOURCES += \
    blenderdialog.cpp \
    geometry.cpp \
    main.cpp \
    mainwidget.cpp \
    MainWindow.cpp \
    mayadialog.cpp

