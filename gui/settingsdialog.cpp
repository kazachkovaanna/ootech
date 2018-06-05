#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QColorDialog>
#include <QFontDialog>
#include <QMetaType>
#include <QStandardItemModel>

QPen SettingsDialog::defaultPen(Qt::black, 2);
QPen SettingsDialog::defaultSelectedPen(QBrush(Qt::red), 2, Qt::DashLine);
QBrush SettingsDialog::defaultBrush(Qt::lightGray);
QBrush SettingsDialog::defaultSelectedBrush(Qt::gray);
QFont SettingsDialog::defaultFont("Arial", 10);

QString toString(Qt::PenStyle style)
{
    switch (style) {
    case Qt::NoPen:
        return QObject::trUtf8("No Pen");
    case Qt::SolidLine:
        return QObject::trUtf8("Solid Line");
    case Qt::DashLine:
        return QObject::trUtf8("Dash Line");
    case Qt::DotLine:
        return QObject::trUtf8("Dot Line");
    case Qt::DashDotLine:
        return QObject::trUtf8("Dash Dot Line");
    case Qt::DashDotDotLine:
        return QObject::trUtf8("Dash Dot Dot Line");
    case Qt::CustomDashLine:
        return QObject::trUtf8("Custom Dash Line");
    default:
        return QObject::trUtf8("Unknown");
    }
}

QString toString(Qt::BrushStyle style)
{
    switch (style) {
    case Qt::NoBrush:       return QObject::trUtf8("NoBrush");
    case Qt::SolidPattern:  return QObject::trUtf8("SolidPattern");
    case Qt::Dense1Pattern: return QObject::trUtf8("Dense1Pattern");
    case Qt::Dense2Pattern: return QObject::trUtf8("Dense2Pattern");
    case Qt::Dense3Pattern: return QObject::trUtf8("Dense3Pattern");
    case Qt::Dense4Pattern: return QObject::trUtf8("Dense4Pattern");
    case Qt::Dense5Pattern: return QObject::trUtf8("Dense5Pattern");
    case Qt::Dense6Pattern: return QObject::trUtf8("Dense6Pattern");
    case Qt::Dense7Pattern: return QObject::trUtf8("Dense7Pattern");
    case Qt::HorPattern:    return QObject::trUtf8("HorPattern");
    case Qt::VerPattern:    return QObject::trUtf8("VerPattern");
    case Qt::CrossPattern:  return QObject::trUtf8("CrossPattern");
    case Qt::BDiagPattern:  return QObject::trUtf8("BDiagPattern");
    case Qt::FDiagPattern:  return QObject::trUtf8("FDiagPattern");
    case Qt::DiagCrossPattern:          return QObject::trUtf8("DiagCrossPattern");
    case Qt::LinearGradientPattern:     return QObject::trUtf8("LinearGradientPattern");
    case Qt::RadialGradientPattern:     return QObject::trUtf8("RadialGradientPattern");
    case Qt::ConicalGradientPattern:    return QObject::trUtf8("ConicalGradientPattern");
    case Qt::TexturePattern:            return QObject::trUtf8("TexturePattern");
    }
    return QObject::trUtf8("Unknown");
}

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , _pen(defaultPen)
    , _selectedPen(defaultSelectedPen)
    , _brush(defaultBrush)
    , _selectedBrush(defaultSelectedBrush)
    , _font(defaultFont)
{
    ui->setupUi(this);

    qRegisterMetaType<QPen>("Qt::QPen");
    qRegisterMetaType<QBrush>("Qt::QBrush");
    qRegisterMetaType<QFont>("Qt::QFont");
    qRegisterMetaType<Qt::PenStyle>("Qt::PenStyle");
    qRegisterMetaType<Qt::BrushStyle>("Qt::BrushStyle");

    ui->penType->addItem(toString(Qt::NoPen), qVariantFromValue(Qt::NoPen));
    ui->penType->addItem(toString(Qt::SolidLine), qVariantFromValue(Qt::SolidLine));
    ui->penType->addItem(toString(Qt::DashLine), qVariantFromValue(Qt::DashLine));
    ui->penType->addItem(toString(Qt::DotLine), qVariantFromValue(Qt::DotLine));
    ui->penType->addItem(toString(Qt::DashDotLine), qVariantFromValue(Qt::DashDotLine));
    ui->penType->addItem(toString(Qt::DashDotDotLine), qVariantFromValue(Qt::DashDotDotLine));
    ui->penType->addItem(toString(Qt::CustomDashLine), qVariantFromValue(Qt::CustomDashLine));

    ui->brushType->addItem(toString(Qt::NoBrush), qVariantFromValue(Qt::NoBrush));
    ui->brushType->addItem(toString(Qt::SolidPattern), qVariantFromValue(Qt::SolidPattern));
    ui->brushType->addItem(toString(Qt::Dense1Pattern), qVariantFromValue(Qt::Dense1Pattern));
    ui->brushType->addItem(toString(Qt::Dense2Pattern), qVariantFromValue(Qt::Dense2Pattern));
    ui->brushType->addItem(toString(Qt::Dense3Pattern), qVariantFromValue(Qt::Dense3Pattern));
    ui->brushType->addItem(toString(Qt::Dense4Pattern), qVariantFromValue(Qt::Dense4Pattern));
    ui->brushType->addItem(toString(Qt::Dense5Pattern), qVariantFromValue(Qt::Dense5Pattern));
    ui->brushType->addItem(toString(Qt::Dense6Pattern), qVariantFromValue(Qt::Dense6Pattern));
    ui->brushType->addItem(toString(Qt::Dense7Pattern), qVariantFromValue(Qt::Dense7Pattern));
    ui->brushType->addItem(toString(Qt::HorPattern), qVariantFromValue(Qt::HorPattern));
    ui->brushType->addItem(toString(Qt::VerPattern), qVariantFromValue(Qt::VerPattern));
    ui->brushType->addItem(toString(Qt::CrossPattern), qVariantFromValue(Qt::CrossPattern));
    ui->brushType->addItem(toString(Qt::BDiagPattern), qVariantFromValue(Qt::BDiagPattern));
    ui->brushType->addItem(toString(Qt::FDiagPattern), qVariantFromValue(Qt::FDiagPattern));
    ui->brushType->addItem(toString(Qt::DiagCrossPattern), qVariantFromValue(Qt::DiagCrossPattern));
    ui->brushType->addItem(toString(Qt::LinearGradientPattern), qVariantFromValue(Qt::LinearGradientPattern));
    ui->brushType->addItem(toString(Qt::RadialGradientPattern), qVariantFromValue(Qt::RadialGradientPattern));
    ui->brushType->addItem(toString(Qt::ConicalGradientPattern), qVariantFromValue(Qt::ConicalGradientPattern));
    ui->brushType->addItem(toString(Qt::TexturePattern), qVariantFromValue(Qt::TexturePattern));

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->brushType->model());
    for (int i = 15; i < 19; i++) {
        QStandardItem* item = model->item(i);
        item->setFlags(Qt::NoItemFlags);
    }

    ui->penType->setCurrentText(toString(_pen.style()));
    ui->brushType->setCurrentText(toString(_brush.style()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::load(const QSettings& settings)
{
    _pen = settings.value("pen", defaultPen).value<QPen>();
    _selectedPen = settings.value("selectedPen", defaultSelectedPen).value<QPen>();

    _brush = settings.value("brush", defaultBrush).value<QBrush>();
    _selectedBrush = settings.value("selectedBrush", defaultSelectedBrush).value<QBrush>();

    _font = settings.value("font", defaultFont).value<QFont>();

    ui->penType->setCurrentText(toString(_pen.style()));
    ui->brushType->setCurrentText(toString(_brush.style()));
}

void SettingsDialog::save(QSettings& settings)
{
    settings.setValue("pen", _pen);
    settings.setValue("selectedPen", _selectedPen);

    settings.setValue("brush", _brush);
    settings.setValue("selectedBrush", _selectedBrush);

    settings.setValue("font", _font);
}

void SettingsDialog::setPen(const QPen &pen)
{
    _pen = pen;
}

void SettingsDialog::setSelectedPen(const QPen &pen)
{
    _selectedPen = pen;
}

void SettingsDialog::setBrush(const QBrush &brush)
{
    _brush = brush;
}

void SettingsDialog::setSelectedBrush(const QBrush &brush)
{
    _selectedBrush = brush;
}

void SettingsDialog::setFont(const QFont &font)
{
    _font = font;
}

void SettingsDialog::on_penColor_clicked()
{
    QColorDialog dialog(_pen.color(), this);

    if (dialog.exec() == QColorDialog::Accepted) {
        _pen.setColor(dialog.selectedColor());
    }
}

void SettingsDialog::on_brushColor_clicked()
{
    QColorDialog dialog(_brush.color(), this);

    if (dialog.exec() == QColorDialog::Accepted) {
        _brush.setColor(dialog.selectedColor());
    }
}

void SettingsDialog::on_font_clicked()
{
    QFontDialog dialog(_font, this);

    if (dialog.exec() == QColorDialog::Accepted) {
        _font = dialog.selectedFont();
    }
}

void SettingsDialog::on_penType_activated(int index)
{
    _pen.setStyle(qvariant_cast<Qt::PenStyle>(ui->penType->itemData(index)));
}

void SettingsDialog::on_brushType_activated(int index)
{
    _brush.setStyle(qvariant_cast<Qt::BrushStyle>(ui->brushType->itemData(index)));
}
