#include <QApplication>
#include <QDebug>
#include <QTimer>

#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    app.setApplicationName("MultiGraphView");
    app.setOrganizationName("Sence");
    app.setOrganizationDomain("sence.ru");

    MainWindow w;
    w.show();

    return app.exec();
}
