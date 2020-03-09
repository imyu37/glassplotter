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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "qcustomplot.h"

#include "glasscatalogmanager.h"
#include "glassmapmanager.h"
#include "dispersionplotmanager.h"
#include "transmittanceplotmanager.h"

#include "glasspropertydlg.h"
#include "glassselectiondlg.h"
#include "aboutdlg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createUI();

private slots:
    void on_cellChanged();
    void on_comboChanged(int index);
    void on_checkBoxCurveChanged(bool checkState);
    void on_lineEdit_textEdited();
    void on_buttonResetViewClicked();
    void on_menu_File_LoadAGF_Triggered();
    void on_menu_Help_About_Triggered();

    //GlassMap tab
    void contextMenuRequest(QPoint pos);
    void showGlassProperty();

    //Dispersion tab
    void on_buttonAddNewGlassClicked();
    void on_buttonDeleteSelectedGlassClicked();
    void on_buttonSetAxisClicked();
    void on_Dispersion_graphSelect_Changed();

    //Transmittance tab
    void on_button_Transmittance_AddNewGlassClicked();
    void on_button_Transmittance_DeleteGlassClicked();
    void on_button_Transmittance_SetAxisClicked();
    void on_Transmittance_graphSelect_Changed();

private:
    Ui::MainWindow *ui;

    QCustomPlot* _glassmapPlot;
    QCustomPlot* _dispersionPlot;
    QCustomPlot* _transmittancePlot;

    GlassMapManager* _glassmapmanager;
    DispersionPlotManager* _dispersionplotmanager;
    TransmittancePlotManager* _transmittanceplotmanager;

    QString _AGFdir;

    static const int ColumnSupplyer = 0;
    static const int ColumnPlot     = 1;
    static const int ColumnLabel    = 2;

};
#endif // MAINWINDOW_H
