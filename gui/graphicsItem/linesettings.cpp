#include "linesettings.h"
#include "ui_linesettings.h"
#include "graphicsline.h"
#include "graph.h"

LineSettings::LineSettings(GraphicsLine& line, QWidget *parent)
    : QWidget(parent)
    , _line(line)
    , ui(new Ui::LineSettings)
{
    ui->setupUi(this);

    ui->value->setValue(line.getEdge()->getData());
    ui->tooltip->setText(line.toolTip());
}

LineSettings::~LineSettings()
{
    delete ui;
}

void LineSettings::on_value_valueChanged(int value)
{
    _line.getEdge()->setData(value);
    _line.update();
}

void LineSettings::on_tooltip_textChanged()
{
    _line.setToolTip(ui->tooltip->toPlainText());
}
