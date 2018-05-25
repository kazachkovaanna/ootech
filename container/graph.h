#ifndef GRAPH_H
#define GRAPH_H

#include <QDataStream>
#include <QList>
#include <QMap>
#include <QPair>
#include <QStringList>
#include <QUuid>
#include <QDebug>

#include "allocator.h"
#include "manipulator.h"

namespace Sence {
// clang-format off
    template<typename V> class Vertex;
    template<typename E> class Edge;
    template<typename V, typename E> class Graph;
// clang-format on
}

template <typename V>
class Sence::Vertex {
public:
    Vertex(const V& data = V()) noexcept
        : _data(data)
        , _uuid(QUuid::createUuid().toString())
    {
    }

    Vertex(const Vertex<V>& vertex) noexcept = default;

    inline V getData() const noexcept { return _data; }
    void setData(const V& data) noexcept { _data = data; }

    inline const QString& getUuid() const noexcept { return _uuid; }

    bool operator==(const Vertex<V>& v) const noexcept { return _uuid == v._uuid && _data == v._data; }
    bool operator!=(const Vertex<V>& v) const noexcept { return _uuid != v._uuid || _data == v._data; }

    void* operator new(size_t size) noexcept(false)
    {
        Q_UNUSED(size)

        return GraphAllocator<Vertex<V>>::instance().allocate();
    }

    void operator delete(void* ptr)noexcept(false)
    {
        GraphAllocator<Vertex<V>>::instance().deallocate(reinterpret_cast<Vertex<V>*>(ptr));
    }

    template<typename _V>
    friend QDataStream& ::operator>>(QDataStream&, Vertex<_V>*&) noexcept;
    template<typename _V>
    friend QDataStream& ::operator<<(QDataStream&, const Vertex<_V>*) noexcept;

protected:
    V _data;
    QString _uuid;
};

template <typename E>
class Sence::Edge {
public:
    Edge(const E& data = E()) noexcept
        : _data(data)
        , _uuid(QUuid::createUuid().toString())
    {
    }

    Edge(const Edge<E>& edge) noexcept = default;

    inline E getData() const noexcept { return _data; }
    void setData(const E& data) noexcept { _data = data; }

    inline const QString& getUuid() const noexcept { return _uuid; }

    bool operator==(const Edge<E>& e) const noexcept { return _uuid == e._uuid && _data == e._data; }
    bool operator!=(const Edge<E>& e) const noexcept { return _uuid != e._uuid || _data == e._data; }

    void* operator new(size_t size) noexcept(false)
    {
        Q_UNUSED(size)

        return GraphAllocator<Edge<E>>::instance().allocate();
    }

    void operator delete(void* ptr) noexcept(false)
    {
        GraphAllocator<Edge<E>>::instance().deallocate(reinterpret_cast<Edge<E>*>(ptr));
    }

    template<typename _E>
    friend QDataStream& ::operator>>(QDataStream&, Edge<_E>*&) noexcept;
    template<typename _E>
    friend QDataStream& ::operator<<(QDataStream&, const Edge<_E>*) noexcept;

protected:
    E _data;
    QString _uuid;
};

template <typename V, typename E>
class Sence::Graph {
public:
    Graph() noexcept = default;
    Graph(const Graph<V, E>& graph) noexcept = default;

    inline bool isEmpty() const noexcept { return _vertices.isEmpty(); }
    inline bool contains(Vertex<V>* vertex) const noexcept { return _vertices.value(vertex->getUuid()) == vertex; }
    inline bool contains(Edge<E>* edge) const noexcept { return _edges.value(edge->getUuid()) == edge; }

    void add(Vertex<V>* vertex) noexcept
    {
        if (vertex == nullptr)
            return;

        _vertices.insert(vertex->getUuid(), vertex);
    }

    void add(Vertex<V>* from, Vertex<V>* to, Edge<E>* edge) noexcept
    {
        if (edge == nullptr)
            return;

        if (from == nullptr || !_vertices.contains(from->getUuid()))
            return;

        if (to == nullptr || !_vertices.contains(to->getUuid()))
            return;

        if (_edges.contains(edge->getUuid()))
            return;

        _edges.insert(edge->getUuid(), edge);
        _connections.insertMulti(from->getUuid(), edge->getUuid());
        _connections.insertMulti(to->getUuid(), edge->getUuid());
    }

    // cascade remove
    QPair<Vertex<V>*, QList<Edge<E>*>> remove(const Vertex<V>* vertex) noexcept
    {
        _vertices.remove(vertex->getUuid());
        QList<QString> edges = _edges.values(vertex->getUuid());
        for (auto e : edges) {
            remove(_edges.value(e));
        }

        return qMakePair(vertex, edges);
    }

    Edge<E>* remove(Edge<E>* edge) noexcept
    {
        QList<Vertex<V>*> vertices = _connections.keys(edge);
        for (auto v : vertices) {
            auto edges = _connections.values(v);
            edges.removeOne(edge);

            _connections.remove(v);
            for (auto e : edges) {
                _connections.insertMulti(v, e);
            }
        }
    }

    inline Vertex<V>* getVertex(const QString& uuid) { return _vertices.value(uuid);}
    inline Vertex<V>* getEdge(const QString& uuid) { return _edges.value(uuid);}

    class iteratorE {
        iteratorE(const QList<Edge<E>*>& edges, bool begin) noexcept
            : _edges(edges)
            , _pointer(nullptr)
        {
            if (begin && !edges.isEmpty())
                _pointer = edges[0];
        }

    public:
        iteratorE(const iteratorE& it) noexcept = default;

        iteratorE& operator++() noexcept
        {
            int number = _edges.indexOf(_pointer);
            if (number != -1 && _edges.last() != _pointer)
                _pointer = _edges[number + 1];
            else
                _pointer = nullptr;

            return *this;
        }

        inline bool operator==(const iteratorE& it) noexcept
        {
            return _pointer == it._pointer && _edges == it._edges;
        }

        inline bool operator!=(const iteratorE& it) noexcept
        {
            return _pointer != it._pointer || _edges != it._edges;
        }

        inline Edge<E>* operator*() noexcept
        {
            return _pointer;
        }

        inline Edge<E>* operator->() noexcept
        {
            return _pointer;
        }

        friend class Graph<V, E>;

    protected:
        QList<Edge<E>*>& _edges;
        Edge<E>* _pointer;
    };

    class iteratorV {
        iteratorV(const QList<Vertex<V>*>& vertices, bool begin) noexcept
            : _vertices(vertices)
            , _pointer(nullptr)
        {
            if (begin && !vertices.isEmpty()) {
                _pointer = _vertices[0];
            }
        }

    public:
        iteratorV(const iteratorV& it) noexcept = default;

        iteratorV& operator++() noexcept
        {
            int number = _vertices.indexOf(_pointer);
            if (number != -1 || _vertices.last() < _pointer)
                _pointer = _vertices[number + 1];
            else
                _pointer = nullptr;

            return *this;
        }

        iteratorV& operator++(const iteratorV&) noexcept
        {
            iteratorV current;

            int number = _vertices.indexOf(_pointer);
            if (number != -1 || _vertices.last() < _pointer)
                _pointer = _vertices[number + 1];
            else
                _pointer = nullptr;

            return current;
        }

        inline bool operator==(const iteratorV& it) noexcept
        {
            return _pointer == it._pointer && _vertices == it._vertices;
        }
        inline bool operator!=(const iteratorV& it) noexcept
        {
            return _pointer != it._pointer || _vertices != it._vertices;
        }

        inline Vertex<V>* operator*() noexcept
        {
            return _pointer;
        }
        inline Vertex<V>* operator->() noexcept
        {
            return _pointer;
        }

        friend class Graph<V, E>;

    protected:
        QList<Vertex<V>*>& _vertices;
        Vertex<V>* _pointer;
    };

    iteratorV begin() noexcept { return iteratorV(_vertices.values(), true); }
    iteratorV end() noexcept { return iteratorV(_vertices.values(), false); }

    iteratorE begin(Vertex<V>* vertex) noexcept
    {
        // TODO throw nullpointer
        return iteratorE(_connections.values(vertex->getUuid()), true);
    }

    iteratorE end(Vertex<V>* vertex) noexcept
    {
        // TODO throw nullpointer
        return iteratorE(_connections.values(vertex->getUuid()), false);
    }

    QList<Vertex<V>*> verticesByEdge(Edge<E>* edge) const noexcept
    {
        QList<Vertex<V>*> vertices;
        for (const QString& v : _connections.keys(edge->getUuid())) {
            vertices.append(_vertices.value(v));
        }

        return vertices;
    }

    inline QList<Edge<E>*> edgesByVertex(Vertex<V>* vertex) const noexcept
    {
        QList<Edge<E>*> edges;

        for (const QString& e : _connections.values(vertex->getUuid())) {
            edges.append(_edges.value(e));
        }

        return edges;
    }

    template<typename _V, typename _E>
    friend QDataStream& ::operator>>(QDataStream&, Graph<_V, _E>&) noexcept;
    template<typename _V, typename _E>
    friend QDataStream& ::operator<<(QDataStream&, const Graph<_V, _E>&) noexcept;

protected:
    QMap<QString, Vertex<V>*> _vertices;
    QMap<QString, Edge<E>*> _edges;
    QMap<QString, QString> _connections;        // { V, [E1, ...]}
};

template <typename V, typename E>
QDataStream& operator<<(QDataStream& stream, const Sence::Graph<V, E>& graph) noexcept
{
    stream << setVersion(QDataStream::Qt_5_10);

    stream.resetStatus();

    stream << graph._vertices;
    stream << graph._edges;
    stream << graph._connections;

    if (stream.status() != QDataStream::Ok)
        throw 2; // TODO serialize exception
}

template <typename V, typename E>
QDataStream& operator>>(QDataStream& stream, Sence::Graph<V, E>& graph) noexcept
{
    stream << setVersion(QDataStream::Qt_5_10);

    stream.startTransaction();

    stream >> graph._vertices;
    stream >> graph._edges;
    stream >> graph._connections;

    if (!stream.commitTransaction())
        throw 2; // TODO deserialize exception
}

template <typename V>
QDataStream& operator<<(QDataStream& stream, const Sence::Vertex<V>* vertex) noexcept
{
    if (nullptr == vertex) {
        stream.setStatus(QDataStream::WriteFailed);
        throw 0; // TODO nullptr
    }

    stream.resetStatus();

    stream << vertex->_data;
    stream << vertex->_uuid;

    if (stream.status() != QDataStream::Ok)
        throw 3; // TODO throw serialize exception;

    return stream;
}

template <typename V>
QDataStream& operator>>(QDataStream& stream, Sence::Vertex<V>*& vertex) noexcept
{
    stream.startTransaction();

    vertex = new Sence::Vertex<V>;
    stream >> vertex->_data;
    stream >> vertex->_uuid;

    if (!stream.commitTransaction())
        throw 0; // TODO deserialize exc;

    return stream;
}

template <typename E>
QDataStream& operator<<(QDataStream& stream, const Sence::Edge<E>* edge) noexcept
{
    if (nullptr == edge) {
        stream.setStatus(QDataStream::WriteFailed);
        throw 0; // TODO nullptr
    }

    stream.resetStatus();

    stream << edge->_data;
    stream << edge->_uuid;

    if (stream.status() != QDataStream::Ok)
        throw 0; // TODO serialize exc

    return stream;
}

template <typename E>
QDataStream& operator>>(QDataStream& stream, Sence::Edge<E>*& edge) noexcept
{
    stream.startTransaction();

    edge = new Sence::Edge<E>;
    stream >> edge->_data;
    stream >> edge->_uuid;

    if (!stream.commitTransaction())
        throw 0; // TODO deserialize exc;

    return stream;
}

#endif // GRAPH_H
