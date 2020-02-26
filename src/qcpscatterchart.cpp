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


#include "qcpscatterchart.h"

QCPScatterChart::QCPScatterChart(QCustomPlot *customPlot)
{  
    _customPlot = customPlot;
    _graphPoints = _customPlot->addGraph();
    _textlabels.clear();
}

QCPScatterChart::~QCPScatterChart()
{
    _graphPoints = NULL;
    _textlabels.clear();
    _customPlot = NULL;
}

QCPScatterChart::QCPScatterChart(QCPScatterChart &other)
{
    _customPlot = other.parentPlot();
    _graphPoints = other.graphPoints();
    _pointCount = other.textLabels().count();
    _textlabels = other.textLabels();
}


void QCPScatterChart::setName(QString name)
{
    _graphPoints->setName(name);
}

void QCPScatterChart::setColor(QColor color)
{
    QPen pen;
    pen.setColor(color);
    _graphPoints->setPen(pen);
}

QCustomPlot* QCPScatterChart::parentPlot()
{
    return _customPlot;
}

QCPGraph* QCPScatterChart::graphPoints()
{
    return _graphPoints;
}


QList<QCPItemText*> QCPScatterChart::textLabels()
{
    return _textlabels;
}

QString QCPScatterChart::name()
{
    return _graphPoints->name();
}

void QCPScatterChart::setData(QVector<double> x, QVector<double> y, QVector<QString> str)
{   
    //set data to points
    //_graphPoints = _customPlot->addGraph();
    _graphPoints->setData(x,y);
    _graphPoints->setLineStyle(QCPGraph::lsNone);
    _graphPoints->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,8));
    _graphPoints->setVisible(false);

    //set text to labels
    _textlabels.clear();
    QCPItemText *label;
    for(int i = 0;i< str.size(); i++){
        label = new QCPItemText(_customPlot);
        _textlabels.append(label);
        _textlabels.last()->position->setCoords(x[i],y[i]);
        _textlabels.last()->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
        _textlabels.last()->setText(str[i]);
        _textlabels.last()->setObjectName(str[i]); //used for mouse click
        _textlabels[i]->setVisible(false);
    }
}

void QCPScatterChart::setVisiblePointSeries(bool state)
{
    if(_customPlot->hasPlottable(_graphPoints)){
        _graphPoints->setVisible(state);
    }
}

void QCPScatterChart::setVisibleTextLabels(bool state)
{
    for(int i = 0; i < _textlabels.size(); i++)
    {
        _textlabels[i]->setVisible(state);
    }
}
