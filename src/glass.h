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

/**
  * Glass property container class
  */




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

    /**
     * @brief Inner class to contain dispersion data
     */
    class DispersionData
    {
    public:
        /**
         * @brief DispersionData
         */
        DispersionData(){
            coefs.clear();
            for(int i = 0;i<12;i++) coefs.append(0.0); //initialize
        };
        ~DispersionData(){
            coefs.clear();
        };

        /**
         * @brief index value to express dispersion formula
         */
        int formulaIndex;

        /**
         * @brief coefficients of dispersion formula
         */
        QVector<double> coefs;

        /**
         * @brief get coefficient
         * @param n coefficient index number
         * @return coefficient value
         */
        double coef(int n) const {
            return coefs[n];
        }

        /**
         * @brief dispersion formula name
         * @return
         */
        QString formulaName();
    };

    /**
     * @brief set dispersion formula index
     * @param n index
     */
    void setDispForm(int n){ _dispersionData->formulaIndex = n;}

    /**
     * @brief set dispersion coefficient value
     * @param n coefficient index
     * @param val value
     */
    void setDispCoef(int index, double val);

    /**
     * @brief Dispersion class instance
     */
    DispersionData* dispersion(){return _dispersionData;}


    /**
     * @brief The inner class to contain Transmittance Data
     */
    class TransmittanceData
    {
    public:
        TransmittanceData(){};
        ~TransmittanceData(){
            wavelength.clear();
            transmittance.clear();
            thickness.clear();
        }

        /**
         * @brief wavelengths contained in IT line of AGF
         */
        QVector<double> wavelength;

        /**
         * @brief transmittance data contained in IT line of AGF
         */
        QVector<double> transmittance;

        /**
         * @brief thickness data contained in IT line of AGF
         */
        QVector<double> thickness;

        /**
         * @brief count transmittance data
         * @return count
         */
        int size(){
          return wavelength.size();
        }
    };

    /**
     * @brief get internal transmittance
     * @param lambdamicron wavelength in micron
     * @param thickness
     * @return internal transmittance
     */
    double transmittance(double lambdamicron, double thickness = 25);

    /**
     * @brief get internal transmittance expressed as vector
     * @param x wavelength vector
     * @param thickness
     * @return internal transmittance
     */
    QVector<double> transmittance(QVector<double> x, double thickness = 25);


    /**
     * @brief The inner class to contain Thermal Data
     */
    class ThermalData
    {
    public:
        ThermalData(){
            coefs.clear();
            for(int i = 0;i<6;i++) coefs.append(0.0); //initialize
        }


        /**
         * @brief coefficients of dn/dT
         */
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

    /**
     * @brief get refractive index at the wavelength
     * @param lambdamicron wavelength in micron
     * @return refractive index
     */
    double index(double lambdamicron);

    /**
     * @brief get refractive index at the wavelength
     * @param spectral Fraunhofer line name
     * @return refractive index
     */
    double index(QString spectral);

    /**
     * @brief glass name
     */
    QString name() const { return _name;}

    /**
     * @brief supplier name
     */
    QString supplyer() const { return _supplyer;}

    /**
     * @brief status
     * @return
     */
    QString status() const { return _status;}

    /**
     * @brief MIL code
     * @return
     */
    QString MIL() const {return _MIL;}

    /**
     * @brief nd
     * @return
     */
    double nd() const { return _nd;}

    /**
     * @brief ne
     * @return
     */
    double ne() const { return _ne;}

    /**
     * @brief Abbe value at d line
     * @return
     */
    double vd() const { return _vd;}

    /**
     * @brief Abbe value at e line
     * @return
     */
    double ve() const { return _ve;}

    /**
     * @brief PgF
     * @return
     */
    double PgF() const {return _PgF;}

    /**
     * @brief Pxy: partial dispersion between x and y
     * @param x Fraunhofer line
     * @param y Fraunhofer line
     * @return
     */
    double Pxy(QString x, QString y);
    double Pxy_(QString x, QString y);

    /**
     * @brief minimum wavelength in micron
     * @return
     */
    double lambdaMin() const {return _lambdaMin;}

    /**
     * @brief maximum wavelength in micron
     * @return
     */
    double lambdaMax() const {return _lambdaMax;}


    /**
     * @brief individual glass comment
     * @return
     */
    QString comment() const { return _comment; }


    /**
     * @brief compute properties
     */
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


    /**
     * @brief append Transmittance Data expressed in IT line
     * @param lambdamicron wavelength in micron
     * @param trans transmittance
     * @param thick thickness
     */
    void appendTransmittanceData(double lambdamicron, double trans, double thick);


    // dispersion formulas
    /*
    double Schott(double lambdamicron, QList<double> c)
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
