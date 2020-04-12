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


#ifndef GLASS_H
#define GLASS_H

#include <QString>
#include <QList>
#include <QDebug>

#include "math.h"
#include "spline.h"
#include "spectralline.h"

class Glass
{
public:
    Glass();
    ~Glass();

    double index(double lambdamicron);
    double index(QString spectral);

    QString name() const { return _name;}
    QString supplyer() const { return _supplyer;}
    QString dispFormName() const;
    double dispCoef(int index) const { return _dispcoefs.at(index); }

    double thermalCoef(int index) const { return _thermalcoefs.at(index);}

    double transmittance(double lambdamicron, double thickness = 25);
    QVector<double> transmittance(QVector<double> x);

    QString status() const { return _status;}
    double nd() const { return _nd;}
    double ne() const { return _ne;}
    double vd() const { return _vd;}
    double ve() const { return _ve;}
    double PgF() const {return _PgF;}
    double Pxy(QString x, QString y);
    double Pxy_(QString x, QString y);

    double lambdaMin() const {return _lambdaMin;} //micron
    double lambdaMax() const {return _lambdaMax;}

    int getITsize() const {return _ITwavelength.size();}
    double getITdata(int data, int index);

    void computeProperties();

    void setName(QString str){ _name = str;}
    void setSupplyer(QString str){ _supplyer = str;}
    void setStatus(QString str);
    void setStatus(int index);

    void setNd(double value){ _nd = value;}
    void setVd(double value){ _vd = value;}
    void setPgF(double value){_PgF = value;}

    void setdPgF(double value){_dPgF = value;}

    void setDispForm(int formnum){ _dispform = formnum;}
    void setDispCoef(QList<double> coefs);
    void setDispCoef(int index, double val);

    void setThermalCoef(int index, double val);
    void setLambdaMin(double value){ _lambdaMin = value;}
    void setLambdaMax(double value){ _lambdaMax = value;}

    void appendITdata(double lambdamicron, double trans, double thick);


    // dispersion formulas
    /*
    double Schott(double lambdamicron);   
    double Sellmeier1(double lambdamicron);  
    double Sellmeier2(double lambdamicron);   
    double Sellmeier3(double lambdamicron);
    double Sellmeier4(double lambdamicron);
    double Sellmeier5(double lambdamicron);
    double Herzberger(double lambdamicron);
    double HandbookOfOptics1(double lambdamicron);
    double HandbookOfOptics2(double lambdamicron);
    double Extended1(double lambdamicron);
    double Extended2(double lambdamicron);
    */

private:

    //fundamentals
    QString _name;
    QString _supplyer;
    QString _status;
    double _nd;
    double _ne;   
    double _vd;
    double _ve;   
    double _PgF;

    // NM
    int    _dispform;

    // ED    
    double _dPgF;

    // CD
    QList<double> _dispcoefs;

    // TD
    QList<double> _thermalcoefs; //<D0> <D1> <D2> <E0> <E1> <Ltk>

    // OD

    // LD
    double _lambdaMax;
    double _lambdaMin;

    // IT
    QList<double> _ITwavelength;
    QList<double> _ITtransmittance;
    QList<double> _ITthickness;
};

#endif // GLASS_H
