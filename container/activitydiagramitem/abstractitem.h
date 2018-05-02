#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QString>
#include <QUuid>

template <typename T>
class AbstractItem {
public:
    AbstractItem(const QString type)
        : _uuid(QUuid::createUuid().toString())
        , _type(type)
    {
    }

    AbstractItem(const AbstractItem& item)
        : _uuid(item._uuid)
        , _type(item.type)
    {
    }

    inline QString getUuid() const { return _uuid; }
    inline QString getType() const { return _type; }

    inline T getData() const { return _data; }
    void setData(const T& data)
    {
        _data = data;
    }

protected:
    QString _uuid;
    QString _type;
    T _data;
};

#endif // ABSTRACTITEM_H
