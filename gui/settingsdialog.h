#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QPen>
#include <QBrush>
#include <QFont>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    void load(const QSettings& settings);
    void save(QSettings& settings);

    inline QPen pen() const { return _pen; }
    inline QPen selectedPen() const { return _selectedPen; }
    inline QBrush brush() const { return _brush; }
    inline QBrush selectedBrush() const { return _selectedBrush; }
    inline QFont font() const { return _font; }

    void setPen(const QPen& pen);
    void setSelectedPen(const QPen& pen);
    void setBrush(const QBrush& brush);
    void setSelectedBrush(const QBrush& brush);
    void setFont(const QFont& font);

public:
    static QPen defaultPen;
    static QPen defaultSelectedPen;
    static QBrush defaultBrush;
    static QBrush defaultSelectedBrush;
    static QFont defaultFont;

private slots:
    void on_penColor_clicked();
    void on_brushColor_clicked();
    void on_font_clicked();

    void on_penType_activated(int index);

    void on_brushType_activated(int index);

private:
    Ui::SettingsDialog *ui;
    QPen _pen;
    QPen _selectedPen;
    QBrush _brush;
    QBrush _selectedBrush;
    QFont _font;
};

#endif // SETTINGSDIALOG_H
