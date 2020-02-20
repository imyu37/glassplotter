#include "glasspropertydlg.h"
#include "ui_glasspropertydlg.h"

GlassPropertyDlg::GlassPropertyDlg(Glass *glass, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlassPropertyDlg)
{
    ui->setupUi(this);

    _glass = glass;

    this ->setWindowTitle(_glass->supplyer() + ": " + _glass->name());

    _dispersionPlot = ui->plotWidget_Dispersion;
    _dispersionPlot->setInteraction(QCP::iRangeDrag, false);
    _dispersionPlot->setInteraction(QCP::iRangeZoom, false);

    _transmittancePlot = ui->plotWidget_Transmittance;
    _transmittancePlot->setInteraction(QCP::iRangeDrag, false);
    _transmittancePlot->setInteraction(QCP::iRangeZoom, false);

    createIndicesTable();
    createPartialDispersionTable();
    plotDispersion();
    plotInternalTransmittance();

}

GlassPropertyDlg::~GlassPropertyDlg()
{
    delete ui;
}

void GlassPropertyDlg::createIndicesTable()
{
    SpectralLine sl;
    QStringList indexList = SpectralLine::spectralLineList();
    QTableWidget *table = ui->tableWidget_Indices;
    table->clear();

    // set table format
    table->setColumnCount( 3 );
    table->setRowCount(indexList.count());

    // set header
    table->setHorizontalHeaderLabels( QStringList() << tr("name") << tr("wavelength") << tr("Index" )  );

    int ColIndexName  = 0;
    int ColWavelength = 1;
    int ColIndexValue = 2;

    for(int i = 0; i < indexList.count(); i++){
        table->setItem(i, ColIndexName, new QTableWidgetItem );
        table->item(i, ColIndexName)->setText(tr("n") + indexList[i]);
        table->setItem(i, ColWavelength, new QTableWidgetItem );
        table->item(i, ColWavelength)->setText(QString::number(sl.wavelength(indexList[i])));
        table->setItem(i, ColIndexValue, new QTableWidgetItem );
        table->item(i, ColIndexValue)->setText(QString::number(_glass->index(indexList[i])));
    }
}

void GlassPropertyDlg::createPartialDispersionTable()
{
    // set table format
    QTableWidget *table = ui->tableWidget_PartialDispersion;
    table->setColumnCount(2);
    table->setRowCount(2);
    table->setItem(0, 0, new QTableWidgetItem );
    table->item(0, 0)->setText("other property to be shown");
}


void GlassPropertyDlg::plotDispersion()
{
    QString glassname    = _glass->name();
    QString supplyername = _glass->supplyer();

    QCPTextElement *title = new QCPTextElement(_dispersionPlot, supplyername + ": " + glassname);
    _dispersionPlot->plotLayout()->insertRow(0);
    _dispersionPlot->plotLayout()->addElement(0, 0, title);

    QCPGraph *graph;
    QVector<double> x(101), y(101);
    double lambdamin = _glass->lambdaMin();
    double lambdamax = _glass->lambdaMax();

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        y[i] = _glass->index(x[i]);

        x[i] *= 1000; //micron to nano
    }

    double ymin = *std::min_element(y.constBegin(), y.constEnd());
    double ymax = *std::max_element(y.constBegin(), y.constEnd());

    graph = _dispersionPlot->addGraph();
    graph->setData(x,y);
    graph->setName(_glass->name());
    graph->setVisible(true);
    _dispersionPlot->xAxis->setRange(lambdamin*1000, lambdamax*1000);
    _dispersionPlot->xAxis->setLabel("wavelength(nm)");
    _dispersionPlot->yAxis->setRange(ymin-0.1, ymax+0.1);
    _dispersionPlot->yAxis->setLabel("Index");

    //coefficients
    QString text("Form: " + _glass->dispFormName() + "\n");
    for(int i = 0; i < _glass->dispcoefs().size(); i++)
    {
        text += "C" + QString::number(i) +": " + QString::number(_glass->dispcoefs()[i]) + "\n";
    }

    QCPItemText *textitem = new QCPItemText(_dispersionPlot);
    textitem->position->setType(QCPItemPosition::ptAxisRectRatio);
    textitem->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
    textitem->position->setCoords(1.0, 0.10);
    textitem->setTextAlignment(Qt::AlignLeft);
    textitem->setText(text);

    _dispersionPlot->replot();
}

void GlassPropertyDlg::plotInternalTransmittance()
{
    QString glassname    = _glass->name();
    QString supplyername = _glass->supplyer();

    QCPTextElement *title = new QCPTextElement(_transmittancePlot, supplyername + ": " + glassname);
    _transmittancePlot->plotLayout()->insertRow(0);
    _transmittancePlot->plotLayout()->addElement(0, 0, title);

    QCPGraph *graph;
    QVector<double> x(101), y(101);
    QVector<double> sx,sy;
    double lambdamin = _glass->lambdaMin();
    double lambdamax = _glass->lambdaMax();

    sx = _glass->get_IT_wl();
    sy = _glass->get_IT_tr();

    tk::spline s; //https://github.com/ttk592/spline
    s.set_points(sx.toStdVector(),sy.toStdVector());

    for(int i = 0; i<101; i++)
    {
        x[i] = lambdamin + (lambdamax - lambdamin)*(double)i/100;
        y[i] = s(x[i]);
        x[i] *= 1000; //micron to nano
    }
    double ymin = *std::min_element(y.constBegin(), y.constEnd());
    double ymax = *std::max_element(y.constBegin(), y.constEnd());
    graph = _transmittancePlot->addGraph();
    graph->setData(x,y);
    graph->setName(_glass->name());
    graph->setVisible(true);
    _transmittancePlot->xAxis->setRange(lambdamin*1000, lambdamax*1000);
    _transmittancePlot->yAxis->setRange(ymin-0.1, ymax+0.1);
    _transmittancePlot->replot();
}
