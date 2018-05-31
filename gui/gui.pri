INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("$$PWD/graphicsItem/graphicsItem.pri")

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/graphicsview.h \
    $$PWD/algorithmdialog.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/graphicsview.cpp \
    $$PWD/algorithmdialog.cpp

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/algorithmdialog.ui
