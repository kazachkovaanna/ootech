#include "mainwindow.h"
#include "algorithmdialog.h"
#include "graphicsline.h"
#include "graphicsview.h"
#include "graphicvertex.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));

    on_actionViewMode_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
}

void MainWindow::on_actionSave_triggered()
{
}

void MainWindow::on_actionSave_as_triggered()
{
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSettings_triggered()
{
}

void MainWindow::on_actionAbout_triggered()
{
}

void MainWindow::on_actionViewMode_triggered()
{
    ui->actionViewMode->setChecked(true);
    ui->actionAddVertexMode->setChecked(false);
    ui->actionAddEdgeMode->setChecked(false);

    ui->graphicsView->setGraphicsMode(GraphicsView::ViewMode);
}

void MainWindow::on_actionAddVertexMode_triggered()
{
    ui->actionViewMode->setChecked(false);
    ui->actionAddVertexMode->setChecked(true);
    ui->actionAddEdgeMode->setChecked(false);

    ui->graphicsView->setGraphicsMode(GraphicsView::EditVertexMode);
}

void MainWindow::on_actionAddEdgeMode_triggered()
{
    ui->actionViewMode->setChecked(false);
    ui->actionAddVertexMode->setChecked(false);
    ui->actionAddEdgeMode->setChecked(true);

    ui->graphicsView->setGraphicsMode(GraphicsView::EditEdgeMode);
}

void MainWindow::on_actionAlgorithm_triggered()
{
    AlgorithmDialog d;
    //    d.calcualte(ui->graphicsView->getGraph(), *ui->graphicsView->getGraph().begin());
}
