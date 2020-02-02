#include "glasspropertydlg.h"
#include "ui_glasspropertydlg.h"

GlassPropertyDlg::GlassPropertyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlassPropertyDlg)
{
    ui->setupUi(this);

    _customPlot = ui->plotWidget;
    _customPlot->setInteraction(QCP::iRangeDrag, true);
    _customPlot->setInteraction(QCP::iRangeZoom, true);
}

GlassPropertyDlg::~GlassPropertyDlg()
{
    delete ui;
}

void GlassPropertyDlg::plotDispersion(Glass *glass)
{
    QString glassname    = glass->name();
    QString supplyername = glass->supplyer();

    QCPTextElement *title = new QCPTextElement(_customPlot, supplyername + ": " + glassname);
    _customPlot->plotLayout()->insertRow(0);
    _customPlot->plotLayout()->addElement(0, 0, title);

    QCPGraph *graph;
    QVector<double> x(101), y(101);
    double lambdamin = glass->lambdaMin();
    double lambdamax = glass->lambdaMax();
    double ymin = 10;
    double ymax = 0;

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        y[i] = glass->index(x[i]);

        if(ymin > y[i]) ymin = y[i];
        if(ymax < y[i]) ymax = y[i];

        //qDebug("%d: %f, %f",i,x[i],y[i]);
    }

    graph = _customPlot->addGraph();
    graph->setData(x,y);
    graph->setName(glass->name());
    graph->setVisible(true);
    _customPlot->xAxis->setRange(lambdamin, lambdamax);
    _customPlot->yAxis->setRange(ymin-0.1, ymax+0.1);
    _customPlot->replot();
}

void GlassPropertyDlg::plotInternalTransmittance(Glass *glass)
{
    QVector<double> x, y;

}
