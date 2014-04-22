# -------------------------------------------------
# Project created by QtCreator 2011-06-16T09:55:28
# -------------------------------------------------
QT += gui widgets core

win32: CONFIG += qt plugin
unix: CONFIG += dll plugin debug
INCLUDEPATH += ../../include ../../graphics/include ../../specctra/include
TARGET = simplerouter
TEMPLATE = lib
unix {
	target.path = /opt/qautorouter/plugins
	INSTALLS += target
}
SOURCES += simplerouter.cpp \
    castarnode.cpp \
    castar.cpp \
    castarmarker.cpp
HEADERS += simplerouter.h \
    castarnode.h \
    castar.h \
    castarmarker.h
OTHER_FILES += README.txt \
    simplerouter.json
unix: LIBS += -L../../specctra -lspecctra
win32: LIBS += -L../../../qautorouter-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK__Debug/specctra/release -L../../../qautorouter-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK__Debug/specctra/debug -lspecctra
