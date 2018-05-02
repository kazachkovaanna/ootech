#ifndef ACTIVITYDIAGRAM_H
#define ACTIVITYDIAGRAM_H

#include <QList>

#include "itemfactory.h"

template <typename T>
class ActivityDiagram {
protected:
    class ActivitySequence {
        ActivitySequence();

    protected:
        StopItem<T>* _stop;
        SynchronizationItem<T>* _sync;
        QList<ActivityItem<T>*> _activitySequence;
    };

protected:
    QList<AbstractItem<T>*> _startItems;
    QMap<SynchronizationItem<T>*, int> _activityItem;
};

#endif // ACTIVITYDIAGRAM_H
