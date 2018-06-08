#include "vertexsettings.h"
#include "ui_vertexsettings.h"

VertexSettings::VertexSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VertexSettings)
{
    ui->setupUi(this);
}

VertexSettings::~VertexSettings()
{
    delete ui;
}
