INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("$$PWD/graphicsItem/graphicsItem.pri")

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/graphicsview.h \
    $$PWD/algorithmdialog.h \
    $$PWD/settingsdialog.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/graphicsview.cpp \
    $$PWD/algorithmdialog.cpp \
    $$PWD/settingsdialog.cpp

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/algorithmdialog.ui \
    $$PWD/settingsdialog.ui

RESOURCES += \
    $$PWD/res.qrc
