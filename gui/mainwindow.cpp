#include "mainwindow.h"
#include "algorithmdialog.h"
#include "graphicsline.h"
#include "graphicsview.h"
#include "graphicvertex.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));

    SettingsDialog dialog;
    dialog.load(QSettings());

    ui->graphicsView->setPen(dialog.pen());
    ui->graphicsView->setSelectedPen(dialog.selectedPen());
    ui->graphicsView->setBrush(dialog.brush());
    ui->graphicsView->setSelectedBrush(dialog.selectedBrush());
    ui->graphicsView->setFont(dialog.font());

    connect(ui->graphicsView, &GraphicsView::itemSelected, this, &MainWindow::onItemSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onItemSelected(AbstractItem *item)
{
    if (nullptr == item) {
        ui->settingsDocWidget->setWidget(ui->settingsWidget);
    } else {
        ui->settingsDocWidget->setWidget(item->getSettingsForm());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if (filename.isEmpty())
        return;

    QFile f(filename);
    if (!f.open(QFile::ReadOnly)) {
        QString title("Ошибка открытия");
        QString message("Не удалось открыть фаил на чтение.");

        QMessageBox::warning(this, title, message);
        return;
    }

    QDataStream ds(&f);
    ds >> *ui->graphicsView;
}

void MainWindow::on_actionSave_triggered()
{
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if (filename.isEmpty())
        return;

    QFile f(filename);
    if (!f.open(QFile::WriteOnly)) {
        QString title("Ошибка сохранения");
        QString message("Не удалось открыть фаил на запись.");

        QMessageBox::warning(this, title, message);
        return;
    }

    QDataStream ds(&f);
    ds << *ui->graphicsView;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSettings_triggered()
{
    QSettings settings;

    SettingsDialog dialog(this);
    dialog.load(settings);

    if (dialog.exec() == SettingsDialog::Accepted) {
        dialog.save(settings);

        ui->graphicsView->setPen(dialog.pen());
        ui->graphicsView->setSelectedPen(dialog.selectedPen());
        ui->graphicsView->setBrush(dialog.brush());
        ui->graphicsView->setSelectedBrush(dialog.selectedBrush());
        ui->graphicsView->setFont(dialog.font());
    }
}

void MainWindow::on_actionAbout_triggered()
{
}

void MainWindow::on_actionAddVertexMode_triggered(bool checked)
{
    ui->actionAddEdgeMode->setChecked(false);
    ui->actionAlgorithm->setChecked(false);

    if (checked)
        ui->graphicsView->setGraphicsMode(GraphicsView::EditVertexMode);
    else
        ui->graphicsView->setGraphicsMode(GraphicsView::ViewMode);
}

void MainWindow::on_actionAddEdgeMode_triggered(bool checked)
{
    ui->actionAddVertexMode->setChecked(false);
    ui->actionAlgorithm->setChecked(false);

    if (checked)
        ui->graphicsView->setGraphicsMode(GraphicsView::EditEdgeMode);
    else
        ui->graphicsView->setGraphicsMode(GraphicsView::ViewMode);
}

void MainWindow::on_actionAlgorithm_triggered(bool checked)
{
    ui->actionAddEdgeMode->setChecked(false);
    ui->actionAddVertexMode->setChecked(false);

    if (checked)
        ui->graphicsView->setGraphicsMode(GraphicsView::ViewCostMode);
    else
        ui->graphicsView->setGraphicsMode(GraphicsView::ViewMode);
}
