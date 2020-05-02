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


#include "transmittanceplotform.h"
#include "ui_transmittanceplotform.h"

TransmittancePlotForm::TransmittancePlotForm(QList<GlassCatalog*> catalogList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransmittancePlotForm)
{
    ui->setupUi(this);

    m_catalogList = catalogList;
    m_plottedGraphList.clear();
    m_customPlot = ui->widget;
    m_customPlot->setInteractions(QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    m_customPlot->xAxis->setLabel("Wavelength(nm)");
    m_customPlot->yAxis->setLabel("Internal Transmittance");

    QObject::connect(ui->pushButton_AddGraph,   SIGNAL(clicked()), this, SLOT(addGraph()));
    QObject::connect(ui->pushButton_DeleteGraph,SIGNAL(clicked()), this, SLOT(deleteGraph()));
    QObject::connect(ui->pushButton_SetAxis,    SIGNAL(clicked()), this, SLOT(setAxis()));

    setDefault();
}

TransmittancePlotForm::~TransmittancePlotForm()
{
    delete ui;
}

void TransmittancePlotForm::addGraph()
{
    if(m_customPlot->graphCount() >= m_maxGraphCount-1){
        QString message = "Up to " + QString::number(m_maxGraphCount) + " graphs can be plotted";
        QMessageBox::information(this,tr("Error"), message);
        return;
    }

    GlassSelectionDialog *dlg = new GlassSelectionDialog(m_catalogList, this);
    if(dlg->exec() == QDialog::Accepted)
    {
        int catalogIndex = dlg->getCatalogIndex();
        QString glassName = dlg->getGlassName();
        Glass* newGlass = m_catalogList.at(catalogIndex)->glass(glassName);
        QCPGraph* newGraph = m_customPlot->addGraph();
        setData(newGraph,newGlass);

        PlottedGraph *plottedGraph = new PlottedGraph;
        plottedGraph->name = glassName;
        plottedGraph->glass = newGlass;
        plottedGraph->graph = newGraph;

        m_plottedGraphList.append(plottedGraph);

        updateColor();
        m_customPlot->replot();
    }

    try {
        delete dlg;
    } catch (...) {
        dlg = nullptr;
    }

}

void TransmittancePlotForm::setData(QCPGraph *graph, Glass *glass)
{
    QVector<double> x(101),y(101), xmicron(101);

    double lambdamin = (double)m_xrange.lower/1000;
    double lambdamax = (double)m_xrange.upper/1000;

    for(int i = 0; i<101; i++)
    {
        xmicron[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        x[i] = xmicron[i]*1000;
    }

    y = glass->transmittance(xmicron, m_thickness);

    graph->setData(x,y);
    //graph->setName(glass->supplyer() + ": " + glass->name());
    graph->setName(glass->name());
    graph->setVisible(true);
    m_customPlot->legend->setVisible(true);
}

void TransmittancePlotForm::setColor(QCPGraph *graph, int index)
{
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color = colorgrad.color(index, QCPRange(0, m_maxGraphCount));

    QPen pen;
    pen.setWidth(2);
    pen.setColor(color);

    graph->setPen(pen);
}

void TransmittancePlotForm::updateColor()
{
    for(int i = 0; i < m_plottedGraphList.size(); i++){
        setColor(m_plottedGraphList.at(i)->graph, i);
    }
}

void TransmittancePlotForm::deleteGraph()
{
    if(m_customPlot->selectedGraphs().size() > 0)
    {
        QCPGraph* selectedGraph = m_customPlot->selectedGraphs().first();
        QString glassName = selectedGraph->name();

        for(int i = 0;i < m_plottedGraphList.size(); i++){
            if(m_plottedGraphList.at(i)->name == glassName){
                m_plottedGraphList.removeAt(i);
                break;
            }
        }
        m_customPlot->removeGraph(selectedGraph);
        updateColor();
        m_customPlot->replot();
    }
}

void TransmittancePlotForm::setDefault()
{
    m_xrange = QCPRange(300,2000);
    m_yrange = QCPRange(0.0,1.2);
    m_thickness = 25;

    m_customPlot->xAxis->setRange(m_xrange);
    m_customPlot->yAxis->setRange(m_yrange);

    ui->lineEdit_Xmin->setText(QString::number(m_xrange.lower));
    ui->lineEdit_Xmax->setText(QString::number(m_xrange.upper));
    ui->lineEdit_Ymin->setText(QString::number(m_yrange.lower));
    ui->lineEdit_Ymax->setText(QString::number(m_yrange.upper));

    ui->lineEdit_Thickness->setText(QString::number(m_thickness));
}

void TransmittancePlotForm::setAxis()
{
    m_xrange.lower = ui->lineEdit_Xmin->text().toDouble();
    m_xrange.upper = ui->lineEdit_Xmax->text().toDouble();
    m_yrange.lower = ui->lineEdit_Ymin->text().toDouble();
    m_yrange.upper = ui->lineEdit_Ymax->text().toDouble();

    m_thickness    = ui->lineEdit_Thickness->text().toDouble();

    m_customPlot->xAxis->setRange(m_xrange);
    m_customPlot->yAxis->setRange(m_yrange);

    //replot on new axis
    for(int i = 0; i < m_plottedGraphList.size(); i++)
    {
        setData(m_plottedGraphList.at(i)->graph, m_plottedGraphList.at(i)->glass);
    }
    updateColor();
    m_customPlot->replot();
}
