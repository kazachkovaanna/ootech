#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class AbstractItem;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected slots:
    void onItemSelected(AbstractItem* item);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExit_triggered();
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();

    void on_actionAddVertexMode_triggered(bool checked);
    void on_actionAddEdgeMode_triggered(bool checked);
    void on_actionAlgorithm_triggered(bool checked);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
