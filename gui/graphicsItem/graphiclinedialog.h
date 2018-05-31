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

    QList<int> getCosts() const;
    void setCosts(const QList<int>& costs);

private:
    Ui::GraphicLineDialog* ui;
};

#endif // GRAPHICLINEDIALOG_H
