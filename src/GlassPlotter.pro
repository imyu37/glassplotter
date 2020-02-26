QT       += core gui

QT += printsupport


# DEPLOY
#GPdist.path = $$OUT_PWD/$$DESTSUBDIR/GlassPlotter
#GPdist.files = ./GlassPlotter/*
#INSTALLS += GPdist

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdlg.cpp \
    dispersionplotmanager.cpp \
    glass.cpp \
    glasscatalog.cpp \
    glasscatalogmanager.cpp \
    glassmapmanager.cpp \
    glasspropertydlg.cpp \
    glassselectiondlg.cpp \
    main.cpp \
    mainwindow.cpp \
    qcpscatterchart.cpp \
    qcustomplot.cpp \
    spectralline.cpp \
    transmittanceplotmanager.cpp

HEADERS += \
    aboutdlg.h \
    dispersionplotmanager.h \
    glass.h \
    glasscatalog.h \
    glasscatalogmanager.h \
    glassmapmanager.h \
    glasspropertydlg.h \
    glassselectiondlg.h \
    mainwindow.h \
    qcpscatterchart.h \
    qcustomplot.h \
    spectralline.h \
    spline.h \
    transmittanceplotmanager.h

FORMS += \
    aboutdlg.ui \
    glasspropertydlg.ui \
    glassselectiondlg.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
