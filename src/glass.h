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
    /**
      @short Glass data container
      @brief Class to handle glass property data
      @author Hiiragi
      */
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

    class ThermalData
    {
    public:
        QVector<double> coefs; //<D0> <D1> <D2> <E0> <E1> <Ltk>

        double coef(int n){return coefs.at(n);}
        double D0();
        double D1();
        double D2();
        double E0();
        double E1();
        double Ltk();
    };

    double index(double lambdamicron);
    double index(QString spectral);

    QString name() const { return _name;}
    QString supplyer() const { return _supplyer;}

    DispersionData* dispersion(){return _dispersionData;}

    double thermalCoef(int index) const { return _thermalcoefs.at(index);}

    double transmittance(double lambdamicron, double thickness = 25);
    QVector<double> transmittance(QVector<double> x, double thickness = 25);

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

    void computeProperties();

    void setName(QString str){ _name = str;}
    void setSupplyer(QString str){ _supplyer = str;}
    void setStatus(QString str);
    void setStatus(int index);

    void setNd(double value){ _nd = value;}
    void setVd(double value){ _vd = value;}
    void setPgF(double value){_PgF = value;}

    void setdPgF(double value){_dPgF = value;}

    void setDispForm(int n){ _dispersionData->formulaIndex = n;}
    void setDispCoef(int index, double val);

    void setThermalCoef(int index, double val);
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
    double _nd;
    double _ne;   
    double _vd;
    double _ve;   
    double _PgF;

    double _dPgF;

    // LD
    double _lambdaMax;
    double _lambdaMin;

    DispersionData* _dispersionData;

    // TD
    QList<double> _thermalcoefs; //<D0> <D1> <D2> <E0> <E1> <Ltk>

    TransmittanceData* _transmittanceData;
};

#endif // GLASS_H
