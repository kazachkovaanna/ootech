#include <QApplication>
#include <QDebug>
#include <QTimer>

#include "mainwindow.h"

#include "graph.h"
#include "dijekstra.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

//    MainWindow w;
//    w.show();

    Graph<QString, int> graph;

    QList<Vertex<QString>*> vList;
    QList<Edge<int>*> eList;

    auto v1 = new Vertex<QString>("1");
    auto v2 = new Vertex<QString>("2");
    auto v3 = new Vertex<QString>("3");
    auto v4 = new Vertex<QString>("4");
    auto v5 = new Vertex<QString>("5");
    auto v6 = new Vertex<QString>("6");

    auto e_1_2 = new Edge<int>(7);
    auto e_1_3 = new Edge<int>(9);
    auto e_1_6 = new Edge<int>(14);
    auto e_2_3 = new Edge<int>(10);
    auto e_2_4 = new Edge<int>(15);
    auto e_3_4 = new Edge<int>(11);
    auto e_3_6 = new Edge<int>(2);
    auto e_4_5 = new Edge<int>(6);
    auto e_5_6 = new Edge<int>(9);

    graph.add(v1);
    graph.add(v2);
    graph.add(v3);
    graph.add(v4);
    graph.add(v5);
    graph.add(v6);

    graph.add(v1, v2, e_1_2);
    graph.add(v1, v3, e_1_3);
    graph.add(v1, v6, e_1_6);

    graph.add(v2, v3, e_2_3);
    graph.add(v2, v4, e_2_4);

    graph.add(v3, v4, e_3_4);
    graph.add(v3, v6, e_3_6);

    graph.add(v4, v5, e_4_5);

    graph.add(v5, v6, e_5_6);

    iteratorD<QString, int> dijekstra(graph, v1);
    while ((++dijekstra).hasNext());
    QMap<Vertex<QString>*, int> costs = dijekstra.cost();

    QMapIterator<Vertex<QString>*, int> it(costs);

    while (it.hasNext()) {
        it.next();
        qDebug() << it.key()->getData() << it.value();
    }

    QTimer::singleShot(0, &app, SLOT(quit()));

    return app.exec();
}
