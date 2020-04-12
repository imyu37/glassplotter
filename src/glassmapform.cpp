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

#include "glassmapform.h"
#include "ui_glassmapform.h"

GlassMapForm::GlassMapForm(QList<GlassCatalog*> catalogList, int plotType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlassMapForm)
{
    ui->setupUi(this);

    if(catalogList.empty()){
        return;
    }else{
        m_catalogList = catalogList;
    }

    m_plotType = plotType;

    m_customPlot = ui->widget;
    m_customPlot->setInteraction(QCP::iRangeDrag, true);
    m_customPlot->setInteraction(QCP::iRangeZoom, true);
    m_customPlot->setInteraction(QCP::iSelectItems, true);
    m_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    m_customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    m_customPlot->legend->setVisible(true);

    m_curveGraph = m_customPlot->addGraph();

    setUpScrollArea();
    setUpCurveCtrl();
    setDefault();
    createGlassMaps();
    update();

    m_catalogList.clear(); //will not be used
}

GlassMapForm::~GlassMapForm()
{
    m_catalogList.clear();
    m_glassMapList.clear();
    m_checkBoxPlotList.clear();
    m_checkBoxLabelList.clear();

    m_customPlot->clearPlottables();

    delete ui;
}

void GlassMapForm::setUpScrollArea()
{
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QLabel *catalogNameLabel;

    m_glassMapList.clear();
    m_checkBoxPlotList.clear();
    m_checkBoxLabelList.clear();

    //Dynamically create checkboxes
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout_PlotControl"));

    for(int i = 0; i < m_catalogList.size(); i++){
        // supplyer name
        catalogNameLabel = new QLabel(ui->scrollAreaWidgetContents);
        catalogNameLabel->setObjectName("label_" + QString::number(i));
        catalogNameLabel->setText(m_catalogList[i]->supplyer());
        gridLayout->addWidget(catalogNameLabel, i, 0, 1, 1);

        // plot on/off
        checkBox = new QCheckBox(ui->scrollAreaWidgetContents);
        checkBox->setObjectName("checkBox_plot_"+QString::number(i));
        checkBox->setText("point");
        gridLayout->addWidget(checkBox, i, 1, 1, 1);
        QObject::connect(checkBox,SIGNAL(toggled(bool)),
                             this, SLOT(update()));
        m_checkBoxPlotList.append(checkBox);

        // label on/off
        checkBox = new QCheckBox(ui->scrollAreaWidgetContents);
        checkBox->setObjectName("checkBox_label_"+QString::number(i));
        checkBox->setText("label");
        QObject::connect(checkBox,SIGNAL(toggled(bool)),
                             this, SLOT(update()));
        gridLayout->addWidget(checkBox, i, 2, 1, 1);
        m_checkBoxLabelList.append(checkBox);
    }
}

void GlassMapForm::setUpCurveCtrl()
{
    m_curveCoefEditList << ui->lineEdit_C0 << ui->lineEdit_C1 << ui->lineEdit_C2 << ui->lineEdit_C3;
    m_curveCoefList << 0.0 << 0.0 << 0.0 << 0.0;

    QObject::connect(ui->groupBox_UserDefinedCurve,SIGNAL(toggled(bool)),
                         this, SLOT(update()));

    for(int i = 0; i < m_curveCoefEditList.size(); i++){
        QObject::connect(m_curveCoefEditList[i],SIGNAL(textEdited(QString)),
                             this, SLOT(update()));
    }
}

void GlassMapForm::createGlassMaps()
{
    GlassCatalog *catalog;
    QCPScatterChart *chart;

    QVector<double> x,y;
    QVector<QString> str;

    for(int j = 0; j < m_catalogList.count();j++)
    {
        catalog = m_catalogList[j];

        x.clear();
        y.clear();
        str.clear();

        switch(m_plotType)
        {
        case 0: //vd-nd
            m_customPlot->xAxis->setLabel("vd");
            m_customPlot->yAxis->setLabel("nd");
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());
                y.append(catalog->glass(i)->nd());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 1:
            m_customPlot->xAxis->setLabel("ve");
            m_customPlot->yAxis->setLabel("ne");
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->ve());
                y.append(catalog->glass(i)->ne());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 2: //ve-ne
            m_customPlot->xAxis->setLabel("vd");
            m_customPlot->yAxis->setLabel("PgF");
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());
                y.append(catalog->glass(i)->PgF());
                str.append(catalog->glass(i)->name());
            }
            break;
        }

        chart = new QCPScatterChart(m_customPlot);
        chart->setData(x,y,str);
        chart->setName(catalog->supplyer());
        chart->setColor(getColor(catalog->supplyer()));
        m_glassMapList.append(chart);
    }
}

void GlassMapForm::setCurveData(QList<double> coefs)
{
    if(!m_curveGraph) return;

    QVector<double> x(101),y(101);
    double xmin, xmax;

    xmin = 10;
    xmax = 100;

    for(int i = 0; i < 101; i++)
    {
        x[i] = xmin + (xmax-xmin)*(double)i/100;

        y[i] = 0;
        for(int j = 0;j < coefs.count(); j ++)
        {
            y[i] += coefs[j]*pow(x[i],j);
        }
    }

    m_curveGraph->setData(x,y);
    m_curveGraph->setName("curve");

    QPen pen;
    pen.setColor(Qt::black); //black
    m_curveGraph->setPen(pen);
}

QColor GlassMapForm::getColor(QString supplyer)
{
    //get index
    int index = 0;
    for(int i = 0;i < m_catalogList.count(); i++)
    {
        if(m_catalogList[i]->supplyer() == supplyer)
        {
            index = i;
            break;
        }
    }

    //get color from colormap
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color = colorgrad.color(index, QCPRange(0,m_catalogList.count()));

    return color;
}

void GlassMapForm::setChartVisible(QCPScatterChart *chart, bool pointstate, bool labelstate)
{
    chart->setVisiblePointSeries(pointstate);
    chart->setVisibleTextLabels(labelstate);
}

void GlassMapForm::setCurveVisible(bool state)
{
    m_curveGraph->setVisible(state);
}

void GlassMapForm::setDefault()
{
    // Coefs

    switch (m_plotType) {
    case 0:

        m_curveCoefList[0] = 2.43;
        m_curveCoefList[1] = -0.028;
        m_curveCoefList[2] = 2.03e-4;
        m_curveCoefList[3] = 2.9e-7;

        //m_curveCoefList << 2.43 << -0.028 << 2.03e-4 << 2.9e-7;
        break;
    case 1:

        m_curveCoefList[0] = 2.43;
        m_curveCoefList[1] = -0.028;
        m_curveCoefList[2] = 2.03e-4;
        m_curveCoefList[3] = 2.9e-7;

        //m_curveCoefList << 2.43 << -0.028 << 2.03e-4 << 2.9e-7;
        break;
    case 2:

        m_curveCoefList[0] = 7.278e-1;
        m_curveCoefList[1] = -5.656e-3;
        m_curveCoefList[2] = 5.213e-5;
        m_curveCoefList[3] = -1.665e-7;

        //m_curveCoefList << 7.278e-1 << -5.656e-3 << 5.213e-5 << -1.665e-7;
        break;
    }

    for(int i = 0; i<m_curveCoefEditList.size();i++){
        m_curveCoefEditList[i]->setText(QString::number(m_curveCoefList[i]));
    }


    // Axis
    QCPRange xrange, yrange;

     switch(m_plotType)
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

     m_customPlot->xAxis->setRangeReversed(true);
     m_customPlot->xAxis->setRange(xrange);
     m_customPlot->yAxis->setRange(yrange);
}


void GlassMapForm::update()
{
    for(int i = 0; i < m_checkBoxPlotList.size(); i++){
        setChartVisible(m_glassMapList[i], m_checkBoxPlotList[i]->checkState(), m_checkBoxLabelList[i]->checkState());
    }

    for (int j = 0; j < m_curveCoefEditList.size(); j++) {
        m_curveCoefList[j] = m_curveCoefEditList[j]->text().toDouble();
    }
    setCurveData(m_curveCoefList);
    setCurveVisible(ui->groupBox_UserDefinedCurve->isChecked());

    m_customPlot->replot();
}

void GlassMapForm::resetView()
{
    setDefault();
    m_customPlot->replot();
}
