INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

#include(activitydiagramitem/ActivityDiagramItem.pri)

HEADERS += \
    $$PWD/graph.h \
    $$PWD/allocator.h \
    $$PWD/manipulator.h \
    $$PWD/graphexception.h

SOURCES += \
    $$PWD/graphexception.cpp
