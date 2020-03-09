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

#ifndef GLASSMAPMANAGER_H
#define GLASSMAPMANAGER_H

#include "qcpscatterchart.h"
#include "glasscatalogmanager.h"
#include <QTableWidget>
#include <QString>

class GlassMapManager: public GlassCatalogManager
{
public:
    GlassMapManager(QCustomPlot* customPlot, QTableWidget* table);
    ~GlassMapManager();

    QColor getColor(QString supplyer);

    void createGlassMapList(int plotType);
    void clearGlassMapList();

    void createTable();

    void setCurveCoefs(QList<double> coefs);

    void updateVisible();
    void setChartVisible(QString supplyer,bool pointstate, bool labelstate);
    void setCurveVisible(bool state);

    void setAxis(QCPRange xrange, QCPRange yrange);
    void setDefaultAxis(int plotType);

    int selectedItemsCount();
    Glass* getSelectedGlass();

    void clear();
    void replot();


private:
    QCustomPlot* _customPlot;
    QTableWidget* _table;

    static const int ColumnSupplyer = 0;
    static const int ColumnPlot     = 1;
    static const int ColumnLabel    = 2;

    bool _isReady;

    QHash<QString, QCPScatterChart* > _glassmaps; //<supplyer, currentmap>

    QCPGraph* _pCurveGraph;
    QList<double> _curvecoefs;

};

#endif // GLASSMAPMANAGER_H
