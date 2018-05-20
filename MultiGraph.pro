QT += core gui widgets

TARGET = MultiGraph
TEMPLATE = app

include($$PWD/defines/christmasTree.pri)
include($$PWD/container/container.pri)
include($$PWD/algorithm/algorithm.pri)
include($$PWD/gui/gui.pri)

SOURCES += \
        main.cpp
