#ifndef VERTEXSETTINGS_H
#define VERTEXSETTINGS_H

#include <QWidget>

namespace Ui {
class VertexSettings;
}

class VertexSettings : public QWidget
{
    Q_OBJECT

public:
    explicit VertexSettings(QWidget *parent = nullptr);
    ~VertexSettings();

private:
    Ui::VertexSettings *ui;
};

#endif // VERTEXSETTINGS_H
