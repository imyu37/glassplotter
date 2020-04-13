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


#include "glass.h"

Glass::Glass()
{
    _name = "";

    _nd  = 0;
    _ne  = 0;
    _vd  = 0;
    _ve  = 0;
    _PgF = 0;

    // NM

    _status = "No Data";

    // ED 
    _dPgF = 0;


    // TD
    _thermalcoefs.clear();
    for(int i = 0; i < 7; i++){
        _thermalcoefs.append(0.0);
    }

    // LD
    _lambdaMax = 700;
    _lambdaMin = 400;

    _dispersionData = new DispersionData;
    _transmittanceData = new TransmittanceData;
}

Glass::~Glass()
{
    _thermalcoefs.clear();

    delete _dispersionData;
    delete _transmittanceData;
}

double Glass::index(double lambdamicron)
{
    QVector<double> _dispcoefs = _dispersionData->coefs;

    switch(_dispersionData->formulaIndex){
    case 1: //Schott
        return sqrt( _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2) + _dispcoefs[2]*pow(lambdamicron,-2) + _dispcoefs[3]*pow(lambdamicron,-4) + _dispcoefs[4]*pow(lambdamicron,-6) + _dispcoefs[5]*pow(lambdamicron,-8) );
    case 2: //Sellmeier 1
        return sqrt( 1 + _dispcoefs[0]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[1]) + _dispcoefs[2]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[3]) + _dispcoefs[4]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[5]) );
    case 3: //Herzberger
        double L;
        L = 1/(pow(lambdamicron,2)-0.028);
        return _dispcoefs[0] + _dispcoefs[1]*L + _dispcoefs[2]*pow(L,2) + _dispcoefs[3]*pow(lambdamicron,2) + _dispcoefs[4]*pow(lambdamicron,4) + _dispcoefs[5]*pow(lambdamicron,6);
    case 4: //Sellmeier 2
        return sqrt( 1 + _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2)/(pow(lambdamicron,2)-pow(_dispcoefs[2],2)) + _dispcoefs[3]*pow(lambdamicron,2)/(pow(lambdamicron,2)-pow(_dispcoefs[4],2)) );
    case 5: //Conrady
        return ( _dispcoefs[0] + _dispcoefs[1]/lambdamicron + _dispcoefs[2]/pow(lambdamicron,3.5) );
    case 6: //Sellmeier 3
        return sqrt( 1 + _dispcoefs[0]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[1]) + _dispcoefs[2]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[3]) + _dispcoefs[4]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[5]) + _dispcoefs[6]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[7]) );
    case 7: //Handbook Of Optics 1
        return sqrt( _dispcoefs[0] + _dispcoefs[1]/(pow(lambdamicron,2)-_dispcoefs[2]) - _dispcoefs[3]*pow(lambdamicron,2) );
    case 8: //Handbook Of Optics 2
        return sqrt( _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[2]) - _dispcoefs[3]*pow(lambdamicron,2) );
    case 9: //Sellmeier 4
        return sqrt( 1 + _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[2]) + _dispcoefs[3]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[4]) );
    case 10: //Extended 1
        return sqrt( _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2) + _dispcoefs[2]*pow(lambdamicron,-2) + _dispcoefs[3]*pow(lambdamicron,-4) + _dispcoefs[4]*pow(lambdamicron,-6) + _dispcoefs[5]*pow(lambdamicron,-8) + _dispcoefs[6]*pow(lambdamicron,-10) + _dispcoefs[7]*pow(lambdamicron,-12) );
    case 11: //Sellmeier 5
        return sqrt( 1 + _dispcoefs[0]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[1]) + _dispcoefs[2]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[3]) + _dispcoefs[4]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[5]) + _dispcoefs[6]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[7]) + _dispcoefs[8]*pow(lambdamicron,2)/(pow(lambdamicron,2)-_dispcoefs[9]) );
    case 12: //Extended 2
        return sqrt( _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2) + _dispcoefs[2]*pow(lambdamicron,-2) + _dispcoefs[3]*pow(lambdamicron,-4) + _dispcoefs[4]*pow(lambdamicron,-6) + _dispcoefs[5]*pow(lambdamicron,-8) + _dispcoefs[6]*pow(lambdamicron,4) + _dispcoefs[7]*pow(lambdamicron,6) );
    case 13: //Unknown
        if(_supplyer.contains("HIKARI")){  //Hikari https://www.hikari-g.co.jp/products/index2_2.htm
            return sqrt( _dispcoefs[0] + _dispcoefs[1]*pow(lambdamicron,2) + _dispcoefs[2]*pow(lambdamicron,4) + _dispcoefs[3]*pow(lambdamicron,-2) + _dispcoefs[4]*pow(lambdamicron,-4) + _dispcoefs[5]*pow(lambdamicron,-6) + _dispcoefs[6]*pow(lambdamicron,-8) + _dispcoefs[7]*pow(lambdamicron,-10) + _dispcoefs[8]*pow(lambdamicron,-12) );
        }else{
            return 0;
        }
    default:
        return 0;
    }
}

double Glass::index(QString spectral)
{
    double lambdanano = SpectralLine::wavelength(spectral);
    double lambdamicron = lambdanano/1000;

    return index(lambdamicron);
}

double Glass::transmittance(double lambdamicron, double thickness)
{
    QVector<double> sx, sy;

    for(int i = 0; i < _transmittanceData->size(); i++)
    {
        sx.append(_transmittanceData->wavelength.at(i));
        sy.append(_transmittanceData->transmittance.at(i));
    }

    tk::spline s;
    s.set_points(sx.toStdVector(), sy.toStdVector());
    return s(lambdamicron);
}

QVector<double> Glass::transmittance(QVector<double> x)
{
    QVector<double> sx, sy;

    for(int i = 0; i < _transmittanceData->size(); i++)
    {
        sx.append(_transmittanceData->wavelength.at(i));
        sy.append(_transmittanceData->transmittance.at(i));
    }

    tk::spline s;
    s.set_points(sx.toStdVector(), sy.toStdVector());

    QVector<double> y;
    for(int i = 0; i < x.count(); i++)
    {
        y.append(s(x[i]));
    }
    return y;
}


QString Glass::DispersionData::formulaName()
{
    switch(formulaIndex){
    case 1:
        return "Schott";
    case 2:
        return "Sellmeier1";
    case 3:
        return "Herzberger";
    case 4:
        return "Sellmeier2";
    case 5:
        return "Conrady";
    case 6:
        return "Sellmeier3";
    case 7:
        return "Handbook of Optics1";
    case 8:
        return "Handbook of Optics2";
    case 9:
        return "Sellmeier4";
    case 10:
        return "Extended1";
    case 11:
        return "Sellmeier5";
    case 12:
        return "Extended2";
    case 13:
            return "Unknown";
    default:
        return "Unknown";
    }
}


double Glass::Pxy(QString x, QString y)
{
    return (index(x) - index(y)) / ( index("F") - index("C") );
}

double Glass::Pxy_(QString x, QString y)
{
    return (index(x) - index(y)) / ( index("F_") - index("C_") );
}

void Glass::computeProperties()
{
    _ne = index("e");
    _ve = (index("e") - 1)/(index("F_") - index("C_"));
    //_vd = (index("d") - 1)/(index("F") - index("C"));
    _PgF = Pxy("g","F");
}

void Glass::setStatus(QString str)
{
    _status = str;
}

void Glass::setStatus(int index)
{
    switch(index)
    {
    case 1:
        _status = "Preferred";
        break;
    case 2:
        _status = "Obsolete";
        break;
    case 3:
        _status = "Special";
        break;
    case 4:
        _status = "Melt";
        break;
    default:
        _status = "No Data";
    }
}


void Glass::setDispCoef(int index, double val)
{
    if(index < _dispersionData->coefs.count()){
        _dispersionData->coefs[index] = val;
    }
}

void Glass::setThermalCoef(int index, double val)
{
    if(index < _thermalcoefs.count()){
        _thermalcoefs[index] = val;
    }
}

void Glass::appendTransmittanceData(double lambdamicron, double trans, double thick)
{
    _transmittanceData->wavelength.append(lambdamicron);
    _transmittanceData->transmittance.append(trans);
    _transmittanceData->thickness.append(thick);
}


