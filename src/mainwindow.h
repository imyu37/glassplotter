#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
//#include <QtWidgets>

#include "qcustomplot.h"

#include "glasscatalog.h"
#include "glasscatalogmanager.h"
#include "glassmapmanager.h"
#include "dispersionplotmanager.h"
#include "transmittanceplotmanager.h"

#include "glasspropertydlg.h"
#include "glassselectiondlg.h"

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
    void on_cellChanged(int catalogIndex, int PlotOrLabel);
    void on_comboChanged(int index);
    void on_checkBoxCurveChanged(bool checkState);
    void on_lineEdit_textEdited(QString linetext);
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

    //Transmittance tab
    void on_button_Transmittance_AddNewGlassClicked();
    void on_button_Transmittance_DeleteGlassClicked();
    void on_button_Transmittance_SetAxisClicked();

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
