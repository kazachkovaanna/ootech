#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H

#include "abstractitem.h"

template <typename T>
class ActivityItem : public AbstractItem<T> {
public:
    ActivityItem(const QString& note = QString())
        : AbstractItem<T>(type())
        , _note(note)
    {
    }

    inline QString getNote() const { return _note; }
    void setNote(const QString& note)
    {
        _note = note;
    }

public:
    static inline QString type() { return "ActivityItem"; }

protected:
    QString _note;
};

#endif // ACTIVITYITEM_H
