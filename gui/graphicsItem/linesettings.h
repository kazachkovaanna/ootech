#ifndef LINESETTINGS_H
#define LINESETTINGS_H

#include <QWidget>

namespace Ui {
class LineSettings;
}

class LineSettings : public QWidget
{
    Q_OBJECT

public:
    explicit LineSettings(QWidget *parent = nullptr);
    ~LineSettings();

private:
    Ui::LineSettings *ui;
};

#endif // LINESETTINGS_H
