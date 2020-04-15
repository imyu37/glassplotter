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


#include "glassdatasheetform.h"
#include "ui_glassdatasheetform.h"

GlassDataSheetForm::GlassDataSheetForm(Glass* glass, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlassDataSheetForm)
{
    ui->setupUi(this);

    m_glass = glass;

    setWindowTitle("DataSheet - " + m_glass->name());

    // set names
    ui->label_GlassName->setText( m_glass->name() );
    ui->label_SupplyerName->setText( m_glass->supplyer() );

    setUpIndicesTab();
    setUpDispersionTab();
}

GlassDataSheetForm::~GlassDataSheetForm()
{
    delete ui;
}

void GlassDataSheetForm::setUpIndicesTab()
{
    QWidget* scrollAreaContents = ui->scrollAreaWidgetContents;
    QGridLayout* gridLayout = new QGridLayout(scrollAreaContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout_Indices"));

    QLabel* label;

    // table header
    label = new QLabel("Spectral", scrollAreaContents);
    gridLayout->addWidget(label, 0, 0, 1, 1);

    label = new QLabel("Wavelength",scrollAreaContents);
    gridLayout->addWidget(label, 0, 1, 1, 1);

    label = new QLabel("Index", scrollAreaContents);
    gridLayout->addWidget(label, 0, 2, 1, 1);

    // list up indices
    QStringList spectralList = SpectralLine::spectralLineList();
    QString spectralLineName;
    double lambdamicron;
    double index;
    for(int i = 1; i < spectralList.size(); i++)
    {
        spectralLineName = spectralList.at(i-1);
        lambdamicron = SpectralLine::wavelength(spectralLineName);
        index = m_glass->index(spectralLineName);

        // Spectral name
        label = new QLabel(scrollAreaContents);
        label -> setText(spectralLineName);
        gridLayout->addWidget(label, i, 0, 1, 1);

        // lambda(nm)
        label = new QLabel(scrollAreaContents);
        label ->setText(QString::number(lambdamicron));
        gridLayout->addWidget(label, i, 1, 1, 1);

        // refractive index
        label = new QLabel(scrollAreaContents);
        label -> setText(QString::number(index));
        gridLayout->addWidget(label, i, 2, 1, 1);
    }
}

void GlassDataSheetForm::setUpDispersionTab()
{
    QWidget* scrollAreaContents = ui->scrollAreaWidgetContents_Dispersion;

    QGridLayout* gridLayout = new QGridLayout(scrollAreaContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout_Dispersion"));

    // formula name
    QLabel *label;
    label = new QLabel(scrollAreaContents);
    label->setText(m_glass->dispersion()->formulaName());
    gridLayout->addWidget(label, 0, 0, 1, 1);

    // list up coefficients
    for(int i = 1; i < m_glass->dispersion()->coefs.size();i++)
    {
        // C0, C1, C2...
        label = new QLabel(scrollAreaContents);
        label->setText("C" + QString::number(i-1));
        gridLayout->addWidget(label, i, 0, 1, 1);

        // coefficient value
        label = new QLabel(scrollAreaContents);
        label->setText(QString::number(m_glass->dispersion()->coefs[i-1]));
        gridLayout->addWidget(label, i, 1, 1, 1);
    }
}
