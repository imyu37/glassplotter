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

#ifndef GLASSMAPFORM_H
#define GLASSMAPFORM_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QScrollArea>

#include "glasscatalog.h"
#include "qcpscatterchart.h"

namespace Ui {
class GlassMapForm;
}

class GlassMapForm : public QWidget
{
    Q_OBJECT

public:
    explicit GlassMapForm(QList<GlassCatalog*> catalogList, int plotType = 0, QWidget *parent = nullptr);
    ~GlassMapForm();

    void setUpScrollArea();
    void setUpCurveCtrl();

    void createGlassMaps();

    void setCurveData(QList<double> coefs);

    void setChartVisible(QCPScatterChart* chart, bool pointstate, bool labelstate);
    void setCurveVisible(bool state);

    void setDefault();

    QColor getColor(QString supplyer);

private slots:
    void update();
    void resetView();

private:
    Ui::GlassMapForm *ui;

    QCustomPlot* m_customPlot;

    QList<GlassCatalog*> m_catalogList;

    QList<QCPScatterChart*> m_glassMapList;
    QCPGraph* m_curveGraph;

    QList<QCheckBox*> m_checkBoxPlotList;
    QList<QCheckBox*> m_checkBoxLabelList;
    QList<QLabel*> m_supplyerNameLabelList;

    QList<QLineEdit*> m_curveCoefEditList;
    QList<double> m_curveCoefList;

    int m_plotType;
};

#endif // GLASSMAPFORM_H
