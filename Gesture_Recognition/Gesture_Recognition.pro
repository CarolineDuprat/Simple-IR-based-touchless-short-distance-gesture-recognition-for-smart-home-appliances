TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        readFile.c \
        snapshot.c

HEADERS += \
    readFile.h \
    snapshot.h \
    structure.h
