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

    QString spectralLineName;
    double lambdamicron;
    double index;

    QLabel* label_spectralName;
    QLabel* label_spectralLambda;
    QLabel* label_index;

    QGridLayout* gridLayout = new QGridLayout(scrollAreaContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout_Indices"));

    QStringList spectralList = SpectralLine::spectralLineList();

    // table header
    label_spectralName = new QLabel;
    label_spectralName -> setText("Spectral");
    gridLayout->addWidget(label_spectralName, 0, 0, 1, 1);

    label_spectralLambda = new QLabel(scrollAreaContents);
    label_spectralLambda ->setText("WaveLength");
    gridLayout->addWidget(label_spectralLambda, 0, 1, 1, 1);

    label_index = new QLabel(scrollAreaContents);
    label_index->setText("Index");
    gridLayout->addWidget(label_index, 0, 2, 1, 1);

    for(int i = 1; i < spectralList.size(); i++)
    {
        spectralLineName = spectralList.at(i-1);
        lambdamicron = SpectralLine::wavelength(spectralList.at(i-1));
        index = m_glass->index(spectralLineName);

        label_spectralName = new QLabel(scrollAreaContents);
        label_spectralName -> setObjectName("label_spectral_" + spectralLineName);
        label_spectralName -> setText(spectralLineName);
        gridLayout->addWidget(label_spectralName, i, 0, 1, 1);

        label_spectralLambda = new QLabel(scrollAreaContents);
        label_spectralLambda -> setObjectName("label_lambda_" + spectralLineName);
        label_spectralLambda ->setText(QString::number(lambdamicron));
        gridLayout->addWidget(label_spectralLambda, i, 1, 1, 1);

        label_index = new QLabel(scrollAreaContents);
        label_index -> setObjectName("label_index_" + spectralLineName);
        label_index -> setText(QString::number(index));
        gridLayout->addWidget(label_index, i, 2, 1, 1);
    }

}

void GlassDataSheetForm::setUpDispersionTab()
{
    QWidget* scrollAreaContents = ui->scrollAreaWidgetContents_Dispersion;
    QLabel *label_formulaName;
    QLabel *label_coefName;
    QLabel *label_coefValue;

    QGridLayout* gridLayout = new QGridLayout(scrollAreaContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout_Dispersion"));

    label_formulaName = new QLabel(scrollAreaContents);
    label_formulaName->setText(m_glass->dispersion()->formulaName());
    gridLayout->addWidget(label_formulaName, 0, 0, 1, 1);

    for(int i = 1; i < m_glass->dispersion()->coefs.size();i++){
        label_coefName = new QLabel(scrollAreaContents);
        label_coefName->setText("C" + QString::number(i-1));
        gridLayout->addWidget(label_coefName, i, 0, 1, 1);

        label_coefValue = new QLabel(scrollAreaContents);
        label_coefValue->setText(QString::number(m_glass->dispersion()->coefs[i-1]));
        gridLayout->addWidget(label_coefValue, i, 1, 1, 1);
    }
}
