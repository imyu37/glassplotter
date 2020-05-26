#include "presetdialog.h"
#include "ui_presetdialog.h"

PresetDialog::PresetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetDialog)
{
    ui->setupUi(this);
}

PresetDialog::~PresetDialog()
{
    delete ui;
}
