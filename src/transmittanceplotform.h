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

#ifndef TRANSMITTANCEPLOTFORM_H
#define TRANSMITTANCEPLOTFORM_H

#include <QWidget>

#include "qcustomplot.h"
#include "glasscatalog.h"

#include "glassselectiondialog.h"

namespace Ui {
class TransmittancePlotForm;
}

class TransmittancePlotForm : public QWidget
{
    Q_OBJECT

public:
    explicit TransmittancePlotForm(QList<GlassCatalog*> catalogList, QWidget *parent = nullptr);
    ~TransmittancePlotForm();

    void setData(QCPGraph *graph, Glass *glass);
    void setColor(QCPGraph *graph, int index);

    void updateColor();

    void setDefault();

private slots:
    void addGraph();
    void deleteGraph();
    void setAxis();

private:

    class PlottedGraph
    {
    public:
        QString name;
        Glass* glass;
        QCPGraph* graph;
    };

    QList<PlottedGraph*> m_plottedGraphList;

    QList<GlassCatalog*> m_catalogList;

    Ui::TransmittancePlotForm *ui;

    QCustomPlot* m_customPlot;
    const int m_maxGraphCount = 5;
    QCPRange m_xrange;
    QCPRange m_yrange;
};

#endif // TRANSMITTANCEPLOTFORM_H
