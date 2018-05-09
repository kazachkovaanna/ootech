#ifndef GRAPH_H
#define GRAPH_H

#include <QList>
#include <QMap>
#include <QSet>
#include <QUuid>

template <typename V>
class Vertex {
public:
    Vertex(const V& data)
        : _data(data)
        , _uuid(QUuid::createUuid().toString())
    {
    }

    Vertex(const Vertex<V>& vertex) = default;

    inline V getData() const { return _data; }
    void setData(const V& data) { _data = data; }

    inline QString getUuid() const { return _uuid; }

protected:
    V _data;
    const QString _uuid;
};

template <typename E>
class Edge {
public:
    Edge(const QString& from, const QString& to, const E& data)
        : _from(from)
        , _to(to)
        , _data(data)
    {
    }

    Edge(const Edge<E>& edge) = default;

    inline QString getFrom() const { return _from; }
    inline QString getTo() const { return _to; }

    inline E getData() const { return _data; }
    void setData(const E& data) { _data = data; }

protected:
    const QString _from;
    const QString _to;
    E _data;
};

template <typename E, typename V>
class Graph {
public:
    Graph() = default;
    Graph(const Graph& graph) = default;

    inline bool isEmpty() const { return _vertices.isEmpty(); }
    inline bool contains(Vertex<V>* vertex) const { return _vertices.contains(vertex); }
    inline bool contains(Edge<E>* edge) const { return _edges.contains(edge); }

    void add(Vertex<V>* vertex)
    {
        if (vertex == nullptr)
            return;

        _vertices.insert(vertex->getUuid(), vertex);
    }

    void add(Edge<E>* edge)
    {
        if (edge == nullptr)
            return;

        if (!_vertices.contains(edge->getFrom()))
            return;
        if (!_vertices.contains(edge->getTo()))
            return;

        // TODO check contains existing edge
        _edges.insertMulti(edge->getFrom(), edge);
        _edges.insertMulti(edge->getTo(), edge);
    }

    // cascade remove
    void remove(Vertex<V>* vertex)
    {
        _vertices.remove(vertex->getUuid());
        QList<Edge<E>*> edges = _edges.values(vertex->getUuid());
        for (Edge<E>* e : edges) {
            remove(e);
        }
    }

    void remove(Edge<E>* edge)
    {
        QList<Edge<E>*> values = _edges.values(edge->getFrom());
        _edges.remove(edge->getFrom());
        values.removeOne(edge);
        for (Edge<E>* e : values) {
            _edges.insertMulti(edge->getFrom(), e);
        }

        values = _edges.values(edge->getTo());
        _edges.remove(edge->getFrom());
        values.removeOne(edge);
        for (Edge<E>* e : values) {
            _edges.insertMulti(edge->getTo(), e);
        }
    }

    // all vertex from graph are linked?
    bool isDisconnected() const;

    class iteratorE {
        iteratorE(const QList<Edge<E>*>& edges, bool begin)
            : _edges(edges)
            , _number(begin ? 0 : edges.size())
        {
        }

    public:
        iteratorE(const iteratorE& it) = default;

        iteratorE& operator++()
        {
            if (_edges.size() < _number)
                _number++;

            return *this;
        }

        iteratorE& operator++(const iteratorE&)
        {
            iteratorE currentIt(*this);

            if (_edges.size() < _number)
                _number++;

            return currentIt;
        }

        inline bool operator==(const iteratorE& it)
        {
            return _number == it._number && _edges == it._edges;
        }

        inline bool operator!=(const iteratorE& it)
        {
            return _number != it._number || _edges != it._edges;
        }

        Edge<E>* operator*()
        {
            return _edges.size() < _number ? _edges[_number] : nullptr;
        }

        Edge<E>* operator->()
        {
            return _edges.size() < _number ? _edges[_number] : nullptr;
        }

        friend class Graph<V, E>;

    protected:
        QList<Edge<E>*> _edges;
        int _number;
    };

    class iteratorV {
        iteratorV(const QList<Vertex<V>*>& vertices, bool begin)
            : _vertices(vertices)
            , _number(begin ? 0 : vertices.size())
        {
        }

    public:
        iteratorV(const iteratorV& it) = default;

        iteratorV& operator++()
        {
            if (_vertices.size() < _number)
                _number++;
            return *this;
        }
        iteratorV& operator++(const iteratorV&)
        {
            iteratorV current;

            if (_vertices.size() < _number)
                _number++;

            return current;
        }

        inline bool operator==(const iteratorV& it)
        {
            return _number == it._number && _vertices == it._vertices;
        }
        inline bool operator!=(const iteratorV& it)
        {
            return _number != it._number || _vertices != it._vertices;
        }

        inline Vertex<V>* operator*()
        {
            return _vertices.size() < _number ? _vertices[_number] : nullptr;
        }
        inline Vertex<V>* operator->()
        {
            return _vertices.size() < _number ? _vertices[_number] : nullptr;
        }

        friend class Graph<V, E>;

    protected:
        QList<Vertex<V>*> _vertices;
        int _number;
    };

    iteratorV begin() { return iteratorV(_vertices.values(), true); }
    iteratorV end() { return iteratorV(_vertices.values(), false); }

    iteratorE begin(Vertex<V>* vertex)
    {
        // TODO
        return iteratorE(_edges.values(vertex), true);
    }

    iteratorE end(Vertex<V>* vertex)
    {
        // TODO
        return iteratorE(_edges.values(vertex), false);
    }

    friend QDataStream& operator>>(QDataStream&, Graph<E, V>&);
    friend QDataStream& operator<<(QDataStream&, const Graph<E, V>&);

protected:
    QMap<QString, Vertex<V>*> _vertices;
    QMap<QString, Edge<E>*> _edges;
};

template <typename E, typename V>
QDataStream& operator>>(QDataStream& stream, Graph<E, V>& graph)
{
    stream.setStatus(QDataStream::Ok);

    stream >> graph._vertices;
    if (stream.status() != QDataStream::Ok)
        throw 2; // TODO deserialize exception

    stream >> graph._edges;
    if (stream.status() != QDataStream::Ok)
        throw 2; // TODO deserialize exception
}

template <typename E, typename V>
QDataStream& operator<<(QDataStream& stream, const Graph<E, V>& graph)
{
    stream << graph._vertices;

    if (stream.status() != QDataStream::Ok)
        throw 1; // TODO throw serialize exception

    stream << graph._edges;
    if (stream.status() != QDataStream::Ok)
        throw 1; // TODO throw serialize exception

    return stream;
}

template <typename V>
QDataStream& operator<<(QDataStream& stream, const Vertex<V>& vertex)
{
    stream << vertex._data;
    if (stream.status() != QDataStream::Ok)
        throw 3; // TODO throw serialize exception;

    return stream;
}

template <typename V>
QDataStream& operator>>(QDataStream& stream, Vertex<V>& vertex)
{
    stream >> vertex._data;
    if (stream.status() != QDataStream::Ok)
        throw 4; // TODO throw serialize exception

    return stream;
}

template <typename E>
QDataStream& operator<<(QDataStream& stream, const Edge<E>& edge)
{
    stream << edge._from;
    stream << edge._to;
    stream << edge._data;

    return stream;
}

template <typename E>
QDataStream& operator>>(QDataStream& stream, Edge<E>& edge)
{
    stream >> edge._from;
    stream >> edge._to;
    stream >> edge._data;

    return stream;
}

#endif // GRAPH_H
