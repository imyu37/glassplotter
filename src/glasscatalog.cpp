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

#include "glasscatalog.h"

GlassCatalog::GlassCatalog()
{
    _glasses.clear();
    _supplyer = "";
}
GlassCatalog::~GlassCatalog()
{
    if(_glasses.size() > 0){
        for(int i = 0; i < _glasses.size(); i++){
            delete _glasses[i];
        }
        _glasses.clear();
    }
    _supplyer = "";
}
void GlassCatalog::clear()
{
    if(_glasses.size() > 0){
        for(int i = 0; i < _glasses.size(); i++){
            delete _glasses[i];
        }
        _glasses.clear();
    }
    _supplyer = "";
}

Glass* GlassCatalog::glass(QString glassname) const
{
    for(int i = 0; i < _glasses.count(); i++)
    {
        if(glassname == _glasses[i]->name()){
            return _glasses[i];
        }
    }
    return nullptr;
}

bool GlassCatalog::hasGlass(QString glassname)
{
    if(_glasses.count() > 0)
    {
        for(int i = 0; i < _glasses.count(); i++)
        {
            if(glassname == _glasses[i]->name()){
                return true;
            }
        }
    }
    return false;
}

bool GlassCatalog::loadAGF(QString AGFpath)
{
    qDebug("Loading : %s", AGFpath.toUtf8().data());

    QFile file(AGFpath);
    if (! file.open(QIODevice::ReadOnly)) {
        qDebug() << "File Open Error";
        return false;
    }

    int linecount = 0;
    QTextStream in(&file);
    QString linetext;
    QStringList lineparts;

    Glass *g;

    _glasses.clear();
    _supplyer = QFileInfo(AGFpath).baseName();

    while (! in.atEnd()) {
        linetext = in.readLine();
        linecount++;

        if(linetext.startsWith("NM")){
            lineparts = linetext.simplified().split(" ");
            g = new Glass;
            _glasses.append(g);
            _glasses.last()->setName(lineparts[1]);
            _glasses.last()->setSupplyer(_supplyer);
            _glasses.last()->setDispForm(lineparts[2].toInt());
            _glasses.last()->setNd(lineparts[4].toDouble());
            _glasses.last()->setVd(lineparts[5].toDouble());
            if(lineparts.size() > 8){
                _glasses.last()->setStatus(lineparts[7].toUInt());
            }
        }
        else if (linetext.startsWith("ED")) {
            lineparts = linetext.simplified().split(" ");
            _glasses.last()->setdPgF(lineparts[4].toDouble());
        }
        else if(linetext.startsWith("CD")){
            lineparts = linetext.simplified().split(" ");
            for(int i = 1;i<lineparts.size();i++){
                _glasses.last()->setDispCoef(i-1,lineparts[i].toDouble());
            }
        }
        else if(linetext.startsWith("TD")){
            lineparts = linetext.simplified().split(" ");
            for(int i = 1;i<lineparts.size();i++){
                _glasses.last()->setThermalCoef(i-1, lineparts[i].toDouble());
            }
        }
        else if(linetext.startsWith("LD")){
            lineparts = linetext.simplified().split(" ");
            _glasses.last()->setLambdaMin(lineparts[1].toDouble());
            _glasses.last()->setLambdaMax(lineparts[2].toDouble());
        }
        else if(linetext.startsWith("IT")){
            lineparts = linetext.simplified().split(" ");
            if(lineparts.size() < 4){
                continue; //eg. NIHON_KESSHO_KOGAKU CaF2
            }
            else{
                _glasses.last()->appendITdata(lineparts[1].toDouble(), lineparts[2].toDouble(), lineparts[3].toDouble());
            }
        }
    }

    file.close();

    for(int i = 0; i<_glasses.size();i++)
    {
        _glasses[i]->computeProperties();
    }

    return true;
}
