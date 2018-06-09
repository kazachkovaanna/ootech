#ifndef LINESETTINGS_H
#define LINESETTINGS_H

#include <QWidget>

namespace Ui {
class LineSettings;
}

class GraphicsLine;

class LineSettings : public QWidget
{
    Q_OBJECT

public:
    explicit LineSettings(GraphicsLine& line, QWidget *parent = nullptr);
    ~LineSettings();

protected:
    GraphicsLine& _line;

private slots:
    void on_value_valueChanged(int value);

    void on_tooltip_textChanged();

private:
    Ui::LineSettings *ui;
};

#endif // LINESETTINGS_H
