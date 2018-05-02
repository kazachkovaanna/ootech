#ifndef STOPITEM_H
#define STOPITEM_H

#include "abstractitem.h"

template <typename T>
class StopItem : public AbstractItem<T> {
public:
    StopItem()
        : AbstractItem<T>(type())
    {
    }

public:
    static inline QString type() { return "StopItem"; }
};

#endif // STOPITEM_H
