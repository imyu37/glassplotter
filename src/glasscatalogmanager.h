#ifndef GLASSCATALOGMANAGER_H
#define GLASSCATALOGMANAGER_H

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QList>
#include <QDebug>

#include "glass.h"
#include "glasscatalog.h"

class GlassCatalogManager
{
public:
    GlassCatalogManager();
    ~GlassCatalogManager();

    int catalogCount();

    void setCatalogList(QList<GlassCatalog*> gcl);

    QList<GlassCatalog*> getCatalogList();

    GlassCatalog* getCatalog(QString supplyername);
    GlassCatalog* getCatalog(int index);

    Glass* getGlass(QString glassname, QString supplyername = "");

    bool hasCatalog(QString supplyername);
    bool hasGlass(QString glassname);

    bool loadAllAGF(QString AGFdir);

protected:
    QList<GlassCatalog*> _catalogs;

private:

};

#endif // GLASSCATALOGMANAGER_H
