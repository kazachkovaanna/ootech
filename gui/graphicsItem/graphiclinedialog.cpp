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

QList<int> GraphicLineDialog::getCosts() const
{
    return { ui->cost->value() };
}

void GraphicLineDialog::setCosts(const QList<int>& costs)
{
    ui->cost->setValue(costs[0]);
}
