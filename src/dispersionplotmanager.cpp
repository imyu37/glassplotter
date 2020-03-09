/*****************************************************************************
 **                                                                         **
 **  This file is part of GlassPlotter.                                     **
 **                                                                         **
 **  GlassPlotter is free software: you can redistribute it and/or modify   **
 **  it under the terms of the GNU General Public License as published by   **
 **  the Free Software Foundation, either version 3 of the License, or      **
 **  (at your option) any later version.                                    **
 **                                                                         **
 **  GlassPlotter is distributed in the hope that it will be useful,        **
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of         **
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
 **  GNU General Public License for more details.                           **
 **                                                                         **
 **  You should have received a copy of the GNU General Public License      **
 **  along with GlassPlotter.  If not, see <http://www.gnu.org/licenses/>.  **
 **                                                                         **
 *****************************************************************************
 **  Author  : Hiiragi                                                      **
 **  Contact : heterophyllus.work@gmail.com                                 **
 **  Website : https://github.com/heterophyllus/glassplotter                **
 **  Date    : 2020-1-25                                                    **
 *****************************************************************************/

#include "dispersionplotmanager.h"

DispersionPlotManager::DispersionPlotManager(QCustomPlot* customPlot)
{
    _customPlot = customPlot;
    _customPlot->setInteractions(QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    _customPlot->xAxis->setLabel("wavelength(nm)");
    _customPlot->yAxis->setLabel("Refractive Index");

    _xrange = QCPRange(300,1000);
    _yrange = QCPRange(0.9,2.1);
    setDefaultAxis();

    _graphList.clear();
}

DispersionPlotManager::~DispersionPlotManager()
{
    _customPlot->clearGraphs();
    _customPlot->clearItems();
    _customPlot = nullptr;

    _graphList.clear();
}

QCPGraph* DispersionPlotManager::addGraph(Glass *glass)
{    
    QCPGraph* graph;

    if(_graphList.contains(glass)){
        graph = _graphList.value(glass);
    }else{
        graph = _customPlot->addGraph();
        _graphList.insert(glass,graph);
    }
    return graph;
}

void DispersionPlotManager::setData(QCPGraph *graph, Glass *glass)
{
    QVector<double> x(101),y(101);

    double lambdamin = _xrange.lower/1000;
    double lambdamax = _xrange.upper/1000;

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        y[i] = glass->index(x[i]);

        x[i] *= 1000; //micron to nano
    }
    graph->setData(x,y);
    //graph->setName(glass->supplyer() + ":" + glass->name());
    graph->setName(glass->name());
    graph->setVisible(true);
    _customPlot->legend->setVisible(true);
}

void DispersionPlotManager::deleteGraph()
{
    if(_customPlot->selectedGraphs().size() > 0)
    {
        _graphList.remove(getGlass(_customPlot->selectedGraphs().first()->name()));
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
        pen.setWidth(2);
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

    //replot at new axis
    QCPGraph *graph;
    for(int i = 0; i < _graphList.keys().size(); i++)
    {
        graph = addGraph(_graphList.keys().at(i));
        setData(graph, _graphList.keys().at(i));
    }
    replot();
}
