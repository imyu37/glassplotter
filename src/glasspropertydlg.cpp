#include "glasspropertydlg.h"
#include "ui_glasspropertydlg.h"

GlassPropertyDlg::GlassPropertyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlassPropertyDlg)
{
    ui->setupUi(this);

    this ->setWindowTitle("Property");
}

GlassPropertyDlg::~GlassPropertyDlg()
{
    delete ui;
}

void GlassPropertyDlg::setProperty(Glass* glass)
{
    _glass = glass;
    ui->lineEdit_Supplyer ->setText(_glass->supplyer());
    ui->lineEdit_GlassName->setText(_glass->name());
    ui->lineEdit_status->setText(_glass->status());
    ui->lineEdit_Nd->setText(QString::number(_glass->nd()));
    ui->lineEdit_Vd->setText(QString::number(_glass->vd()));

    ui->lineEdit_index_C->setText(QString::number(_glass->index("C")));
    ui->lineEdit_index_d->setText(QString::number(_glass->index("d")));
    ui->lineEdit_index_e->setText(QString::number(_glass->index("e")));
    ui->lineEdit_index_F->setText(QString::number(_glass->index("F")));
    ui->lineEdit_index_g->setText(QString::number(_glass->index("g")));

    ui->lineEdit_Dispersion_Formula->setText(_glass->dispFormName());
    ui->lineEdit_Dispersion_C0->setText(QString::number(_glass->dispcoefs()[0]));
    ui->lineEdit_Dispersion_C1->setText(QString::number(_glass->dispcoefs()[1]));
    ui->lineEdit_Dispersion_C2->setText(QString::number(_glass->dispcoefs()[2]));
    ui->lineEdit_Dispersion_C3->setText(QString::number(_glass->dispcoefs()[3]));
    ui->lineEdit_Dispersion_C4->setText(QString::number(_glass->dispcoefs()[4]));
    ui->lineEdit_Dispersion_C5->setText(QString::number(_glass->dispcoefs()[5]));
    ui->lineEdit_Dispersion_C6->setText(QString::number(_glass->dispcoefs()[6]));
    ui->lineEdit_Dispersion_C7->setText(QString::number(_glass->dispcoefs()[7]));
    ui->lineEdit_Dispersion_C8->setText(QString::number(_glass->dispcoefs()[8]));
    ui->lineEdit_Dispersion_C9->setText(QString::number(_glass->dispcoefs()[9]));

    ui->lineEdit_D0->setText(QString::number(_glass->thermalCoefs()[0]));
    ui->lineEdit_D1->setText(QString::number(_glass->thermalCoefs()[1]));
    ui->lineEdit_D2->setText(QString::number(_glass->thermalCoefs()[2]));
    ui->lineEdit_E0->setText(QString::number(_glass->thermalCoefs()[3]));
    ui->lineEdit_E1->setText(QString::number(_glass->thermalCoefs()[4]));
    ui->lineEdit_Ltk->setText(QString::number(_glass->thermalCoefs()[5]));

}
