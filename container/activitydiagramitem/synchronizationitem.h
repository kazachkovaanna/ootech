#ifndef SYNCHRONIZATIONITEM_H
#define SYNCHRONIZATIONITEM_H

#include "abstractitem.h"

template <typename T>
class SynchronizationItem : public AbstractItem<T> {
public:
    SynchronizationItem()
        : AbstractItem<T>(type())
    {
    }

public:
    static inline QString type() { return "SinchronizationItem"; }
};

#endif // SYNCHRONIZATIONITEM_H
