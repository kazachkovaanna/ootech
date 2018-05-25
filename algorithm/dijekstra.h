#ifndef DIJEKSTRA_H
#define DIJEKSTRA_H

#include <QMap>
#include <QList>
#include <QQueue>
#include <QDebug>

#include "graph.h"

namespace Sence {
// clang-format off
    template<typename V, typename E> class iteratorD;
// clang-format on
}

template <typename V, typename E>
class Sence::iteratorD {
public:
    iteratorD(const Graph<V, E>& graph, Vertex<V>* startVertex, bool begin = true)
        : _graph(graph)
        , _current(nullptr)
    {
        if (!graph.contains(startVertex))
            begin = false;

        if (begin) {
            _visionVertices.append(startVertex);
            _current = startVertex;
            _cost.insert(_current, E());
        }
    }

    iteratorD(const iteratorD<V, E>& it) = default;

    iteratorD<V, E>& operator++()
    {
        _current = selectNextVisionVertex();
        if (nullptr == _current)
            return *this;

        _visionVertices.removeOne(_current);
        _visitedVertices.append(_current);

        updateVisionVertex();

        return *this;
    }

    inline bool operator==(const iteratorD<V, E>& it)
    {
        return _current == it._current;
    }

    inline bool operator!=(const iteratorD<V, E>& it)
    {
        return _current != it._current;
    }

    Vertex<V>* operator*()
    {
        return _current;
    }

    Vertex<V>* operator->()
    {
        return _current;
    }

    inline QMap<Vertex<V>*, E> cost() const
    {
        return _cost;
    }

    inline bool hasNext() const { return !_visionVertices.isEmpty(); }

protected:
    Vertex<V>* selectNextVisionVertex() const
    {
        if (_visionVertices.isEmpty())
            return nullptr;

        Vertex<V>* current = _visionVertices[0];
        for (Vertex<V>* v : _visionVertices) {
            if (!_visitedVertices.contains(v) && _cost.value(v) < _cost.value(current))
                current = v;
        }

        return current;
    }

    void updateVisionVertex()
    {
        QList<Edge<E>*> edges = _graph.edgesByVertex(_current);

        for (Edge<E>* e : edges) {
            for (Vertex<V>* v : _graph.verticesByEdge(e)) {
                if (_visitedVertices.contains(v))
                    continue;

                if (!_visionVertices.contains(v))
                    _visionVertices.append(v);

                E cost = _cost.value(_current) + e->getData();
                if (!_cost.contains(v) || _cost.value(v) > cost) {
                    _cost.insert(v, cost);
                }
            }
        }
    }

protected:
    QList<Vertex<V>*> _visitedVertices;
    QList<Vertex<V>*> _visionVertices;
    const Graph<V, E>& _graph;
    Vertex<V>* _current;
    QMap<Vertex<V>*, E> _cost;
};

#endif // DIJEKSTRA_H
