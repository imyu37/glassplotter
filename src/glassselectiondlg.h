#ifndef GLASSSELECTIONDLG_H
#define GLASSSELECTIONDLG_H

#include <QDialog>
#include <QComboBox>
#include "glass.h"
#include "glasscatalog.h"

namespace Ui {
class GlassSelectionDlg;
}

class GlassSelectionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GlassSelectionDlg(QWidget *parent = nullptr);
    ~GlassSelectionDlg();

    QString getSupplyerName();
    QString getGlassName();

    void create_comboBox_Supplyers();

    void setCatalogList(QList<GlassCatalog*> gcl);

private:
    Ui::GlassSelectionDlg *ui;
    QComboBox* _comboBox_Glass;
    QComboBox* _comboBox_Supplyer;

    QList<GlassCatalog*> _catalogs;

private slots:
    void create_comboBox_Glass(int catalogindex);

};

#endif // GLASSSELECTIONDLG_H
