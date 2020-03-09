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

#ifndef DISPERSIONPLOTMANAGER_H
#define DISPERSIONPLOTMANAGER_H


#include "qcustomplot.h"
#include "glasscatalogmanager.h"

class DispersionPlotManager : public GlassCatalogManager
{
public:
    DispersionPlotManager(QCustomPlot* customPlot);
    ~DispersionPlotManager();
    QCPGraph* addGraph(Glass *glass);
    void setData(QCPGraph *graph, Glass *glass);
    void deleteGraph();

    void setAllColors();

    void setDefaultAxis();
    void setAxis(QCPRange xr, QCPRange yr);

    void replot();

private:
    QCustomPlot* _customPlot;
    const int _maxGraphCount = 5;
    QCPRange _xrange;
    QCPRange _yrange;

    QHash<Glass*, QCPGraph*> _graphList; //<glassname, graph>
};

#endif // DISPERSIONPLOTMANAGER_H
