#ifndef VERTEXSETTINGS_H
#define VERTEXSETTINGS_H

#include <QWidget>

namespace Ui {
class VertexSettings;
}

class GraphicVertex;

class VertexSettings : public QWidget
{
    Q_OBJECT

public:
    explicit VertexSettings(GraphicVertex& vertex, QWidget *parent = nullptr);
    ~VertexSettings();

protected:
    GraphicVertex& _vertex;

private slots:
    void on_name_textChanged();
    void on_tooltip_textChanged();

private:
    Ui::VertexSettings *ui;
};

#endif // VERTEXSETTINGS_H
