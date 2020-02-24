#ifndef GLASSPROPERTYDLG_H
#define GLASSPROPERTYDLG_H

#include <QDialog>
#include "qcustomplot.h"
#include "glass.h"


namespace Ui {
class GlassPropertyDlg;
}

class GlassPropertyDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GlassPropertyDlg(QWidget *parent = nullptr);
    ~GlassPropertyDlg();

    void setProperty(Glass* glass);

private:
    Ui::GlassPropertyDlg *ui;
    Glass* _glass;

};

#endif // GLASSPROPERTYDLG_H
