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

#include "transmittanceplotmanager.h"

TransmittancePlotManager::TransmittancePlotManager(QCustomPlot* customPlot, QTableWidget *table)
{
    _customPlot = customPlot;
    _customPlot->setInteractions(QCP::iSelectLegend | QCP::iSelectPlottables);
    _customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    _customPlot->xAxis->setLabel("wavelength(nm)");
    _customPlot->yAxis->setLabel("Internal Transmittance");

    _table = table;
    _table->setColumnCount(3);
    _table->setHorizontalHeaderLabels(QStringList() << "WL" << "Trans" << "Thick" );

    _maxGraphCount = 5;
    _graphList.clear();
    setDefaultAxis();
}
TransmittancePlotManager::~TransmittancePlotManager()
{
    _graphList.clear();
    _table->clear();
    _customPlot->clearGraphs();
    _customPlot->clearItems();
    _customPlot = nullptr;
}

QCPGraph* TransmittancePlotManager::addGraph(Glass *glass)
{
    QCPGraph* graph;

    if(_graphList.contains(glass)){
        graph = _graphList.value(glass);
    }else{
        graph = _customPlot->addGraph();
        _graphList.insert(glass, graph);
    }

    return graph;
}

void TransmittancePlotManager::setData(QCPGraph *graph, Glass *glass)
{
    QVector<double> x(101),y(101), xmicron(101);

    double lambdamin = (double)_xrange.lower/1000;
    double lambdamax = (double)_xrange.upper/1000;

    for(int i = 0; i<101; i++)
    {
        xmicron[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        x[i] = xmicron[i]*1000;
    }

    y = glass->transmittance(xmicron);

    graph->setData(x,y);
    //graph->setName(glass->supplyer() + ": " + glass->name());
    graph->setName(glass->name());
    graph->setVisible(true);
    _customPlot->legend->setVisible(true);
}

void TransmittancePlotManager::deleteGraph()
{
    if(_customPlot->selectedGraphs().size() > 0)
    {
        _graphList.remove(getGlass(_customPlot->selectedGraphs().first()->name()));
        _customPlot->removeGraph(_customPlot->selectedGraphs().first());
        _customPlot->replot();
    }

    //after delete
    if(_customPlot->selectedGraphs().size() > 0)
    {
        createTransmittanceDataTable(getGlass(_customPlot->selectedGraphs().first()->name()));
    }
    else{
        clearTransmittanceDataTable();
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
        pen.setWidth(2);
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

    //replot at new axis
    QCPGraph *graph;
    for(int i = 0; i < _graphList.size(); i++)
    {
        graph = addGraph(_graphList.keys().at(i));
        setData(graph, _graphList.keys().at(i));
    }

    replot();
}


void TransmittancePlotManager::createTransmittanceDataTable(Glass *glass)
{
    if(!hasGlass(glass->name())){
        qDebug() << "TransmittancePlotManager::createTransmittanceDataTable - Glass object not found";
        return;
    }

    _table->clear();
    _table->setColumnCount(3);
    _table->setHorizontalHeaderLabels(QStringList() << "WL" << "Trans" << "Thick" );
    _table->setRowCount(glass->getITsize());

    for(int i = 0; i < glass->getITsize(); i++)
    {
        _table->setItem( i, 0, new QTableWidgetItem(QString::number(glass->getITdata(0,i))) );
        _table->setItem( i, 1, new QTableWidgetItem(QString::number(glass->getITdata(1,i))) );
        _table->setItem( i, 2, new QTableWidgetItem(QString::number(glass->getITdata(2,i))) );
    }
}

void TransmittancePlotManager::clearTransmittanceDataTable()
{
    _table->clear();
    _table->setColumnCount(3);
    _table->setHorizontalHeaderLabels(QStringList() << "WL" << "Trans" << "Thick" );
}
