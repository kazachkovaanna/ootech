#include "graphiclinedialog.h"
#include "ui_graphiclinedialog.h"

GraphicLineDialog::GraphicLineDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::GraphicLineDialog)
{
    ui->setupUi(this);
}

GraphicLineDialog::~GraphicLineDialog()
{
    delete ui;
}

QString GraphicLineDialog::getTooltip() const
{
    return ui->tooltip->toPlainText();
}

void GraphicLineDialog::setTooltip(const QString& tooltip)
{
    ui->tooltip->setText(tooltip);
}

int GraphicLineDialog::getCost() const
{
    return ui->cost->value();
}

void GraphicLineDialog::setCost(int cost)
{
    ui->cost->setValue(cost);
}
