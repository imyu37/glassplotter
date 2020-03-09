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

#ifndef GLASSCATALOGMANAGER_H
#define GLASSCATALOGMANAGER_H

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QList>
#include <QDebug>

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
