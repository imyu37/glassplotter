#include "glasscatalogmanager.h"

GlassCatalogManager::GlassCatalogManager()
{
    _catalogs.clear();
}
GlassCatalogManager::~GlassCatalogManager()
{
    if(_catalogs.size() > 0) _catalogs.clear();
}
int GlassCatalogManager::catalogCount()
{
    return _catalogs.count();
}
void GlassCatalogManager::setCatalogList(QList<GlassCatalog *> gcl)
{
    _catalogs = gcl;
}
QList<GlassCatalog*> GlassCatalogManager::getCatalogList()
{
    return _catalogs;
}
GlassCatalog* GlassCatalogManager::getCatalog(QString supplyername)
{
    for(int i = 0; i < _catalogs.count(); i++)
    {
        if(_catalogs[i]->supplyer() == supplyername)
        {
            return _catalogs[i];
        }
    }
    return nullptr;
}
GlassCatalog* GlassCatalogManager::getCatalog(int index)
{
    if(index < _catalogs.count()){
        return _catalogs[index];
    }else{
        return nullptr;
    }
}
Glass* GlassCatalogManager::getGlass(QString glassname, QString supplyername)
{
    if(supplyername == "")
    {
        for(int i = 0; i < _catalogs.count(); i++)
        {
            if(_catalogs[i]->hasGlass(glassname)){
                return _catalogs[i]->glass(glassname);
            }
        }
    }else{
        return getCatalog(supplyername)->glass(glassname);
    }
    return NULL;
}
bool GlassCatalogManager::hasCatalog(QString supplyername)
{
    for(int i = 0; i < _catalogs.count(); i++)
    {
        if(supplyername == _catalogs[i]->supplyer()){
            return true;
        }
    }
    return false;
}
bool GlassCatalogManager::hasGlass(QString glassname)
{
    for(int i = 0; i < _catalogs.count(); i++)
    {
        for(int j = 0; j < _catalogs.at(i)->glassCount(); j++)
        {
            if(glassname == _catalogs.at(i)->glass(j)->name())
            {
                return true;
            }
        }
    }
    return false;
}
bool GlassCatalogManager::loadAllAGF(QString AGFdir)
{
    GlassCatalog *catalog;

    _catalogs.clear();

    QStringList nameFilters;
    nameFilters.append("*.AGF");

    QDir dir(AGFdir);
    QStringList filelist = dir.entryList(nameFilters, QDir::Files);
    if(filelist.empty())
    {
        qDebug() << "AGF dir is empty";
        return false;
    }

    QString fullpath;
    for (int i = 0; i < filelist.size(); i++) {
        fullpath = dir.filePath(filelist[i]);
        catalog = new GlassCatalog;
        if(!catalog->loadAGF(fullpath))
        {
            //delete catalog;
            return false;
        }else{
            _catalogs.append(catalog);
        }
    }
    return true;
}
