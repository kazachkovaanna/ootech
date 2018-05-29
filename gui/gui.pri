INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("$$PWD/graphicsItem/graphicsItem.pri")

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/graphicsview.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/graphicsview.cpp

FORMS += \
    $$PWD/mainwindow.ui
