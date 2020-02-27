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

#include "glasspropertydlg.h"
#include "ui_glasspropertydlg.h"

GlassPropertyDlg::GlassPropertyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlassPropertyDlg)
{
    ui->setupUi(this);

    this->setWindowTitle("Property");
}

GlassPropertyDlg::~GlassPropertyDlg()
{
    delete ui;
}

void GlassPropertyDlg::setProperty(Glass* glass)
{
    ui->lineEdit_Supplyer ->setText(glass->supplyer());
    ui->lineEdit_GlassName->setText(glass->name());
    ui->lineEdit_status->setText(glass->status());
    ui->lineEdit_Nd->setText(QString::number(glass->nd()));
    ui->lineEdit_Vd->setText(QString::number(glass->vd()));

    ui->lineEdit_index_C->setText(QString::number(glass->index("C")));
    ui->lineEdit_index_d->setText(QString::number(glass->index("d")));
    ui->lineEdit_index_e->setText(QString::number(glass->index("e")));
    ui->lineEdit_index_F->setText(QString::number(glass->index("F")));
    ui->lineEdit_index_g->setText(QString::number(glass->index("g")));

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

    ui->lineEdit_D0->setText(QString::number(glass->thermalCoef(0)));
    ui->lineEdit_D1->setText(QString::number(glass->thermalCoef(1)));
    ui->lineEdit_D2->setText(QString::number(glass->thermalCoef(2)));
    ui->lineEdit_E0->setText(QString::number(glass->thermalCoef(3)));
    ui->lineEdit_E1->setText(QString::number(glass->thermalCoef(4)));
    ui->lineEdit_Ltk->setText(QString::number(glass->thermalCoef(5)));
}
