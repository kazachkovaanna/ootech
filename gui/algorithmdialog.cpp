#include "algorithmdialog.h"
#include "dijekstra.h"
#include "ui_algorithmdialog.h"

AlgorithmDialog::AlgorithmDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AlgorithmDialog)
{
    ui->setupUi(this);
}

AlgorithmDialog::~AlgorithmDialog()
{
    delete ui;
}

void AlgorithmDialog::calcualte(const Sence::Graph<QString, int>& graph, Sence::Vertex<QString>* vertex)
{
    Sence::iteratorD<QString, int> it(graph, vertex);

    while ((++it).hasNext())
        ;

    _costs = it.cost();
}
