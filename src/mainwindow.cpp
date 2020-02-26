#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set default value
    _AGFdir = QApplication::applicationDirPath() + "/AGF";

    //---> Glass Map
    _glassmapPlot = ui->widget;
    _glassmapmanager = new GlassMapManager(ui->widget, ui->tableWidget);

    if(!_glassmapmanager->loadAllAGF(_AGFdir)){ // read Zemax AGF in the folder
        QMessageBox::information(this,tr("File"), tr("AGF load missed"));
    }

    _glassmapmanager->createGlassMapList(0);
    _glassmapmanager->resetAxis(0);
    _glassmapmanager->replot();

    //---> Dispersion Plot
    _dispersionPlot = ui->plotWidget_Dispersion;
    _dispersionplotmanager = new DispersionPlotManager(_dispersionPlot);
    _dispersionplotmanager->setCatalogList(_glassmapmanager->getCatalogList()); //copy from glassmap

    //---> Transmittance Plot
    _transmittancePlot = ui->plotWidget_Transmittance;
    _transmittanceplotmanager = new TransmittancePlotManager(_transmittancePlot, ui->tableWidget_TransmittanceData);
    _transmittanceplotmanager->setCatalogList(_glassmapmanager->getCatalogList());

    createUI();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    //---> menu
    QObject::connect(ui->actionLoadAGFfolder,SIGNAL(triggered()),
                     this, SLOT(on_menu_File_LoadAGF_Triggered()));

    QObject::connect(ui->actionAbout,SIGNAL(triggered()),
                     this, SLOT(on_menu_Help_About_Triggered()));

    //---> Map tab
    //combobox
    ui->comboBox_plotType->clear();
    ui->comboBox_plotType->addItem("Nd-Vd");
    ui->comboBox_plotType->addItem("Ne-Ve");
    ui->comboBox_plotType->addItem("Vd-PgF");
    QObject::connect(ui->comboBox_plotType,SIGNAL(currentIndexChanged(int)),
                     this, SLOT(on_comboChanged(int)));

    //mouse
    QObject::connect(_glassmapPlot,SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(contextMenuRequest(QPoint)));

    //user defined curve
    /*
    ui->lineEdit_coef0->setText("7.278e-1");
    ui->lineEdit_coef1->setText("-5.656e-3");
    ui->lineEdit_coef2->setText("5.213e-5");
    ui->lineEdit_coef3->setText("-1.665e-7");
    */
    ui->lineEdit_coef0->setText("2.43");
    ui->lineEdit_coef1->setText("-0.028");
    ui->lineEdit_coef2->setText("2.03e-4");
    ui->lineEdit_coef3->setText("2.9e-7");
    QObject::connect(ui->groupBox_curve,SIGNAL(toggled(bool)),
                     this, SLOT(on_checkBoxCurveChanged(bool)));
    QObject::connect(ui->lineEdit_coef0,SIGNAL(textEdited(QString)),
                     this, SLOT(on_lineEdit_textEdited()));
    QObject::connect(ui->lineEdit_coef1,SIGNAL(textEdited(QString)),
                     this, SLOT(on_lineEdit_textEdited()));
    QObject::connect(ui->lineEdit_coef2,SIGNAL(textEdited(QString)),
                     this, SLOT(on_lineEdit_textEdited()));
    QObject::connect(ui->lineEdit_coef3,SIGNAL(textEdited(QString)),
                     this, SLOT(on_lineEdit_textEdited()));

    //reset view button
    QObject::connect(ui->button_resetView,SIGNAL(clicked()),
                     this, SLOT(on_buttonResetViewClicked()));

    //plot control table
    _glassmapmanager->createTable();
    QObject::connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),
                     this, SLOT(on_cellChanged()));


    //---> Dispersion tab
    QObject::connect(ui->pushButton_addNewGlass, SIGNAL(clicked()),
                     this, SLOT(on_buttonAddNewGlassClicked()));
    QObject::connect(ui->pushButton_deleteSelectedGlass, SIGNAL(clicked()),
                     this, SLOT(on_buttonDeleteSelectedGlassClicked()));
    QObject::connect(ui->pushButton_Dispersion_SetAxis, SIGNAL(clicked()),
                     this, SLOT(on_buttonSetAxisClicked()));
    ui->lineEdit_Xmin->setText("300");
    ui->lineEdit_Xmax->setText("1000");
    ui->lineEdit_Ymin->setText("0.9");
    ui->lineEdit_Ymax->setText("2.1");

    QObject::connect(_dispersionPlot, SIGNAL(selectionChangedByUser()),
                     this, SLOT(on_Dispersion_graphSelect_Changed()));

    //---> Transmittance tab
    QObject::connect(ui->pushButton_Transmittance_addGraph, SIGNAL(clicked()),
                     this, SLOT(on_button_Transmittance_AddNewGlassClicked()));
    QObject::connect(ui->pushButton_Transmittance_deleteGraph,SIGNAL(clicked()),
                     this, SLOT(on_button_Transmittance_DeleteGlassClicked()));
    QObject::connect(ui->pushButton_Transmittance_setAxis, SIGNAL(clicked()),
                     this, SLOT(on_button_Transmittance_SetAxisClicked()));
    ui->lineEdit_Transmittance_Xmin->setText("300");
    ui->lineEdit_Transmittance_Xmax->setText("2000");
    ui->lineEdit_Transmittance_Ymin->setText("0.0");
    ui->lineEdit_Transmittance_Ymax->setText("1.0");

    QObject::connect(_transmittancePlot, SIGNAL(selectionChangedByUser()),
                     this, SLOT(on_Transmittance_graphSelect_Changed()));
}

/***********************
 * Menu
 * *********************/

void MainWindow::on_menu_Help_About_Triggered()
{
    AboutDlg *dlg = new AboutDlg(this);
    dlg->exec();
}


void MainWindow::on_menu_File_LoadAGF_Triggered()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
    if(fileDialog.exec()){
        QStringList filePaths = fileDialog.selectedFiles();
        _AGFdir = filePaths.first();

        if(!_glassmapmanager->loadAllAGF(_AGFdir))
        {
            QMessageBox::information(this,tr("File"), tr("AGF load missed"));
            return;
        }

        _glassmapmanager->setCatalogList(_glassmapmanager->getCatalogList());
        _glassmapmanager->createTable();
        _glassmapmanager->createGlassMapList(ui->comboBox_plotType->currentIndex());
        _glassmapmanager->resetAxis(ui->comboBox_plotType->currentIndex());

        _dispersionplotmanager->setCatalogList(_glassmapmanager->getCatalogList());
        _transmittanceplotmanager->setCatalogList(_glassmapmanager->getCatalogList());

        QMessageBox::information(this,tr("Load AGF folder"), tr("AGF loaded"));
    }

}


/*****************
 * GlassMap tab
 * ***************/
void MainWindow::contextMenuRequest(QPoint pos)
{
    if(_glassmapPlot->selectedItems().size() > 0){ //at least one textitem should be selected
        QMenu* contextMenu;
        contextMenu = new QMenu(this);
        contextMenu->setAttribute(Qt::WA_DeleteOnClose);
        contextMenu->addAction("Show Property",this,SLOT(showGlassProperty()));
        contextMenu->popup(_glassmapPlot->mapToGlobal(pos));
    }
}

void MainWindow::showGlassProperty()
{
    if(_glassmapmanager->selectedItemsCount() > 0){
        GlassPropertyDlg *dlg = new GlassPropertyDlg(this);
        dlg->setProperty(_glassmapmanager->getSelectedGlass());
        dlg->show();
    }
}



void MainWindow::on_comboChanged(int index)
{
    switch(index){
    case 0:
        ui->lineEdit_coef0->setText("2.43");
        ui->lineEdit_coef1->setText("-0.028");
        ui->lineEdit_coef2->setText("2.03e-4");
        ui->lineEdit_coef3->setText("2.9e-7");
        break;
    case 1:
        ui->lineEdit_coef0->setText("2.43");
        ui->lineEdit_coef1->setText("-0.028");
        ui->lineEdit_coef2->setText("2.03e-4");
        ui->lineEdit_coef3->setText("2.9e-7");
        break;
    case 2:
        ui->lineEdit_coef0->setText("7.278e-1");
        ui->lineEdit_coef1->setText("-5.656e-3");
        ui->lineEdit_coef2->setText("5.213e-5");
        ui->lineEdit_coef3->setText("-1.665e-7");
    }

    _glassmapmanager->clearGlassMapList();
    _glassmapmanager->createGlassMapList(index);
    _glassmapmanager->createTable();
    _glassmapmanager->updateVisible();
    _glassmapmanager->resetAxis(index);
    _glassmapmanager->replot();
}

void MainWindow::on_cellChanged()
{
    _glassmapmanager->updateVisible();
    _glassmapmanager->replot();
}

void MainWindow::on_checkBoxCurveChanged(bool checkState)
{
    QList<double> coefs;
    coefs.clear();

    coefs.append(ui->lineEdit_coef0->text().toDouble());
    coefs.append(ui->lineEdit_coef1->text().toDouble());
    coefs.append(ui->lineEdit_coef2->text().toDouble());
    coefs.append(ui->lineEdit_coef3->text().toDouble());

    _glassmapmanager->setCurveCoefs(coefs);
    _glassmapmanager->setCurveVisible(checkState);
    _glassmapmanager->replot();
}

void MainWindow::on_lineEdit_textEdited()
{
    QList<double> coefs;

    coefs.append(ui->lineEdit_coef0->text().toDouble());
    coefs.append(ui->lineEdit_coef1->text().toDouble());
    coefs.append(ui->lineEdit_coef2->text().toDouble());
    coefs.append(ui->lineEdit_coef3->text().toDouble());

    _glassmapmanager->setCurveCoefs(coefs);
    _glassmapmanager->replot();
}

void MainWindow::on_buttonResetViewClicked()
{
    _glassmapmanager->resetAxis(ui->comboBox_plotType->currentIndex());
    _glassmapmanager->replot();
}


/*******************
 * Dispersion tab
 * ****************/
void MainWindow::on_buttonAddNewGlassClicked()
{
    if(_dispersionplotmanager->catalogCount() < 1){
        QMessageBox::information(this,tr("File"), tr("No catalog has been loaded"));
        return;
    }else if(_dispersionPlot->graphCount() >= 4){
        QMessageBox::information(this,tr("File"), tr("Up to 5 graphs can be plotted"));
        return;
    }

    QString glassname, supplyername;
    GlassSelectionDlg *dlg = new GlassSelectionDlg(this);

    dlg->setCatalogList(_dispersionplotmanager->getCatalogList());
    dlg->create_comboBox_Supplyers();

    if(dlg->exec() == QDialog::Accepted)
    {
        supplyername = dlg->getSupplyerName();
        glassname = dlg->getGlassName();
        _dispersionplotmanager->addGraph(_dispersionplotmanager->getGlass(glassname,supplyername));
        _dispersionplotmanager->setAllColors();
        _dispersionplotmanager->replot();
    }
}

void MainWindow::on_buttonDeleteSelectedGlassClicked()
{
    if(_dispersionPlot->selectedGraphs().size() > 0){

        _dispersionplotmanager->deleteGraph();
        _dispersionplotmanager->replot();

        //after delete
        if(_dispersionPlot->selectedGraphs().size() > 0){
            Glass *glass;
            glass = _dispersionplotmanager->getGlass(_dispersionPlot->selectedGraphs().first()->name());

            //Belows should be programmatically implemented without Qt Designer
            ui->lineEdit_Dispersion_Formula->setText(glass->dispFormName());
            ui->lineEdit_Dispersion_C0->setText(QString::number(glass->dispCoef(0)));
            ui->lineEdit_Dispersion_C1->setText(QString::number(glass->dispCoef(1)));
            ui->lineEdit_Dispersion_C2->setText(QString::number(glass->dispCoef(2)));
            ui->lineEdit_Dispersion_C3->setText(QString::number(glass->dispCoef(3)));
            ui->lineEdit_Dispersion_C4->setText(QString::number(glass->dispCoef(4)));
            ui->lineEdit_Dispersion_C5->setText(QString::number(glass->dispCoef(5)));
            ui->lineEdit_Dispersion_C6->setText(QString::number(glass->dispCoef(6)));
            ui->lineEdit_Dispersion_C7->setText(QString::number(glass->dispCoef(7)));
            ui->lineEdit_Dispersion_C8->setText(QString::number(glass->dispCoef(8)));
            ui->lineEdit_Dispersion_C9->setText(QString::number(glass->dispCoef(9)));
        }
        else{
            ui->lineEdit_Dispersion_Formula->clear();
            ui->lineEdit_Dispersion_C0->clear();
            ui->lineEdit_Dispersion_C1->clear();
            ui->lineEdit_Dispersion_C2->clear();
            ui->lineEdit_Dispersion_C3->clear();
            ui->lineEdit_Dispersion_C4->clear();
            ui->lineEdit_Dispersion_C5->clear();
            ui->lineEdit_Dispersion_C6->clear();
            ui->lineEdit_Dispersion_C7->clear();
            ui->lineEdit_Dispersion_C8->clear();
            ui->lineEdit_Dispersion_C9->clear();
        }
    }else{
        QMessageBox::information(this,tr("File"),tr("No graph selected"));
        return;
    }
}

void MainWindow::on_buttonSetAxisClicked()
{
    QCPRange xr = QCPRange(ui->lineEdit_Xmin->text().toDouble(),ui->lineEdit_Xmax->text().toDouble());
    QCPRange yr = QCPRange(ui->lineEdit_Ymin->text().toDouble(),ui->lineEdit_Ymax->text().toDouble());

    _dispersionplotmanager->setAxis(xr,yr);
    _dispersionplotmanager->replot();
}

void MainWindow::on_Dispersion_graphSelect_Changed()
{

    if(_dispersionPlot->selectedGraphs().size() > 0){
        Glass *glass;
        glass = _dispersionplotmanager->getGlass(_dispersionPlot->selectedGraphs().first()->name());

        //Belows should be programmatically implemented without Qt Designer
        ui->lineEdit_Dispersion_Formula->setText(glass->dispFormName());
        ui->lineEdit_Dispersion_C0->setText(QString::number(glass->dispCoef(0)));
        ui->lineEdit_Dispersion_C1->setText(QString::number(glass->dispCoef(1)));
        ui->lineEdit_Dispersion_C2->setText(QString::number(glass->dispCoef(2)));
        ui->lineEdit_Dispersion_C3->setText(QString::number(glass->dispCoef(3)));
        ui->lineEdit_Dispersion_C4->setText(QString::number(glass->dispCoef(4)));
        ui->lineEdit_Dispersion_C5->setText(QString::number(glass->dispCoef(5)));
        ui->lineEdit_Dispersion_C6->setText(QString::number(glass->dispCoef(6)));
        ui->lineEdit_Dispersion_C7->setText(QString::number(glass->dispCoef(7)));
        ui->lineEdit_Dispersion_C8->setText(QString::number(glass->dispCoef(8)));
        ui->lineEdit_Dispersion_C9->setText(QString::number(glass->dispCoef(9)));
    }
    else{
        ui->lineEdit_Dispersion_Formula->clear();
        ui->lineEdit_Dispersion_C0->clear();
        ui->lineEdit_Dispersion_C1->clear();
        ui->lineEdit_Dispersion_C2->clear();
        ui->lineEdit_Dispersion_C3->clear();
        ui->lineEdit_Dispersion_C4->clear();
        ui->lineEdit_Dispersion_C5->clear();
        ui->lineEdit_Dispersion_C6->clear();
        ui->lineEdit_Dispersion_C7->clear();
        ui->lineEdit_Dispersion_C8->clear();
        ui->lineEdit_Dispersion_C9->clear();
    }


}


/*****************
 * Transmittance tab
 * ******************/
void MainWindow::on_button_Transmittance_AddNewGlassClicked()
{
    if(_transmittanceplotmanager->catalogCount() < 1){
        QMessageBox::information(this,tr("File"), tr("No catalog has been loaded"));
        return;
    }

    if(_transmittancePlot->graphCount() >= 4){
        QMessageBox::information(this,tr("File"), tr("Up to 5 graphs can be plotted"));
        return;
    }
    QString glassname, supplyername;
    GlassSelectionDlg *dlg = new GlassSelectionDlg(this);

    dlg->setCatalogList(_transmittanceplotmanager->getCatalogList());
    dlg->create_comboBox_Supplyers();

    if(dlg->exec() == QDialog::Accepted)
    {
        supplyername = dlg->getSupplyerName();
        glassname = dlg->getGlassName();
        _transmittanceplotmanager->addGraph(_transmittanceplotmanager->getGlass(glassname,supplyername));
        _transmittanceplotmanager->setAllColors();
        _transmittanceplotmanager->replot();
    }
}

void MainWindow::on_button_Transmittance_DeleteGlassClicked()
{
    if(_transmittancePlot->selectedGraphs().size() > 0){
        _transmittanceplotmanager->deleteGraph();
        _transmittanceplotmanager->replot();
    }else{
        QMessageBox::information(this,tr("File"),tr("No graph selected"));
        return;
    }
}

void MainWindow::on_button_Transmittance_SetAxisClicked()
{
    QCPRange xr = QCPRange(ui->lineEdit_Transmittance_Xmin->text().toDouble(),ui->lineEdit_Transmittance_Xmax->text().toDouble());
    QCPRange yr = QCPRange(ui->lineEdit_Transmittance_Ymin->text().toDouble(),ui->lineEdit_Transmittance_Ymax->text().toDouble());

    _transmittanceplotmanager->setAxis(xr,yr);
    _transmittanceplotmanager->replot();
}

void MainWindow::on_Transmittance_graphSelect_Changed()
{
    if(_transmittancePlot->selectedGraphs().size() > 0){
        qDebug() << _transmittancePlot->selectedGraphs().first()->name();
        Glass *glass;
        glass = _transmittanceplotmanager->getGlass(_transmittancePlot->selectedGraphs().first()->name());
        _transmittanceplotmanager->createTransmittanceDataTable(glass);
    }
    else{
        _transmittanceplotmanager->clearTransmittanceDataTable();
    }
}
