#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExit_triggered();
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();

    void on_actionViewMode_triggered();
    void on_actionAddVertexMode_triggered();
    void on_actionAddEdgeMode_triggered();

    void on_actionAlgorithm_triggered();

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
