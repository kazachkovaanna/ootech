#include "linesettings.h"
#include "ui_linesettings.h"

LineSettings::LineSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineSettings)
{
    ui->setupUi(this);
}

LineSettings::~LineSettings()
{
    delete ui;
}
