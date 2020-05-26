#ifndef PRESETDIALOG_H
#define PRESETDIALOG_H

#include <QDialog>

namespace Ui {
class PresetDialog;
}

class PresetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PresetDialog(QWidget *parent = nullptr);
    ~PresetDialog();

private:
    Ui::PresetDialog *ui;
};

#endif // PRESETDIALOG_H
