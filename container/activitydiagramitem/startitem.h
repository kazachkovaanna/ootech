#ifndef STARTITEM_H
#define STARTITEM_H

#include "abstractitem.h"

template <typename T>
class StartItem : public AbstractItem<T> {
public:
    StartItem()
        : AbstractItem<T>(type())
    {
    }

public:
    static inline QString type() { return "StartItem"; }
};

#endif // STARTITEM_H
