/********************************************************************************
** Form generated from reading UI file 'glasspropertydlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLASSPROPERTYDLG_H
#define UI_GLASSPROPERTYDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GlassPropertyDlg
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_Property;
    QWidget *tab_Dispersion;
    QGridLayout *gridLayout_2;
    QCustomPlot *plotWidget;

    void setupUi(QDialog *GlassPropertyDlg)
    {
        if (GlassPropertyDlg->objectName().isEmpty())
            GlassPropertyDlg->setObjectName(QString::fromUtf8("GlassPropertyDlg"));
        GlassPropertyDlg->resize(695, 521);
        gridLayout = new QGridLayout(GlassPropertyDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(GlassPropertyDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_Property = new QWidget();
        tab_Property->setObjectName(QString::fromUtf8("tab_Property"));
        tabWidget->addTab(tab_Property, QString());
        tab_Dispersion = new QWidget();
        tab_Dispersion->setObjectName(QString::fromUtf8("tab_Dispersion"));
        gridLayout_2 = new QGridLayout(tab_Dispersion);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        plotWidget = new QCustomPlot(tab_Dispersion);
        plotWidget->setObjectName(QString::fromUtf8("plotWidget"));

        gridLayout_2->addWidget(plotWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab_Dispersion, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(GlassPropertyDlg);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GlassPropertyDlg);
    } // setupUi

    void retranslateUi(QDialog *GlassPropertyDlg)
    {
        GlassPropertyDlg->setWindowTitle(QApplication::translate("GlassPropertyDlg", "Dialog", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Property), QApplication::translate("GlassPropertyDlg", "Property", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Dispersion), QApplication::translate("GlassPropertyDlg", "Dispersion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GlassPropertyDlg: public Ui_GlassPropertyDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLASSPROPERTYDLG_H
