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


GlassMapForm::GlassMapForm(QList<GlassCatalog*> catalogList, int plotType, QMdiArea *parent) :
    QWidget(parent),
    ui(new Ui::GlassMapForm)
{
    if(catalogList.empty()){
        return;
    }

    m_catalogList = catalogList;
    m_parentMdiArea = parent;
    m_plotType = plotType;

    ui->setupUi(this);

    m_customPlot = ui->widget;
    m_customPlot->setInteraction(QCP::iRangeDrag, true);
    m_customPlot->setInteraction(QCP::iRangeZoom, true);
    m_customPlot->setInteraction(QCP::iSelectItems, true);
    m_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    m_customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    m_customPlot->legend->setVisible(true);

    m_curveCtrl = new CurveCtrl(m_customPlot);
    setUpCurveCtrl();

    GlassMapCtrl* entry;
    for(int i = 0; i < catalogList.size(); i++)
    {
        entry = new GlassMapCtrl(m_customPlot);
        entry->catalog = catalogList.at(i);
        entry->setGlassMap(m_plotType, getColorFromIndex(i));
        m_glassMapCtrlList.append(entry);
    }
    setUpScrollArea();

    //mouse
    QObject::connect(m_customPlot,SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(contextMenuRequest(QPoint)));

    // reset view button
    QObject::connect(ui->pushButton_resetView, SIGNAL(clicked()), this, SLOT(resetView()));

    setDefault();
    update();
}

GlassMapForm::~GlassMapForm()
{
    m_customPlot->clearPlottables();
    m_customPlot->clearItems();
    m_glassMapCtrlList.clear();
    m_customPlot = nullptr;

    delete ui;
}

GlassMapForm::GlassMapCtrl::GlassMapCtrl(QCustomPlot *customPlot)
{
    m_customPlot = customPlot;
    catalog = new GlassCatalog;
    glassmap = new QCPScatterChart(m_customPlot);
    labelSupplyer = new QLabel;
    checkBoxPlot = new QCheckBox;
    checkBoxLabel = new QCheckBox;
}

GlassMapForm::GlassMapCtrl::~GlassMapCtrl()
{
    try{
        delete catalog;
        catalog = nullptr;
        delete glassmap;
        glassmap = nullptr;
        delete labelSupplyer;
        labelSupplyer = nullptr;
        delete checkBoxPlot;
        checkBoxPlot = nullptr;
        delete checkBoxLabel;
        checkBoxLabel = nullptr;
    } catch (...) {
        catalog = nullptr;
        glassmap = nullptr;
        labelSupplyer = nullptr;
        checkBoxPlot = nullptr;
        checkBoxLabel = nullptr;
    }
    m_customPlot = nullptr;
}

void GlassMapForm::GlassMapCtrl::setGlassMap(int plotType, QColor color)
{
    QVector<double> x,y;
    QVector<QString> str;

        x.clear();
        y.clear();
        str.clear();

        switch(plotType)
        {
        case 0: //vd-nd
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());
                y.append(catalog->glass(i)->nd());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 1:
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->ve());
                y.append(catalog->glass(i)->ne());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 2:
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());
                y.append(catalog->glass(i)->PgF());
                str.append(catalog->glass(i)->name());
            }
            break;
        case 3:
            for(int i = 0; i < catalog->glassCount(); i++)
            {
                x.append(catalog->glass(i)->vd());
                y.append(catalog->glass(i)->Pxy("C","t"));
                str.append(catalog->glass(i)->name());
            }

        }

        glassmap->setData(x,y,str);
        glassmap->setName(catalog->supplyer());
        glassmap->setColor(color);
}

void GlassMapForm::GlassMapCtrl::setVisible(bool pointstate, bool labelstate)
{
    glassmap->setVisiblePointSeries(pointstate);
    glassmap->setVisibleTextLabels(labelstate);
}

void GlassMapForm::GlassMapCtrl::setVisible()
{
    setVisible(checkBoxPlot->checkState(), checkBoxLabel->checkState());
}

GlassMapForm::CurveCtrl::CurveCtrl(QCustomPlot* customPlot)
{
    m_customPlot = customPlot;
    graph = m_customPlot->addGraph();

    lineEditList.clear();
    checkBox = new QGroupBox;
}

GlassMapForm::CurveCtrl::~CurveCtrl()
{
    m_customPlot->removeGraph(graph);
    lineEditList.clear();
    coefs.clear();
    delete checkBox;
    m_customPlot = nullptr;
}

void GlassMapForm::contextMenuRequest(QPoint pos)
{
    if(m_customPlot->selectedItems().size() > 0){ //at least one text item should be selected
        QMenu* contextMenu;
        contextMenu = new QMenu(this);
        contextMenu->setAttribute(Qt::WA_DeleteOnClose);
        contextMenu->addAction("Show Property",this,SLOT(showGlassDataSheet()));
        contextMenu->popup(m_customPlot->mapToGlobal(pos));
     }
}

void GlassMapForm::showGlassDataSheet()
{
    if(m_customPlot->selectedItems().size() > 0){
        QString glassName = m_customPlot->selectedItems().first()->objectName();
        Glass* glass = getGlassFromName(glassName);
        GlassDataSheetForm* subwindow = new GlassDataSheetForm(glass, m_parentMdiArea);
        m_parentMdiArea->addSubWindow(subwindow);
        subwindow->parentWidget()->setGeometry(0,10, this->width()*1/2,this->height()*3/4);
        subwindow->show();
    }
}

void GlassMapForm::setUpScrollArea()
{
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QLabel *label;

    //Dynamically create checkboxes
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout_PlotControl"));

    for(int i = 0; i < m_glassMapCtrlList.size(); i++){
        // supplyer name
        label = new QLabel(ui->scrollAreaWidgetContents);
        label->setObjectName("label_" + QString::number(i));
        label->setText(m_catalogList.at(i)->supplyer());
        gridLayout->addWidget(label, i, 0, 1, 1);
        m_glassMapCtrlList.at(i)->labelSupplyer = label;

        // plot on/off
        checkBox = new QCheckBox(ui->scrollAreaWidgetContents);
        checkBox->setObjectName("checkBox_plot_"+QString::number(i));
        checkBox->setText("point");
        gridLayout->addWidget(checkBox, i, 1, 1, 1);
        QObject::connect(checkBox,SIGNAL(toggled(bool)), this, SLOT(update()));
        m_glassMapCtrlList.at(i)->checkBoxPlot = checkBox;

        // label on/off
        checkBox = new QCheckBox(ui->scrollAreaWidgetContents);
        checkBox->setObjectName("checkBox_label_"+QString::number(i));
        checkBox->setText("label");
        QObject::connect(checkBox,SIGNAL(toggled(bool)), this, SLOT(update()));
        gridLayout->addWidget(checkBox, i, 2, 1, 1);
        m_glassMapCtrlList.at(i)->checkBoxLabel = checkBox;
    }
}

void GlassMapForm::setUpCurveCtrl()
{
    QObject::connect(ui->groupBox_UserDefinedCurve,SIGNAL(toggled(bool)),
                         this, SLOT(update()));
    m_curveCtrl->checkBox = ui->groupBox_UserDefinedCurve;

    m_curveCtrl->lineEditList.clear();
    m_curveCtrl->lineEditList << ui->lineEdit_C0 << ui->lineEdit_C1 << ui->lineEdit_C2 << ui->lineEdit_C3;
    for(int i = 0; i < m_curveCtrl->lineEditList.size(); i++){
        QObject::connect(m_curveCtrl->lineEditList[i],SIGNAL(textEdited(QString)),
                             this, SLOT(update()));
    }
}

QColor GlassMapForm::getColorFromIndex(int index)
{
    QCPColorGradient colorgrad;
    colorgrad.loadPreset(QCPColorGradient::gpHues);
    QColor color;
    color = colorgrad.color(index, QCPRange(0,m_catalogList.size()));

    return color;
}

void GlassMapForm::CurveCtrl::setData()
{
    if(!graph) return;

    QVector<double> x(101),y(101);
    double xmin, xmax;

    xmin = 10;
    xmax = 100;

    for(int i = 0; i < 101; i++)
    {
        x[i] = xmin + (xmax-xmin)*(double)i/100;

        y[i] = 0;
        for(int j = 0;j < coefs.size(); j ++)
        {
            y[i] += coefs[j]*pow(x[i],j);
        }
        //qDebug("(x,y)= (%f, %f)", x[i], y[i]);
    }

    graph->setData(x,y);
    graph->setName("curve");

    QPen pen;
    pen.setColor(Qt::black); //black
    graph->setPen(pen);

}

void GlassMapForm::CurveCtrl::setVisible(bool state)
{
    graph->setVisible(state);
}

void GlassMapForm::CurveCtrl::setVisible()
{
    setVisible(checkBox->isChecked());
}

void GlassMapForm::CurveCtrl::getCoefsFromUI()
{
    for (int i = 0; i < lineEditList.size(); i++) {
        coefs[i] = lineEditList.at(i)->text().toDouble();
    }
}

void GlassMapForm::CurveCtrl::setCoefsToUI()
{
    for (int i = 0; i < lineEditList.size(); i++) {
        lineEditList[i]->setText(QString::number(coefs[i]));
    }
}

void GlassMapForm::setDefault()
{
    // Coefs
    m_curveCtrl->coefs.clear();
    switch (m_plotType) {
    case 0:
        m_customPlot->xAxis->setLabel("vd");
        m_customPlot->yAxis->setLabel("nd");

        m_curveCtrl->coefs << 2.43 << -0.028 << 2.03e-4 << 2.9e-7;
        break;
    case 1:
        m_customPlot->xAxis->setLabel("ve");
        m_customPlot->yAxis->setLabel("ne");

        m_curveCtrl->coefs << 2.43 << -0.028 << 2.03e-4 << 2.9e-7;
        break;
    case 2:
        m_customPlot->xAxis->setLabel("vd");
        m_customPlot->yAxis->setLabel("PgF");

        m_curveCtrl->coefs << 7.278e-1 << -5.656e-3 << 5.213e-5 << -1.665e-7;
        break;
    case 3:
        m_customPlot->xAxis->setLabel("vd");
        m_customPlot->yAxis->setLabel("PCt");

        m_curveCtrl->coefs << 0.53 << 0.005 << 0.0<< 0.0;
        break;
    }

    for(int i = 0; i < m_curveCtrl->lineEditList.size();i++){
        m_curveCtrl->lineEditList[i]->setText(QString::number(m_curveCtrl->coefs[i]));
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
     case 3:
         xrange.lower = 10;
         xrange.upper = 100;
         yrange.lower = 0.6;
         yrange.upper = 0.9;
     default:
         break;
     }

     m_customPlot->xAxis->setRangeReversed(true);
     m_customPlot->xAxis->setRange(xrange);
     m_customPlot->yAxis->setRange(yrange);
}

void GlassMapForm::update()
{
    for(int i = 0; i < m_glassMapCtrlList.size(); i++){
        m_glassMapCtrlList.at(i)->setVisible();
    }

    // replot curve
    m_curveCtrl->getCoefsFromUI();
    m_curveCtrl->setData();
    m_curveCtrl->setVisible();

    m_customPlot->replot();
}

void GlassMapForm::resetView()
{
    setDefault();
    m_customPlot->replot();
}

Glass* GlassMapForm::getGlassFromName(QString glassName)
{
    for(int i = 0; i < m_catalogList.size(); i++){
        if(m_catalogList.at(i)->hasGlass(glassName)){
            return m_catalogList.at(i)->glass(glassName);
        }
    }
    return nullptr;
}
