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

#ifndef TRANSMITTANCEPLOTMANAGER_H
#define TRANSMITTANCEPLOTMANAGER_H

#include "qcustomplot.h"
#include "glasscatalogmanager.h"

class TransmittancePlotManager:public GlassCatalogManager
{
public:
    TransmittancePlotManager(QCustomPlot* customPlot, QTableWidget *table);
    ~TransmittancePlotManager();
    void addGraph(Glass* glass);
    void deleteGraph();
    bool hasGraph(Glass* glass);
    void setAllColors();
    void setDefaultAxis();
    void setAxis(QCPRange xr, QCPRange yr);
    void replot();

    void createTransmittanceDataTable(Glass* glass);
    void clearTransmittanceDataTable();

private:
    QCustomPlot* _customPlot;
    QTableWidget* _table;
    int _maxGraphCount;
    QCPRange _xrange;
    QCPRange _yrange;

    QList<Glass*> _glassList;
};

#endif // TRANSMITTANCEPLOTMANAGER_H
