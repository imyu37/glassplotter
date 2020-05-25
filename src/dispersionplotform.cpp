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

#include "dispersionplotform.h"
#include "ui_dispersionplotform.h"

DispersionPlotForm::DispersionPlotForm(QList<GlassCatalog*> catalogList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DispersionPlotForm)
{
    ui->setupUi(this);

    m_catalogList = catalogList;
    m_plottedGraphList.clear();
    m_customPlot = ui->widget;
    m_customPlot->setInteractions(QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    m_customPlot->xAxis->setLabel("Wavelength(nm)");
    m_customPlot->yAxis->setLabel("Refractive Index");
    m_customPlot->legend->setVisible(true);

    m_table = ui->tableWidget;

    QObject::connect(ui->pushButton_AddGraph,   SIGNAL(clicked()), this, SLOT(addGraph()));
    QObject::connect(ui->pushButton_DeleteGraph,SIGNAL(clicked()), this, SLOT(deleteGraph()));
    QObject::connect(ui->pushButton_SetAxis,    SIGNAL(clicked()), this, SLOT(setAxis()));
    QObject::connect(ui->pushButton_Clear,      SIGNAL(clicked()), this, SLOT(clearAll()));
    QObject::connect(ui->checkBox_Legend,       SIGNAL(toggled(bool)), this, SLOT(setLegendVisible()));

    m_curveCtrl = new CurveCtrl(this);
    m_checkBox = ui->checkBox_Curve;
    QObject::connect(ui->checkBox_Curve,       SIGNAL(toggled(bool)), this, SLOT(updateAll()));
    QObject::connect(ui->lineEdit_C0,          SIGNAL(textEdited(QString)), this, SLOT(updateAll()));
    QObject::connect(ui->lineEdit_C1,          SIGNAL(textEdited(QString)), this, SLOT(updateAll()));
    QObject::connect(ui->lineEdit_C2,          SIGNAL(textEdited(QString)), this, SLOT(updateAll()));
    QObject::connect(ui->lineEdit_C3,          SIGNAL(textEdited(QString)), this, SLOT(updateAll()));

    setDefault();
}

DispersionPlotForm::~DispersionPlotForm()
{
    m_catalogList.clear();

    for(int i = 0; i < m_plottedGraphList.size(); i++){
        m_customPlot->removeGraph(m_plottedGraphList[i]->graph);
    }

    delete ui;
}


DispersionPlotForm::CurveCtrl::CurveCtrl(DispersionPlotForm *super)
{
    m_super = super;
    m_super -> m_customPlot = super->m_customPlot;
    graph = m_super->m_customPlot->addGraph();
    graph->setName("curve");

    coefs.clear();
    for(int i = 0; i < 4; i++) coefs.append(0);
}

void DispersionPlotForm::CurveCtrl::setData()
{
    qDebug("Call DispersionPlotForm::CurveCtrl::setData()\n");
    if(!graph) return;

    coefs[0] = m_super->ui->lineEdit_C0->text().toDouble();
    coefs[1] = m_super->ui->lineEdit_C1->text().toDouble();
    coefs[2] = m_super->ui->lineEdit_C2->text().toDouble();
    coefs[3] = m_super->ui->lineEdit_C3->text().toDouble();
    //coefs[4] = m_super->ui->lineEdit_C4->text().toDouble();

    QVector<double> x(101),y(101);
    double xmin, xmax;

    xmin = m_super->m_xrange.lower;
    xmax = m_super->m_xrange.upper;

    for(int i = 0; i < 101; i++)
    {
        x[i] = xmin + (xmax-xmin)*(double)i/100;

        y[i] = 0;
        for(int j = 0;j < coefs.size(); j ++)
        {
            y[i] += coefs[j]*pow(x[i],j);
        }
        qDebug("%f  %f\n", x[i], y[i]);
    }
    xdata = x;
    ydata = y;

    graph->setData(x,y);
    graph->setName("curve");

    QPen pen;
    pen.setColor(Qt::black); //black
    graph->setPen(pen);

}

void DispersionPlotForm::CurveCtrl::setVisible(bool state)
{
    graph->setVisible(state);
}


void DispersionPlotForm::PlottedGraph::setData(QCPRange xrange)
{
    QVector<double> x(101),y(101);

    double lambdamin = xrange.lower/1000;
    double lambdamax = xrange.upper/1000;

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        y[i] = glass->index(x[i]);

        x[i] *= 1000; //micron to nano
    }
    graph->setData(x,y);
    graph->setName(glass->name() + "_" + glass->supplyer() );
    //graph->setName(glass->name());
    graph->setVisible(true);

    xdata = x;
    ydata = y;

}
void DispersionPlotForm::PlottedGraph::setColor(int index)
{
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color = colorgrad.color(index, QCPRange(0, MAX_GRAPH_COUNT));

    QPen pen;
    pen.setWidth(2);
    pen.setColor(color);
    graph->setPen(pen);
}

void DispersionPlotForm::addGraph()
{
    if(m_customPlot->graphCount() >= MAX_GRAPH_COUNT-1){
        QString message = "Up to " + QString::number(MAX_GRAPH_COUNT) + " graphs can be plotted";
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
    }

}


void DispersionPlotForm::updateAll()
{
    // plot
    for(int i = 0; i < m_plottedGraphList.size(); i++)
    {
        m_plottedGraphList[i]->setData(m_xrange);
        m_plottedGraphList[i]->setColor(i);
    }

    m_curveCtrl->setData();
    m_curveCtrl->setVisible(m_checkBox->checkState());

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


void DispersionPlotForm::deleteGraph()
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

void DispersionPlotForm::setDefault()
{
    m_xrange = QCPRange(300,1000);
    m_yrange = QCPRange(0.9,2.1);

    ui->lineEdit_Xmin->setText(QString::number(m_xrange.lower));
    ui->lineEdit_Xmax->setText(QString::number(m_xrange.upper));
    ui->lineEdit_Ymin->setText(QString::number(m_yrange.lower));
    ui->lineEdit_Ymax->setText(QString::number(m_yrange.upper));

    m_customPlot->xAxis->setRange(m_xrange);
    m_customPlot->yAxis->setRange(m_yrange);
}

void DispersionPlotForm::setAxis()
{
    m_xrange.lower = ui->lineEdit_Xmin->text().toDouble();
    m_xrange.upper = ui->lineEdit_Xmax->text().toDouble();
    m_yrange.lower = ui->lineEdit_Ymin->text().toDouble();
    m_yrange.upper = ui->lineEdit_Ymax->text().toDouble();

    m_customPlot->xAxis->setRange(m_xrange);
    m_customPlot->yAxis->setRange(m_yrange);

    updateAll();
}

void DispersionPlotForm::clearAll()
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
void DispersionPlotForm::setLegendVisible()
{
    m_customPlot->legend->setVisible(ui->checkBox_Legend->checkState());
    m_customPlot->replot();
}
