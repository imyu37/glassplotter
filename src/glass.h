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

#include "math.h"
#include "spline.h" // c++ cubic spline library, Tino Kluge (ttk448 at gmail.com), https://github.com/ttk592/spline
#include "spectralline.h"

class Glass
{
public:
    Glass();
    ~Glass();

    class DispersionData
    {
    public:
        DispersionData(){
            coefs.clear();
            for(int i = 0;i<10;i++) coefs.append(0.0); //initialize
        };
        ~DispersionData(){
            coefs.clear();
        };

        int formulaIndex;
        QVector<double> coefs;

        double coef(int n) const {
            return coefs.at(n);
        }
        QString formulaName();
    };
    void setDispForm(int n){ _dispersionData->formulaIndex = n;}
    void setDispCoef(int index, double val);
    DispersionData* dispersion(){return _dispersionData;}

    class TransmittanceData
    {
    public:
        TransmittanceData(){};
        ~TransmittanceData(){
            wavelength.clear();
            transmittance.clear();
            thickness.clear();
        }
        QVector<double> wavelength;
        QVector<double> transmittance;
        QVector<double> thickness;

        int size(){
          return wavelength.size();
        }
    };

    double transmittance(double lambdamicron, double thickness = 25);
    QVector<double> transmittance(QVector<double> x, double thickness = 25);

    class ThermalData
    {
    public:
        ThermalData(){
            coefs.clear();
            for(int i = 0;i<6;i++) coefs.append(0.0); //initialize
        }
        QVector<double> coefs; //<D0> <D1> <D2> <E0> <E1> <Ltk>

        double coef(int n){return coefs.at(n);}
        double D0(){ return coefs[0]; };
        double D1(){ return coefs[1]; };
        double D2(){ return coefs[2]; };
        double E0(){ return coefs[3]; };
        double E1(){ return coefs[4]; };
        double Ltk(){ return coefs[5]; };

        bool hasData = true;
    };
    void setThermalCoef(int index, double val);
    double dn_dT(double T, double lambdamicron);
    ThermalData* thermalData(){ return _thermalData; }

    double index(double lambdamicron);
    double index(QString spectral);

    QString name() const { return _name;}
    QString supplyer() const { return _supplyer;}
    QString status() const { return _status;}
    QString MIL() const {return _MIL;}
    double nd() const { return _nd;}
    double ne() const { return _ne;}
    double vd() const { return _vd;}
    double ve() const { return _ve;}
    double PgF() const {return _PgF;}
    double Pxy(QString x, QString y);
    double Pxy_(QString x, QString y);

    double lambdaMin() const {return _lambdaMin;} //micron
    double lambdaMax() const {return _lambdaMax;}

    QString comment() const { return _comment; }

    void computeProperties();

    void setName(QString str){ _name = str;}
    void setSupplyer(QString str){ _supplyer = str;}
    void setMIL(QString str) {_MIL = str;}
    void setStatus(QString str);
    void setStatus(int index);

    void setNd(double value){ _nd = value;}
    void setVd(double value){ _vd = value;}
    void setPgF(double value){_PgF = value;}
    void setdPgF(double value){_dPgF = value;}

    void setComment(QString str){ _comment = str; }

    void setLambdaMin(double value){ _lambdaMin = value;}
    void setLambdaMax(double value){ _lambdaMax = value;}

    void appendTransmittanceData(double lambdamicron, double trans, double thick);


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
    QString _MIL;
    double _nd;
    double _ne;   
    double _vd;
    double _ve;   
    double _PgF;
    double _dPgF;

    QString _comment;

    double _lambdaMax;
    double _lambdaMin;

    DispersionData* _dispersionData;
    TransmittanceData* _transmittanceData;
    ThermalData* _thermalData;
};

#endif // GLASS_H
