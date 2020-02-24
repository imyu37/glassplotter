#include "transmittanceplotmanager.h"

TransmittancePlotManager::TransmittancePlotManager(QCustomPlot* customPlot)
{
    _customPlot = customPlot;
    _customPlot->setInteractions(QCP::iSelectLegend | QCP::iSelectPlottables);
    _maxGraphCount = 5;

    setDefaultAxis();
}

void TransmittancePlotManager::addGraph(Glass *glass)
{
    QCPGraph* graph = _customPlot->addGraph();

    QVector<double> x(101),y(101);

    //double lambdamin = glass->lambdaMin();
    //double lambdamax = glass->lambdaMax();
    double lambdamin = (double)_xrange.lower/1000;
    double lambdamax = (double)_xrange.upper/1000;

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        x[i] *= 1000;
    }
    y = glass->transmittance(lambdamin, lambdamax, 101);

    for(int i = 0; i < x.count(); i++)
    {
        qDebug("%f,%f", x[i],y[i]);
    }

    graph->setData(x,y);
    graph->setName(glass->supplyer() + ": " + glass->name());
    graph->setVisible(true);
    _customPlot->legend->setVisible(true);
}

void TransmittancePlotManager::deleteGraph()
{
    if(_customPlot->selectedGraphs().size() > 0)
    {
        _customPlot->removeGraph(_customPlot->selectedGraphs().first());
    }
}

void TransmittancePlotManager::replot()
{
    _customPlot->replot();
}

void TransmittancePlotManager::setAllColors()
{
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color;
    QPen pen;

    for(int i = 0;i < _customPlot->graphCount(); i++)
    {
        color = colorgrad.color(i, QCPRange(0,_maxGraphCount));
        pen.setColor(color);
        _customPlot->graph(i)->setPen(pen);
    }
}

void TransmittancePlotManager::setDefaultAxis()
{
    _xrange = QCPRange(300,2000);
    _yrange = QCPRange(0.0,1.0);
    _customPlot->xAxis->setRange(_xrange);
    _customPlot->yAxis->setRange(_yrange);
}
void TransmittancePlotManager::setAxis(QCPRange xr, QCPRange yr)
{
    _xrange = xr;
    _yrange = yr;
    _customPlot->xAxis->setRange(_xrange);
    _customPlot->yAxis->setRange(_yrange);
}
