#ifndef GLASSPROPERTYDLG_H
#define GLASSPROPERTYDLG_H

#include <QDialog>
#include "qcustomplot.h"
#include "glass.h"
#include "glasscatalog.h"

namespace Ui {
class GlassPropertyDlg;
}

class GlassPropertyDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GlassPropertyDlg(QWidget *parent = nullptr);
    ~GlassPropertyDlg();

    void plotDispersion(Glass *glass);
    void plotInternalTransmittance(Glass *glass);

private:
    Ui::GlassPropertyDlg *ui;

    QCustomPlot* _customPlot;

};

#endif // GLASSPROPERTYDLG_H
