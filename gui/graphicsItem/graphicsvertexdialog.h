#ifndef GRAPHICSVERTEXDIALOG_H
#define GRAPHICSVERTEXDIALOG_H

#include <QDialog>

namespace Ui {
class GraphicsVertexDialog;
}

class GraphicsVertexDialog : public QDialog {
    Q_OBJECT

public:
    explicit GraphicsVertexDialog(QWidget* parent = nullptr);
    ~GraphicsVertexDialog();

    QString getName() const;
    void setName(const QString& name);

    QString getTooltip() const;
    void setTooltip(const QString& tooltip);

private:
    Ui::GraphicsVertexDialog* ui;
};

#endif // GRAPHICSVERTEXDIALOG_H
