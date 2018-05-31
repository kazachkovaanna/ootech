#ifndef ALGORITHMDIALOG_H
#define ALGORITHMDIALOG_H

#include "graph.h"
#include <QDialog>

namespace Ui {
class AlgorithmDialog;
}

class AlgorithmDialog : public QDialog {
    Q_OBJECT

public:
    explicit AlgorithmDialog(QWidget* parent = nullptr);
    ~AlgorithmDialog();

    void calcualte(const Sence::Graph<QString, int>& graph, Sence::Vertex<QString>* vertex);

private:
    Ui::AlgorithmDialog* ui;
    QMap<Sence::Vertex<QString>*, int> _costs;
};

#endif // ALGORITHMDIALOG_H
