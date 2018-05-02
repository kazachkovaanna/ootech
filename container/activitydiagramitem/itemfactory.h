#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QMap>

#include "abstractitem.h"
#include "activityitem.h"
#include "synchronizationitem.h"
#include "startitem.h"
#include "stopitem.h"

template <typename T>
class ItemFactory {
private:
    ItemFactory()
    {
        add<StartItem>();
        add<StopItem>();
        add<ActivityItem>();
        add<SynchronizationItem>();
    }

    ~ItemFactory() = default;

    ItemFactory(const ItemFactory&) = delete;
    ItemFactory operator=(const ItemFactory&) = delete;

    template <typename Type>
    static AbstractItem<T>* create() { return new Type; }

    template <typename Type>
    void add() { _creatorMap.insert(Type::type(), create<Type>); }

    typedef AbstractItem<T>* (*ItemCreator)();

public:
    AbstractItem<T>* item(const QString& type)
    {
        return _creatorMap.contains(type) ? _creatorMap.value(type)() : nullptr;
    }

public:
    static ItemFactory<T>& instance()
    {
        static ItemFactory itemFactory;
        return itemFactory;
    }

private:
    QMap<QString, ItemCreator> _creatorMap;
};

#endif // ITEMFACTORY_H
