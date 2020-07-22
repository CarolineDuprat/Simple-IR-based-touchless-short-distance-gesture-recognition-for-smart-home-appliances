TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        generateSnapshot.c \
        gesture.c \
        main.c \
        readFile.c \
        snapshot.c \
        snapshotAnalysis.c

HEADERS += \
    generateSnapshot.h \
    gesture.h \
    gesture.h \
    readFile.h \
    snapshot.h \
    snapshotAnalysis.h \
    structure.h
