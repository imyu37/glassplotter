/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadAGFfolder;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_GlassMap;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_plotControl;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox_plotType;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_curve;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_coef2;
    QLineEdit *lineEdit_coef0;
    QLabel *label;
    QLineEdit *lineEdit_coef3;
    QLineEdit *lineEdit_coef1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *button_resetView;
    QCustomPlot *widget;
    QWidget *tab_GlassTable;
    QGridLayout *gridLayout_4;
    QComboBox *comboBox_Supplyers;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget_GlassTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(932, 703);
        actionLoadAGFfolder = new QAction(MainWindow);
        actionLoadAGFfolder->setObjectName(QString::fromUtf8("actionLoadAGFfolder"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_GlassMap = new QWidget();
        tab_GlassMap->setObjectName(QString::fromUtf8("tab_GlassMap"));
        gridLayout_3 = new QGridLayout(tab_GlassMap);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(tab_GlassMap);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_plotControl = new QGroupBox(frame);
        groupBox_plotControl->setObjectName(QString::fromUtf8("groupBox_plotControl"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_plotControl->sizePolicy().hasHeightForWidth());
        groupBox_plotControl->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_plotControl);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox_plotType = new QComboBox(groupBox_plotControl);
        comboBox_plotType->setObjectName(QString::fromUtf8("comboBox_plotType"));

        verticalLayout->addWidget(comboBox_plotType);

        tableWidget = new QTableWidget(groupBox_plotControl);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(tableWidget);

        groupBox_curve = new QGroupBox(groupBox_plotControl);
        groupBox_curve->setObjectName(QString::fromUtf8("groupBox_curve"));
        groupBox_curve->setCheckable(true);
        groupBox_curve->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBox_curve);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit_coef2 = new QLineEdit(groupBox_curve);
        lineEdit_coef2->setObjectName(QString::fromUtf8("lineEdit_coef2"));

        gridLayout_2->addWidget(lineEdit_coef2, 2, 1, 1, 1);

        lineEdit_coef0 = new QLineEdit(groupBox_curve);
        lineEdit_coef0->setObjectName(QString::fromUtf8("lineEdit_coef0"));

        gridLayout_2->addWidget(lineEdit_coef0, 0, 1, 1, 1);

        label = new QLabel(groupBox_curve);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_coef3 = new QLineEdit(groupBox_curve);
        lineEdit_coef3->setObjectName(QString::fromUtf8("lineEdit_coef3"));

        gridLayout_2->addWidget(lineEdit_coef3, 3, 1, 1, 1);

        lineEdit_coef1 = new QLineEdit(groupBox_curve);
        lineEdit_coef1->setObjectName(QString::fromUtf8("lineEdit_coef1"));

        gridLayout_2->addWidget(lineEdit_coef1, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_curve);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_curve);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox_curve);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBox_curve);

        button_resetView = new QPushButton(groupBox_plotControl);
        button_resetView->setObjectName(QString::fromUtf8("button_resetView"));

        verticalLayout->addWidget(button_resetView);


        horizontalLayout->addWidget(groupBox_plotControl);

        widget = new QCustomPlot(frame);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        tabWidget->addTab(tab_GlassMap, QString());
        tab_GlassTable = new QWidget();
        tab_GlassTable->setObjectName(QString::fromUtf8("tab_GlassTable"));
        gridLayout_4 = new QGridLayout(tab_GlassTable);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        comboBox_Supplyers = new QComboBox(tab_GlassTable);
        comboBox_Supplyers->setObjectName(QString::fromUtf8("comboBox_Supplyers"));

        gridLayout_4->addWidget(comboBox_Supplyers, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(764, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 1, 1, 1);

        tableWidget_GlassTable = new QTableWidget(tab_GlassTable);
        tableWidget_GlassTable->setObjectName(QString::fromUtf8("tableWidget_GlassTable"));

        gridLayout_4->addWidget(tableWidget_GlassTable, 1, 0, 1, 2);

        tabWidget->addTab(tab_GlassTable, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 932, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionLoadAGFfolder);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoadAGFfolder->setText(QApplication::translate("MainWindow", "Load AGF Folder", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        groupBox_plotControl->setTitle(QApplication::translate("MainWindow", "Plot Control", nullptr));
        groupBox_curve->setTitle(QApplication::translate("MainWindow", "Curve", nullptr));
        label->setText(QApplication::translate("MainWindow", "C0 =", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "C1 =", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "C2 = ", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "C3 =", nullptr));
        button_resetView->setText(QApplication::translate("MainWindow", "Reset View", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_GlassMap), QApplication::translate("MainWindow", "Map", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_GlassTable), QApplication::translate("MainWindow", "Table", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
