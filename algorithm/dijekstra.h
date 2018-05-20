#ifndef DIJEKSTRA_H
#define DIJEKSTRA_H

#include <QQueue>

#include "graph.h"

template <typename V, typename E>
class Dijekstra;

template <typename V, typename E>
class iteratorD {
    iteratorD(const Graph<V, E>& graph, Vertex<V>* startVertex, bool begin)
        : _graph(graph)
    {
        if (!graph.contains(startVertex))
            throw "start vertex mast be contains in graph";

        if (begin)
            _visionVertex.append(startVertex->getUuid(), startVertex);
    }

public:
    iteratorD(const iteratorD<V, E>& it) = default;

    iteratorD& operator++()
    {
        // ПЕРЕДЕЛАТЬ
        if (_visionVertex.isEmpty())
            return *this;

        auto v = _visionVertex.begin();
        _visionVertex.erase(v);

        Vertex<V>* vertex = v.value();

        for (Vertex<V>* v : vertex) {
            if (_visitedVertex.contains(v->getUuid(), v))
                continue;

            if (_visionVertex.contains(v->getUuid(), v))
                continue;

            _visionVertex.insertMilti(v->getUuid(), v);
        }

        return *this;
    }

    inline bool operator==(const iteratorD& it)
    {
        return _visionVertex == it._visionVertex && _visitedVertex == it._visitedVertex && _graph == it._graph;
    }

    inline bool operator!=(const iteratorD& it)
    {
        return _visionVertex != it._visionVertex || _visitedVertex != it._visitedVertex || _graph != it._graph;
    }

    Vertex<V>* operator*()
    {
        return _visionVertex.begin().value();
    }

    Vertex<V>* operator->()
    {
        return _visionVertex.begin().value();
    }

    friend class Dijekstra<V, E>;

protected:
    QMap<QString, Vertex<V>*> _visitedVertex;
    QMap<QString, Vertex<V>*> _visionVertex;
    const Graph<V, E>& _graph;
};

template <typename E, typename V>
class Dijekstra {
    static QMap<QString, E> cost(const Graph<E, V>& graph, Vertex<V>* startVertex)
    {
        QMap<QString, E> cost;

        iteratorD it(graph, startVertex, true);
        iteratorD end(graph, startVertex, false);

        for (; it != end; ++it) {
            Vertex<V>* vertex = *it;
            typename Graph<V, E>::iteratorE itE = graph.begin(vertex);
            typename Graph<V, E>::iteratorE end = graph.end(vertex);

            for (; itE != end; ++itE) {
                E currentCost = cost.contains(vertex->getUuid()) ? cost.value(vertex->getUuid()) : 0;
                E otherCost = cost.contains(itE->getTo()) ? cost.value(itE->getTo()) : currentCost + 1;

                if (currentCost > otherCost + itE->getData())
                    cost.insert(vertex->getUuid(), otherCost + itE->getData());
            }
        }

        return cost;
    }
};

#endif // DIJEKSTRA_H
