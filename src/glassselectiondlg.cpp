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

#include "glassselectiondlg.h"
#include "ui_glassselectiondlg.h"

GlassSelectionDlg::GlassSelectionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlassSelectionDlg)
{
    ui->setupUi(this);

    _comboBox_Glass = ui->comboBox_Glass;
    _comboBox_Supplyer = ui->comboBox_Supplyer;

    QObject::connect(_comboBox_Supplyer, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(create_comboBox_Glass(int)));
}

GlassSelectionDlg::~GlassSelectionDlg()
{
    delete ui;
}

QString GlassSelectionDlg::getSupplyerName()
{
    return ui->comboBox_Supplyer->currentText();
}
QString GlassSelectionDlg::getGlassName()
{
    return ui->comboBox_Glass->currentText();
}

void GlassSelectionDlg::create_comboBox_Glass(int catalogindex)
{
    _comboBox_Glass->clear();

    GlassCatalog* catalog;

    catalog = _catalogs[catalogindex];

    for(int i = 0; i < catalog->glassCount(); i++)
    {
        _comboBox_Glass->addItem(catalog->glass(i)->name());
    }
}

void GlassSelectionDlg::create_comboBox_Supplyers()
{
    _comboBox_Supplyer->clear();

    for(int i = 0; i < _catalogs.count(); i++)
    {
        _comboBox_Supplyer->addItem(_catalogs[i]->supplyer());
    }
}

void GlassSelectionDlg::setCatalogList(QList<GlassCatalog*> gcl)
{
    _catalogs = gcl;
}
