#include "mainwindow.h"
#include "graphicvertex.h"
#include "graphicsline.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    GraphicsLine* line = new GraphicsLine;
    GraphicVertex* vert = new GraphicVertex;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addItem(vert);
    ui->graphicsView->scene()->addItem(line);
    line->setPoints({QPointF(0, 0), QPointF(0, 200), QPointF(200, 200)});
    vert->setPos(0, 0);
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
