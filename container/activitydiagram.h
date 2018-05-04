#ifndef ACTIVITYDIAGRAM_H
#define ACTIVITYDIAGRAM_H

#include <QList>
#include <QMap>

template <typename Node> class ActivityDiagram
{
public:
    ActivityDiagram()
        : _start(new Node)
        , _stop(new Node)
    {
        _itemLinks.insert(_start, _stop);
    }

    ~ActivityDiagram()
    {
        for (Node* item : _items)
        {
            delete item;
        }

        delete _start;
        delete _stop;
    }

    inline bool isEmpty() const
    {
        return _itemLinks.isEmpty();
    }

    bool contains(Node* item) const
    {
        return item == _start || item == _stop || _items.contains(item);
    }

    inline int size() const
    {
        return _items.size() + 2;
    }

    void insert(Node* preview, Node* node)
    {
        // TODO
        if (contains(node))
            return;

        for (Node* next : _itemLinks.values(preview))
        {
            _itemLinks.insertMulti(node, next);
        }

        _itemLinks.insert(preview, node);
        _items.append(node);
    }

    void insert(Node* preview, Node* node, Node* next)
    {
        // TODO
        if (!_items.contains(node))
        {
            if (_start == node || _stop == node)
                return;

            _items.append(node);
        }

        if (!_itemLinks.contains(preview, node))
            _itemLinks.insertMulti(preview, node);

        if (_itemLinks.contains(node, next))
            _itemLinks.insertMulti(node, next);
    }

    void remove(Node* node)
    {
        // TODO
        if (!_items.contains(node))
            return;

        _items.removeOne(node);
        QList<Node*> childrens = _itemLinks.values(node);
        QList<Node*> parents = getParents(node);
        _itemLinks.remove(node);

        for (Node* from : parents)
        {
            for (Node* to : childrens)
            {
                _itemLinks.remove(from, node);
                if (!hasLink(from, to))
                {
                    _itemLinks.insert(from, to);
                }
            }
        }
    }

    // iterator
    class iterator
    {
        iterator(QMap<Node*, Node*>& map, bool begin)
            : _key(nullptr)
            , _value(nullptr)
            , _map(map)
        {
            if (!begin)
                return;

            if (!_map.isEmpty())
            {
                _key = _map.begin().key();
                _value = _map.begin().value();
            }
        }

    public:
        iterator(const iterator& it)
            : _key(it._key)
            , _value(it._value)
            , _map(it._map)
        {
        }

        Node* operator*()
        {
            return _value;
        }

        iterator& operator++()
        {
            if (nullptr == _key || nullptr == _value)
                return *this;

            QList<Node*> values = _map.values(_key);
            int valueIndex = values.indexOf(_value);
            if (values.size() > ++valueIndex)
            {
                _value = values[valueIndex];
                return *this;
            }

            QList<Node*> keys = _map.keys();
            int keyIndex = keys.indexOf(_key);
            if (keys.size() > ++keyIndex)
            {
                _key = keys[keyIndex];
                _value = _map.value(_key);
            }
            else
            {
                _key = nullptr;
                _value = nullptr;
            }

            return *this;
        }

        inline bool operator==(const iterator& i) const
        {
            return _key == i._key && _value == i._value;
        }

        inline bool operator!=(const iterator& i) const
        {
            return _key != i._key || _value != i._value;
        }

        friend class ActivityDiagram;

    protected:
        Node* _key;
        Node* _value;
        QMap<Node*, Node*>& _map;
    };

    iterator begin()
    {
        return iterator(_itemLinks, true);
    }
    iterator end()
    {
        return iterator(_itemLinks, false);
    }

protected:
    bool hasLink(const Node* from, const Node* to, QList<Node*>& visited = QList<Node*>()) const
    {
        if (_itemLinks.contains(from, to))
            return true;

        for (Node* newFrom : _itemLinks.values(from))
        {
            if (!visited.contains(newFrom))
            {
                visited.append(newFrom);
                if (hasLink(newFrom, to))
                    return true;
            }
        }

        return false;
    }

    QList<Node*> getParents(Node* node) const
    {
        QList<Node*> result;

        for (const QMapNode<Node*, Node*>& pair : _itemLinks)
        {
            if (pair.value == node)
                result.append(pair.key);
        }

        return result;
    }

protected:
    const Node* _start;
    const Node* _stop;

    QList<Node*> _items;
    QMap<Node*, Node*> _itemLinks;
};

#endif // ACTIVITYDIAGRAM_H
