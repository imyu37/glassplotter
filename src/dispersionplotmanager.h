#ifndef DISPERSIONPLOTMANAGER_H
#define DISPERSIONPLOTMANAGER_H

#include "qcustomplot.h"
#include <QList>

#include "glass.h"
#include "glasscatalog.h"
#include "glasscatalogmanager.h"

class DispersionPlotManager : public GlassCatalogManager
{
public:
    DispersionPlotManager(QCustomPlot* customPlot);
    void addGraph(Glass *glass);
    void deleteGraph();
    void setAllColors();

    void setDefaultAxis();
    void setAxis(QCPRange xr, QCPRange yr);

    void replot();

private:
    QCustomPlot* _customPlot;
    int _maxGraphCount;
    QCPRange _xrange;
    QCPRange _yrange;
};

#endif // DISPERSIONPLOTMANAGER_H
