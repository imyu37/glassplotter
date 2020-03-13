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

#include "glassmapmanager.h"

GlassMapManager::GlassMapManager(QCustomPlot* customPlot, QTableWidget* table)
{
    _isReady = false;
    _table = table;

    _customPlot = customPlot;
    _customPlot->setInteraction(QCP::iRangeDrag, true);
    _customPlot->setInteraction(QCP::iRangeZoom, true);
    _customPlot->setInteraction(QCP::iSelectItems, true);
    _customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    _customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    _customPlot->legend->setVisible(false);

    _graphCurve = _customPlot->addGraph();

}

GlassMapManager::~GlassMapManager()
{
    _customPlot->clearGraphs();
    _customPlot->clearItems();
    _customPlot = nullptr;
    _table->clear();
}

QColor GlassMapManager::getColor(QString supplyer)
{
    //get index
    int index = 0;
    for(int i = 0;i < _catalogs.count(); i++)
    {
        if(_catalogs[i]->supplyer() == supplyer)
        {
            index = i;
            break;
        }
    }

    //get color from colormap
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color;
    color = colorgrad.color(index, QCPRange(0,_catalogs.count()));

    return color;
}

void GlassMapManager::createGlassMapAll(int plotType)
{
    if(_catalogs.size() == 0)
    {
        qDebug() << "createGlassMapList: Catalogs has not been loaded";
        return;
    }

    _isReady = false;

    GlassCatalog *catalog;
    QCPScatterChart *chart;

    QVector<double> x,y;
    QVector<QString> str;

    for(int j = 0; j < _catalogs.count();j++)
    {
        catalog = _catalogs[j];

        x.clear();
        y.clear();
        str.clear();

        switch(plotType)
        {
        case 0: //vd-nd
            _customPlot->xAxis->setLabel("vd");
            _customPlot->yAxis->setLabel("nd");
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());           
                y.append(catalog->glass(i)->nd());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 1:
            _customPlot->xAxis->setLabel("ve");
            _customPlot->yAxis->setLabel("ne");
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->ve());
                y.append(catalog->glass(i)->ne());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 2: //ve-ne
            _customPlot->xAxis->setLabel("vd");
            _customPlot->yAxis->setLabel("PgF");
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());
                y.append(catalog->glass(i)->PgF());
                str.append(catalog->glass(i)->name());
            }
            break;
        }

        chart = new QCPScatterChart(_customPlot);
        chart->setData(x,y,str);
        chart->setName(catalog->supplyer());
        chart->setColor(getColor(catalog->supplyer()));
        _glassmaps.insert(catalog->supplyer(),chart);
        //delete chart;
    }
    _isReady = true;
}

void GlassMapManager::clear()
{
    _customPlot->clearGraphs();
    _customPlot->clearItems();
    _glassmaps.clear();
    _graphCurve = _customPlot->addGraph();

    _isReady = false;
}

void GlassMapManager::createTable()
{
    _isReady = false;
    _table->clear();

    // set table format
    _table->setColumnCount( 3 );
    _table->setRowCount( catalogCount() );

    // set header
    _table->setHorizontalHeaderLabels( QStringList() << "CATALOG" << "P" << "L" );

    // set supplyers' names and checkboxes
    QString supplyername;

    if(catalogCount() ==0) return;
    for (int i = 0; i< catalogCount() ; i++)
    {
        supplyername = getCatalog(i)->supplyer();
        _table->setItem( i, ColumnSupplyer, new QTableWidgetItem(supplyername) );     //supplyer
        _table->item(i,ColumnSupplyer)->setBackgroundColor(getColor(supplyername));
        _table->item(i,ColumnSupplyer)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        _table->setItem( i, ColumnPlot, new QTableWidgetItem("")  );                   //plot
        _table->item(i,ColumnPlot)->setCheckState(Qt::Unchecked );

        _table->setItem( i, ColumnLabel, new QTableWidgetItem("")  );                  //label
        _table->item(i,ColumnLabel)->setCheckState(Qt::Unchecked );
    }

    _table->setColumnWidth(ColumnSupplyer,(_table->width() - _table->verticalHeader()->width()) /3);
    _table->setColumnWidth(ColumnPlot,    (_table->width() - _table->verticalHeader()->width()) /3);
    _table->setColumnWidth(ColumnLabel,   (_table->width() - _table->verticalHeader()->width()) /3);

    _isReady = true;
}



void GlassMapManager::setCurveCoefs(QList<double> coefs)
{
    if(!_graphCurve) return;

    QVector<double> x(101),y(101);
    double xmin, xmax;

    xmin = 10;
    xmax = 100;

    for(int i = 0; i<101; i++)
    {
        x[i] = xmin + (xmax-xmin)*(double)i/100;

        y[i] = 0;
        for(int j = 0;j < coefs.count(); j ++)
        {
            y[i] += coefs[j]*pow(x[i],j);
        }
    }

    _graphCurve->setData(x,y);
    _graphCurve->setName("curve");

    QPen pen;
    pen.setColor(Qt::black); //black
    _graphCurve->setPen(pen);

}

void GlassMapManager::updateVisible()
{
    if(_isReady){
        for(int i = 0 ;i<_table->rowCount();i++)
        {
            setChartVisible(_table->item(i,ColumnSupplyer)->text(),
                            _table->item(i,ColumnPlot)->checkState(),
                            _table->item(i,ColumnLabel)->checkState());
        }
        _customPlot->replot();
    }

}

void GlassMapManager::setChartVisible(QString supplyer,bool pointstate, bool labelstate)
{
    _glassmaps[supplyer]->setVisiblePointSeries(pointstate);
    _glassmaps[supplyer]->setVisibleTextLabels(labelstate);
}
void GlassMapManager::setCurveVisible(bool state)
{
    _graphCurve->setVisible(state);
}

void GlassMapManager::setAxis(QCPRange xrange, QCPRange yrange)
{
    _customPlot->xAxis->setRange(xrange);
    _customPlot->yAxis->setRange(yrange);
}

void GlassMapManager::setDefaultAxis(int plotType)
{
    QCPRange xrange, yrange;

    switch(plotType)
    {
    case 0: // vd-nd
        xrange.lower = 10;
        xrange.upper = 100;
        yrange.lower = 1.4;
        yrange.upper = 2.1;
        break;
    case 1: // ve-ne
        xrange.lower = 10;
        xrange.upper = 100;
        yrange.lower = 1.4;
        yrange.upper = 2.1;
        break;
    case 2: //vd-PgF
        xrange.lower = 10;
        xrange.upper = 100;
        yrange.lower = 0.5;
        yrange.upper = 0.7;
    default:
        break;
    }

    _customPlot->xAxis->setRangeReversed(true);
    _customPlot->xAxis->setRange(xrange);
    _customPlot->yAxis->setRange(yrange);
}

int GlassMapManager::selectedItemsCount()
{
    return _customPlot->selectedItems().size();
}

Glass* GlassMapManager::getSelectedGlass()
{
    if(_customPlot->selectedItems().size() > 0){
        return getGlass(_customPlot->selectedItems().first()->objectName());
    }
    return nullptr;
}

void GlassMapManager::replot()
{
    _customPlot->replot();
}
