#include "dispersionplotmanager.h"

DispersionPlotManager::DispersionPlotManager(QCustomPlot* customPlot)
{
    _customPlot = customPlot;
    //_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
    //                             QCP::iSelectLegend | QCP::iSelectPlottables);
    _customPlot->setInteractions(QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    _maxGraphCount = 5;

    _xrange = QCPRange(300,1000);
    _yrange = QCPRange(0.9,2.1);

    setDefaultAxis();
}

void DispersionPlotManager::addGraph(Glass *glass)
{
    QCPGraph* graph = _customPlot->addGraph();

    QVector<double> x(101),y(101);

    double lambdamin = _xrange.lower/1000;
    double lambdamax = _xrange.upper/1000;

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        y[i] = glass->index(x[i]);

        x[i] *= 1000; //micron to nano
        qDebug("%f, %f", x[i], y[i]);
    }
    graph->setData(x,y);
    graph->setName(glass->supplyer() + ": " + glass->name());
    graph->setVisible(true);
    _customPlot->legend->setVisible(true);
}

void DispersionPlotManager::deleteGraph()
{
    if(_customPlot->selectedGraphs().size() > 0)
    {
        _customPlot->removeGraph(_customPlot->selectedGraphs().first());
        _customPlot->replot();
    }
}

void DispersionPlotManager::replot()
{
    _customPlot->replot();
}

void DispersionPlotManager::setAllColors()
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

void DispersionPlotManager::setDefaultAxis()
{
    _xrange = QCPRange(300,1000);
    _yrange = QCPRange(0.9,2.1);
    _customPlot->xAxis->setRange(_xrange);
    _customPlot->yAxis->setRange(_yrange);
}

void DispersionPlotManager::setAxis(QCPRange xr, QCPRange yr)
{
    _xrange = xr;
    _yrange = yr;
    _customPlot->xAxis->setRange(xr);
    _customPlot->yAxis->setRange(yr);
}
