#ifndef GRAPH_H
#define GRAPH_H

#include <QDataStream>
#include <QList>
#include <QMap>
#include <QPair>
#include <QStringList>
#include <QUuid>

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
    Vertex(const V& data = V())
        : _data(data)
        , _uuid(QUuid::createUuid().toString())
    {
    }

    Vertex(const Vertex<V>& vertex) = default;

    inline V getData() const { return _data; }
    void setData(const V& data) { _data = data; }

    inline const QString& getUuid() const { return _uuid; }

    bool operator==(const Vertex<V>& v) { return _uuid == v._uuid && _data == v._data; }
    bool operator!=(const Vertex<V>& v) { return _uuid != v._uuid || _data == v._data; }

    void* operator new(size_t size) noexcept(false)
    {
        Q_UNUSED(size)

        return GraphAllocator<Vertex<V>>::instance().allocate();
    }

    void operator delete(void* ptr) noexcept(false)
    {
        GraphAllocator<Vertex<V>>::instance().deallocate(reinterpret_cast<Vertex<V>*>(ptr));
    }

protected:
    V _data;
    const QString _uuid;
};

template <typename E>
class Sence::Edge {
public:
    Edge(const E& data = E())
        : _data(data)
        , _uuid(QUuid::createUuid().toString())
    {
    }

    Edge(const Edge<E>& edge) = default;

    inline E getData() const { return _data; }
    void setData(const E& data) { _data = data; }

    inline const QString& getUuid() const { return _uuid; }

    bool operator==(const Edge<E>& e) { return _uuid == e._uuid && _data == e._data; }
    bool operator!=(const Edge<E>& e) { return _uuid != e._uuid || _data == e._data; }

    void* operator new(size_t size) noexcept(false)
    {
        Q_UNUSED(size)

        return GraphAllocator<Edge<E>>::instance().allocate();
    }

    void operator delete(void* ptr) noexcept(false)
    {
        GraphAllocator<Edge<E>>::instance().deallocate(reinterpret_cast<Edge<E>*>(ptr));
    }

protected:
    E _data;
    const QString _uuid;
};

template <typename V, typename E>
class Sence::Graph {
public:
    Graph() = default;
    Graph(const Graph<V, E>& graph) = default;

    inline bool isEmpty() const { return _vertices.isEmpty(); }
    inline bool contains(Vertex<V>* vertex) const { return _vertices.contains(vertex->getUuid()); }
    inline bool contains(Edge<E>* edge) const { return _edges.contains(edge->getUuid()); }

    void add(Vertex<V>* vertex)
    {
        if (vertex == nullptr)
            return;

        _vertices.insert(vertex->getUuid(), vertex);
    }

    void add(Vertex<V>* from, Vertex<V>* to, Edge<E>* edge)
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
    QPair<Vertex<V>*, QList<Edge<E>*>> remove(const Vertex<V>* vertex)
    {
        _vertices.remove(vertex->getUuid());
        QList<QString> edges = _edges.values(vertex->getUuid());
        for (auto e : edges) {
            remove(_edges.value(e));
        }

        return qMakePair(vertex, edges);
    }

    Edge<E>* remove(Edge<E>* edge)
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

    class iteratorE {
        iteratorE(const QList<Edge<E>*>& edges, bool begin)
            : _edges(edges)
            , _pointer(nullptr)
        {
            if (begin && !edges.isEmpty())
                _pointer = edges[0];
        }

    public:
        iteratorE(const iteratorE& it) = default;

        iteratorE& operator++()
        {
            int number = _edges.indexOf(_pointer);
            if (number != -1 && _edges.last() != _pointer)
                _pointer = _edges[number + 1];
            else
                _pointer = nullptr;

            return *this;
        }

        inline bool operator==(const iteratorE& it)
        {
            return _pointer == it._pointer && _edges == it._edges;
        }

        inline bool operator!=(const iteratorE& it)
        {
            return _pointer != it._pointer || _edges != it._edges;
        }

        inline Edge<E>* operator*()
        {
            return _pointer;
        }

        inline Edge<E>* operator->()
        {
            return _pointer;
        }

        friend class Graph<V, E>;

    protected:
        QList<Edge<E>*>& _edges;
        Edge<E>* _pointer;
    };

    class iteratorV {
        iteratorV(const QList<Vertex<V>*>& vertices, bool begin)
            : _vertices(vertices)
            , _pointer(nullptr)
        {
            if (begin && !vertices.isEmpty()) {
                _pointer = _vertices[0];
            }
        }

    public:
        iteratorV(const iteratorV& it) = default;

        iteratorV& operator++()
        {
            int number = _vertices.indexOf(_pointer);
            if (number != -1 || _vertices.last() < _pointer)
                _pointer = _vertices[number + 1];
            else
                _pointer = nullptr;

            return *this;
        }

        iteratorV& operator++(const iteratorV&)
        {
            iteratorV current;

            int number = _vertices.indexOf(_pointer);
            if (number != -1 || _vertices.last() < _pointer)
                _pointer = _vertices[number + 1];
            else
                _pointer = nullptr;

            return current;
        }

        inline bool operator==(const iteratorV& it)
        {
            return _pointer == it._pointer && _vertices == it._vertices;
        }
        inline bool operator!=(const iteratorV& it)
        {
            return _pointer != it._pointer || _vertices != it._vertices;
        }

        inline Vertex<V>* operator*()
        {
            return _pointer;
        }
        inline Vertex<V>* operator->()
        {
            return _pointer;
        }

        friend class Graph<V, E>;

    protected:
        QList<Vertex<V>*>& _vertices;
        Vertex<V>* _pointer;
    };

    iteratorV begin() { return iteratorV(_vertices.values(), true); }
    iteratorV end() { return iteratorV(_vertices.values(), false); }

    iteratorE begin(Vertex<V>* vertex)
    {
        // TODO throw nullpointer
        return iteratorE(_connections.values(vertex->getUuid()), true);
    }

    iteratorE end(Vertex<V>* vertex)
    {
        // TODO throw nullpointer
        return iteratorE(_connections.values(vertex->getUuid()), false);
    }

    QList<Vertex<V>*> verticesByEdge(Edge<E>* edge) const
    {
        QList<Vertex<V>*> vertices;
        for (const QString& v : _connections.keys(edge->getUuid())) {
            vertices.append(_vertices.value(v));
        }

        return vertices;
    }

    inline QList<Edge<E>*> edgesByVertex(Vertex<V>* vertex) const
    {
        QList<Edge<E>*> edges;

        for (const QString& e : _connections.values(vertex->getUuid())) {
            edges.append(_edges.value(e));
        }

        return edges;
    }

    template<typename _V, typename _E>
    friend QDataStream& operator>>(QDataStream& stream, Graph<_V, _E>& graph);
    template<typename _V, typename _E>
    friend QDataStream& operator<<(QDataStream& stream, const Graph<_V, _E>& graph);

protected:
    QMap<QString, Vertex<V>*> _vertices;
    QMap<QString, Edge<E>*> _edges;
    QMap<QString, QString> _connections;        // { V, [E1, ...]}
};

template <typename E, typename V>
QDataStream& operator<<(QDataStream& stream, const Sence::Graph<V, E>& graph)
{
    stream << setVersion(QDataStream::Qt_5_10);

    stream.resetStatus();

    stream << graph._vertices;
    stream << graph._edges;
    stream << graph._connections;

    if (stream.status() != QDataStream::Ok)
        throw 2; // TODO serialize exception
}

template <typename E, typename V>
QDataStream& operator>>(QDataStream& stream, Sence::Graph<V, E>& graph)
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
QDataStream& operator<<(QDataStream& stream, const Sence::Vertex<V>* vertex)
{
    if (nullptr == vertex) {
        stream.setStatus(QDataStream::WriteFailed);
        throw 0; // TODO nullptr
    }

    stream.resetStatus();

    stream << vertex->_data();
    stream << vertex->_uuid();

    if (stream.status() != QDataStream::Ok)
        throw 3; // TODO throw serialize exception;

    return stream;
}

template <typename V>
QDataStream& operator>>(QDataStream& stream, Sence::Vertex<V>*& vertex)
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
QDataStream& operator<<(QDataStream& stream, const Sence::Edge<E>* edge)
{
    if (nullptr == edge) {
        stream.setStatus(QDataStream::WriteFailed);
        throw 0; // TODO nullptr
    }

    stream.resetStatus();

    stream << edge->_data();
    stream << edge->_uuid();

    if (stream.status() != QDataStream::Ok)
        throw 0; // TODO serialize exc

    return stream;
}

template <typename E>
QDataStream& operator>>(QDataStream& stream, Sence::Edge<E>*& edge)
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
