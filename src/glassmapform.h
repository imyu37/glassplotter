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

#include "glassdatasheetform.h"

namespace Ui {
class GlassMapForm;
}

class GlassMapForm : public QWidget
{
    Q_OBJECT

public:
    explicit GlassMapForm(QList<GlassCatalog*> catalogList, int plotType = 0, QMdiArea *parent = nullptr);
    ~GlassMapForm();

    class GlassMapCtrl
    {
    public:
        GlassMapCtrl(QCustomPlot *customPlot);
        ~GlassMapCtrl();
        QString name;
        GlassCatalog* catalog;
        QCPScatterChart* glassmap;
        QLabel* labelSupplyer;
        QCheckBox* checkBoxPlot;
        QCheckBox* checkBoxLabel;
        void setGlassMap(int plotType, QColor color);
        void setVisible(bool pointState, bool labelState);
        void setVisible();
    private:
        QCustomPlot* m_customPlot;
    };

    class CurveCtrl
    {
    public:
        CurveCtrl(QCustomPlot* customPlot);
        ~CurveCtrl();
        QCPGraph* graph;
        QList<QLineEdit*> lineEditList;
        QGroupBox* checkBox; //User defined curve is controled with checkbox inside of groupbox
        QList<double> coefs;
        void setData();
        void setVisible(bool state);
        void setVisible();
        void getCoefsFromUI();
        void setCoefsToUI();
    private:
        QCustomPlot* m_customPlot;
    };

    void setUpScrollArea();
    void setUpCurveCtrl();

    void setDefault();

    QColor getColorFromIndex(int index);

private slots:
    void contextMenuRequest(QPoint pos);
    void showGlassDataSheet();

    void update();
    void resetView();

private:
    Ui::GlassMapForm *ui;

    QMdiArea* m_parentMdiArea;
    QCustomPlot* m_customPlot;

    QList<GlassCatalog*> m_catalogList;
    QList<GlassMapCtrl*> m_glassMapCtrlList;

    CurveCtrl *m_curveCtrl;

    int m_plotType;

    Glass* getGlassFromName(QString glassName);
};

#endif // GLASSMAPFORM_H
