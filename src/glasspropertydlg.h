#ifndef GLASSPROPERTYDLG_H
#define GLASSPROPERTYDLG_H

#include <QDialog>
#include "qcustomplot.h"
#include "glass.h"
#include "spline.h"

namespace Ui {
class GlassPropertyDlg;
}

class GlassPropertyDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GlassPropertyDlg(Glass *glass, QWidget *parent = nullptr);
    ~GlassPropertyDlg();


    //Indices tab
    void createIndicesTable();
    void createPartialDispersionTable();

    //Dispersion tab
    void plotDispersion();

    //Transmittance tab
    void plotInternalTransmittance();


private:
    Ui::GlassPropertyDlg *ui;

    QCustomPlot* _dispersionPlot;
    QCustomPlot* _transmittancePlot;
    Glass* _glass;

};

#endif // GLASSPROPERTYDLG_H
