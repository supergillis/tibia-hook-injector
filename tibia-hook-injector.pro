QT += core
QT -= gui

TEMPLATE = app

TARGET = tibia-hook-injector
CONFIG += console

SOURCES += src/Main.cpp \
    src/Initializer.cpp
HEADERS += src/Injector.h \
    src/Initializer.h

unix {
    HEADERS += src/UnixInjector.h
    SOURCES += src/UnixInjector.cpp
}

win32 {
    HEADERS += src/WindowsInjector.h
    SOURCES += src/WindowsInjector.cpp
}
