#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicvertex.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphicVertex* vert = new GraphicVertex;
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(vert);
}

MainWindow::~MainWindow()
{
    delete ui;
}
