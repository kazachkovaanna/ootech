#include "graphicsvertexdialog.h"
#include "ui_graphicsvertexdialog.h"

GraphicsVertexDialog::GraphicsVertexDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::GraphicsVertexDialog)
{
    ui->setupUi(this);
}

GraphicsVertexDialog::~GraphicsVertexDialog()
{
    delete ui;
}

QString GraphicsVertexDialog::getName() const
{
    return ui->name->text();
}

void GraphicsVertexDialog::setName(const QString& name)
{
    ui->name->setText(name);
}

QString GraphicsVertexDialog::getTooltip() const
{
    return ui->tooltip->toPlainText();
}

void GraphicsVertexDialog::setTooltip(const QString& tooltip)
{
    ui->tooltip->setText(tooltip);
}
