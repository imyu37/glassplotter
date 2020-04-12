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


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "aboutdialog.h"
#include "glassmapform.h"
#include "dispersionplotform.h"
#include "transmittanceplotform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // File menu
    QObject::connect(ui->action_loadAGF,SIGNAL(triggered()), this, SLOT(loadAGF()));

    // Tools menu
    QObject::connect(ui->action_NdVd,    SIGNAL(triggered()),this, SLOT(showGlassMapNdVd()));
    QObject::connect(ui->action_NeVe,    SIGNAL(triggered()),this, SLOT(showGlassMapNeVe()));
    QObject::connect(ui->action_VdPgF,   SIGNAL(triggered()),this, SLOT(showGlassMapVdPgF()));
    QObject::connect(ui->action_DispersionPlot, SIGNAL(triggered()),this, SLOT(showDispersionPlot()));
    QObject::connect(ui->action_TransmittancePlot, SIGNAL(triggered()),this, SLOT(showTransmittancePlot()));
    QObject::connect(ui->action_CloseAll,SIGNAL(triggered()),this, SLOT(closeAll()));

    // Help menu
    QObject::connect(ui->action_About, SIGNAL(triggered()), this, SLOT(showAbout()));

    //setAttribute(Qt::WA_DeleteOnClose);
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAGF()
{
    m_catalogList.clear();

    QStringList filePaths = QFileDialog::getOpenFileNames(this,
                                                          tr("select AGF"),
                                                          tr("AGF files(*.agf);;All Files(*.*)"));
    if(filePaths.empty()){
        QMessageBox::information(this,tr("File"), tr("No AGF file loaded"));
        return;
    }

    GlassCatalog* catalog;
    for(int i = 0; i < filePaths.size(); i++){
        catalog = new GlassCatalog;
        catalog->loadAGF(filePaths[i]);
        m_catalogList.append(catalog);
        qDebug("%s",m_catalogList[i]->supplyer().toUtf8().data());
    }
}

void MainWindow::showAbout()
{
    AboutDialog *dlg = new AboutDialog(this);
    dlg->exec();
}

void MainWindow::showGlassMapNdVd()
{
    int plotType = 0;

    if(m_catalogList.empty()){
        QMessageBox::information(this,tr("File"), tr("catalog list empty"));
        return;
    }

    GlassMapForm *subwindow = new GlassMapForm(m_catalogList, plotType, ui->mdiArea);
    ui->mdiArea->addSubWindow(subwindow);

    subwindow->setWindowTitle("Vd - Nd Map");
    subwindow->show();
}

void MainWindow::showGlassMapNeVe()
{
    int plotType = 1;

    if(m_catalogList.empty()){
        QMessageBox::information(this,tr("File"), tr("catalog list empty"));
        return;
    }

    GlassMapForm *subwindow = new GlassMapForm(m_catalogList, plotType, ui->mdiArea);
    ui->mdiArea->addSubWindow(subwindow);

    subwindow->setWindowTitle("Ve - Ne Map");
    subwindow->show();
}

void MainWindow::showGlassMapVdPgF()
{
    int plotType = 2;

    if(m_catalogList.empty()){
        QMessageBox::information(this,tr("File"), tr("catalog list empty"));
        return;
    }

    GlassMapForm *subwindow = new GlassMapForm(m_catalogList, plotType, ui->mdiArea);
    ui->mdiArea->addSubWindow(subwindow);

    subwindow->setWindowTitle("Vd - PgF Map");
    subwindow->show();
}

void MainWindow::showDispersionPlot()
{
    if(m_catalogList.empty()){
        QMessageBox::information(this,tr("File"), tr("catalog list empty"));
        return;
    }

    DispersionPlotForm *subwindow = new DispersionPlotForm(m_catalogList, ui->mdiArea);
    ui->mdiArea->addSubWindow(subwindow);
    subwindow->setWindowTitle("Dispersion Plot");
    subwindow->show();
}

void MainWindow::showTransmittancePlot()
{
    if(m_catalogList.empty()){
        QMessageBox::information(this,tr("File"), tr("catalog list empty"));
        return;
    }

    TransmittancePlotForm *subwindow = new TransmittancePlotForm(m_catalogList, ui->mdiArea);
    ui->mdiArea->addSubWindow(subwindow);
    subwindow->setWindowTitle("Transmittance Plot");
    subwindow->show();
}

void MainWindow::closeAll()
{
    ui->mdiArea->closeAllSubWindows();
}
