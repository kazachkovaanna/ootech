#include "vertexsettings.h"
#include "ui_vertexsettings.h"
#include "graphicvertex.h"
#include "graph.h"

VertexSettings::VertexSettings(GraphicVertex& vertex, QWidget *parent)
    : QWidget(parent)
    , _vertex(vertex)
    , ui(new Ui::VertexSettings)
{
    ui->setupUi(this);

    ui->name->setText(vertex.getVertex()->getData());
    ui->tooltip->setText(vertex.toolTip());
}

VertexSettings::~VertexSettings()
{
    delete ui;
}

void VertexSettings::on_name_textChanged()
{
    _vertex.getVertex()->setData(ui->name->text());
    _vertex.update();
}

void VertexSettings::on_tooltip_textChanged()
{
    _vertex.setToolTip(ui->tooltip->toPlainText());
}
