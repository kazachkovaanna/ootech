#ifndef GRAPHICLINEDIALOG_H
#define GRAPHICLINEDIALOG_H

#include <QDialog>

namespace Ui {
class GraphicLineDialog;
}

class GraphicLineDialog : public QDialog {
    Q_OBJECT

public:
    explicit GraphicLineDialog(QWidget* parent = nullptr);
    ~GraphicLineDialog();

    QString getTooltip() const;
    void setTooltip(const QString& tooltip);

    int getCost() const;
    void setCost(int cost);

private:
    Ui::GraphicLineDialog* ui;
};

#endif // GRAPHICLINEDIALOG_H
