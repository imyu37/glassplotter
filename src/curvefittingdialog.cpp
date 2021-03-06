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
 **  Date    : 2020-5-25                                                    **
 *****************************************************************************/

#include "curvefittingdialog.h"
#include "ui_curvefittingdialog.h"

using namespace Eigen;

CurveFittingDialog::CurveFittingDialog(QList<GlassCatalog*> catalogList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurveFittingDialog)
{
    ui->setupUi(this);

    m_catalogList = catalogList;

    m_listWidget = ui->listWidget_Glasses;

    m_comboBoxOrder = ui->comboBox_Order;
    m_comboBoxOrder->clear();
    for (int i = 1; i <= 3;i++){
        m_comboBoxOrder->addItem(QString::number(i));
    }

    QObject::connect(ui->pushButton_AddGlass, SIGNAL(clicked()), this, SLOT(addGlass()));
    QObject::connect(ui->pushButton_DeleteGlass, SIGNAL(clicked()), this, SLOT(deleteSelectedGlass()));

    m_fittingResult.clear();
    for(int i = 0;i<4;i++) m_fittingResult.append(0);
}

CurveFittingDialog::~CurveFittingDialog()
{
    m_fittingResult.clear();
    m_catalogList.clear();
    m_targetGlassList.clear();

    delete ui;
}

void CurveFittingDialog::updateGlassList()
{
    m_targetGlassList.clear();
    QString glassname, supplyername, tempname;
    Glass* glass;
    for(int i = 0;i < m_listWidget->count() ;i++)
    {
        tempname = m_listWidget->item(i)->text();
        glassname = tempname.split("_")[0];
        supplyername = tempname.split("_")[1];

        for(int j = 0;j < m_catalogList.size();j++)
        {
            if(m_catalogList[j]->supplyer() == supplyername){
                glass = m_catalogList[j]->glass(glassname);
                m_targetGlassList.append(glass);
            }
        }

    }
}

void CurveFittingDialog::addGlass()
{
    GlassSelectionDialog* dlg = new GlassSelectionDialog(m_catalogList,this);
    if(dlg->exec() == QDialog::Accepted)
    {
        QString catalogName = m_catalogList[dlg->getCatalogIndex()]->supplyer();
        QString glassName = dlg->getGlassName();

        m_listWidget->addItem(glassName + "_" + catalogName);
    }
}

void CurveFittingDialog::deleteSelectedGlass()
{
    if(m_listWidget->selectedItems().size() > 0){
        delete m_listWidget->currentItem();
        m_listWidget->update();
    }
}

bool CurveFittingDialog::calculateFitting(int plotType)
{
    //https://en.wikipedia.org/wiki/Polynomial_regression

    updateGlassList();

    int N = m_comboBoxOrder->currentIndex() + 1; //order
    int M = m_targetGlassList.size(); //samples

    if(m_targetGlassList.size() == 0){
        QMessageBox::warning(this,tr("File"), tr("No glass has been selected"));
        return false;
    }else if( M <= N ){
        QMessageBox::warning(this,tr("File"), tr("Too few samples. Curve will seem weird."));
    }

    // initialize results
    m_fittingResult.clear();
    for(int i = 0;i<4;i++) m_fittingResult.append(0);

    // sampling points
    MatrixXd X = MatrixXd::Zero(M, N+1);
    VectorXd y(M);

    for(int i = 0; i<M; i++)
    {
        switch (plotType) {
        case NdVd:

            for(int j = 0; j < N+1; j++){
                X(i,j) = pow(m_targetGlassList[i]->vd(), j);
            }
            y(i) = m_targetGlassList[i]->nd();
            break;

        case NeVe:

            for(int j = 0;j<N+1;j++){
                X(i,j) = pow(m_targetGlassList[i]->ve(), j);
            }
            y(i) = m_targetGlassList[i]->ne();
            break;

        case PgFVd:

            for(int j = 0;j<N+1;j++){
                X(i,j) = pow(m_targetGlassList[i]->vd(), j);
            }
            y(i) = m_targetGlassList[i]->PgF();
            break;

        case PCtVd:

            for(int j = 0;j<N+1;j++){
                X(i,j) = pow(m_targetGlassList[i]->vd(), j);
            }
            y(i) = m_targetGlassList[i]->Pxy("C", "t");
            break;
        }
    }

    MatrixXd A = X.transpose()*X;
    VectorXd b = (X.transpose())*y;
    VectorXd beta = A.bdcSvd(ComputeThinU | ComputeThinV).solve(b);
    //VectorXd beta = (X.transpose()*X).inverse()*(X.transpose())*y;

    for(int k = 0;k<=N;k++)
    {
        m_fittingResult[k] = beta(k);
    }

    return true;
}

QList<double> CurveFittingDialog::fittingResult()
{
    return m_fittingResult;
}
