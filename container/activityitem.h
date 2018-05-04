#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H

#include <QString>

template <typename T> class ActivityItem
{
public:
    ActivityItem(const QString& note, const T& data)
        : _note(note)
        , _data(data)
    {
    }

    ActivityItem(const ActivityItem<T>& item)
        : _note(item.note())
        , _data(item.data())
    {
    }

    inline QString note() const
    {
        return _note;
    }
    void setNote(const QString& note)
    {
        _note = note;
    }

    inline T data() const
    {
        return _data;
    }
    void setData(const T& data)
    {
        _data = data;
    }

protected:
    QString _note;
    T _data;
};

#endif // ACTIVITYITEM_H
