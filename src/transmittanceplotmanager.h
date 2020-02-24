#ifndef TRANSMITTANCEPLOTMANAGER_H
#define TRANSMITTANCEPLOTMANAGER_H

#include "qcustomplot.h"
#include "glasscatalogmanager.h"

class TransmittancePlotManager:public GlassCatalogManager
{
public:
    TransmittancePlotManager(QCustomPlot* customPlot);
    void addGraph(Glass* glass);
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

#endif // TRANSMITTANCEPLOTMANAGER_H
