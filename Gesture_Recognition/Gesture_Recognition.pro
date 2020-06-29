TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        readFile.c \
        snapshot.c \
        snapshotAnalysis.c

HEADERS += \
    readFile.h \
    snapshot.h \
    snapshotAnalysis.h \
    structure.h
