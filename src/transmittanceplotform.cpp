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
    m_customPlot->legend->setVisible(true);

    QObject::connect(ui->pushButton_AddGraph,   SIGNAL(clicked()),     this, SLOT(addGraph()));
    QObject::connect(ui->pushButton_DeleteGraph,SIGNAL(clicked()),     this, SLOT(deleteGraph()));
    QObject::connect(ui->pushButton_SetAxis,    SIGNAL(clicked()),     this, SLOT(setAxis()));
    QObject::connect(ui->pushButton_Clear,      SIGNAL(clicked()),     this, SLOT(clearAll()));
    QObject::connect(ui->checkBox_Legend,       SIGNAL(toggled(bool)), this, SLOT(setLegendVisible()));

    m_table = ui->tableWidget;
    setDefault();
}

TransmittancePlotForm::~TransmittancePlotForm()
{
    delete ui;
}

void TransmittancePlotForm::addGraph()
{
    if(m_customPlot->graphCount() >= m_maxGraphCount) // 5 glass
    {
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

        PlottedGraph *plottedGraph = new PlottedGraph;
        plottedGraph->name = glassName;
        plottedGraph->glass = newGlass;
        plottedGraph->graph = newGraph;

        m_plottedGraphList.append(plottedGraph);

        updateAll();
        m_customPlot->replot();
    }

}

void TransmittancePlotForm::PlottedGraph::setData(QCPRange xrange)
{
    QVector<double> x(101),y(101), xmicron(101);

    double lambdamin = (double)xrange.lower/1000;
    double lambdamax = (double)xrange.upper/1000;

    //double lambdamin = glass->lambdaMin();
    //double lambdamax = glass->lambdaMax();

    for(int i = 0; i<101; i++)
    {
        xmicron[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        x[i] = xmicron[i]*1000;
    }

    y = glass->transmittance(xmicron, m_thickness);

    xdata = x;
    ydata = y;

    graph->setData(x,y);
    //graph->setName(glass->name() + "_" + glass->supplyer());
    graph->setName(glass->name());
    graph->setVisible(true);
    //m_customPlot->legend->setVisible(true);
}

void TransmittancePlotForm::PlottedGraph::setColor(int index)
{
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color = colorgrad.color(index, QCPRange(0, MAX_GRAPH_COUNT));

    QPen pen;
    pen.setWidth(2);
    pen.setColor(color);

    graph->setPen(pen);
}

void TransmittancePlotForm::updateAll()
{
    for(int i = 0; i < m_plottedGraphList.size(); i++){
        m_plottedGraphList[i]->m_thickness = ui->lineEdit_Thickness->text().toDouble();
        m_plottedGraphList[i]->setData(m_xrange);
        m_plottedGraphList[i]->setColor(i);
    }
    m_customPlot->replot();

    // table
    int rowCount = m_plottedGraphList[0]->xdata.size();
    int columnCount = m_plottedGraphList.size() + 1; // lambda + glasses
    m_table->clear();
    m_table->setRowCount(rowCount);
    m_table->setColumnCount(columnCount);

    QStringList header = QStringList() << "WVL";
    for(int j = 0;j<m_plottedGraphList.size();j++)
    {
        header << m_plottedGraphList[j]->name;
    }
    m_table->setHorizontalHeaderLabels(header);

    QTableWidgetItem* item;
    for(int i = 0; i< rowCount; i++)
    {
        // wavelength
        item = new QTableWidgetItem;
        item->setText(QString::number(m_plottedGraphList[0]->xdata[i]));
        m_table->setItem(i, 0, item);

        // refractive indices
        for(int j = 1; j<columnCount; j++)
        {
            item = new QTableWidgetItem;
            item->setText( QString::number(m_plottedGraphList[j-1]->ydata[i]) );
            m_table->setItem(i, j, item);
        }
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
        updateAll();
    }
}

void TransmittancePlotForm::setDefault()
{
    m_xrange = QCPRange(300,2000);
    m_yrange = QCPRange(0.0,1.2);
    //m_thickness = 25;

    m_customPlot->xAxis->setRange(m_xrange);
    m_customPlot->yAxis->setRange(m_yrange);

    ui->lineEdit_Xmin->setText(QString::number(m_xrange.lower));
    ui->lineEdit_Xmax->setText(QString::number(m_xrange.upper));
    ui->lineEdit_Ymin->setText(QString::number(m_yrange.lower));
    ui->lineEdit_Ymax->setText(QString::number(m_yrange.upper));

    ui->lineEdit_Thickness->setText(QString::number(25));
}

void TransmittancePlotForm::setAxis()
{
    m_xrange.lower = ui->lineEdit_Xmin->text().toDouble();
    m_xrange.upper = ui->lineEdit_Xmax->text().toDouble();
    m_yrange.lower = ui->lineEdit_Ymin->text().toDouble();
    m_yrange.upper = ui->lineEdit_Ymax->text().toDouble();

    m_customPlot->xAxis->setRange(m_xrange);
    m_customPlot->yAxis->setRange(m_yrange);

    updateAll();
    m_customPlot->replot();
}

void TransmittancePlotForm::clearAll()
{
    for(int i = 0; i < m_plottedGraphList.size();i++){
        try {
            delete m_plottedGraphList[i];
        } catch (...) {
            m_plottedGraphList[i] = nullptr;
        }
    }
    m_plottedGraphList.clear();
    m_customPlot->clearGraphs();
    m_customPlot->replot();
}

void TransmittancePlotForm::setLegendVisible()
{
    m_customPlot->legend->setVisible(ui->checkBox_Legend->checkState());
    m_customPlot->replot();
}
