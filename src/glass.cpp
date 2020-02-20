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
    _dispform = 1;

    // ED 
    _dPgF = 0;

    // CD
    _dispcoefs.clear();
    for(int i = 0;i <10; i++){
        _dispcoefs.append(0.0);
    }

    // TD
    _thermaldata.clear();

    // OD


    // LD
    _lambdaMax = 700;
    _lambdaMin = 400;

    // IT
    _int_trans.clear();

}

Glass::~Glass()
{
    _dispcoefs.clear();
    _thermaldata.clear();
    _int_trans.clear();
}

double Glass::index(double lambdamicron)
{
    switch(_dispform){
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
    if(spectral == "t"){
        return index(SpectralLine::t/1000);
    }
    else if(spectral == "s"){
        return index(SpectralLine::s/1000);
    }
    else if(spectral == "r"){
        return index(SpectralLine::r/1000);
    }
    else if(spectral == "C"){
        return index(SpectralLine::C/1000);
    }
    else if(spectral == "C_"){
        return index(SpectralLine::C_/1000);
    }
    else if(spectral == "D"){
        return index(SpectralLine::D/1000);
    }
    else if(spectral == "d"){
        return index(SpectralLine::d/1000);
    }
    else if(spectral == "e"){
        return index(SpectralLine::e/1000);
    }
    else if(spectral == "F"){
        return index(SpectralLine::F/1000);
    }
    else if(spectral == "F_"){
        return index(SpectralLine::F_/1000);
    }
    else if(spectral == "g"){
        return index(SpectralLine::g/1000);
    }
    else if(spectral == "h"){
        return index(SpectralLine::h/1000);
    }
    else if(spectral == "i"){
        return index(SpectralLine::i/1000);
    }
    else{
        return 0;
    }
}

QString Glass::dispFormName()
{
    switch(_dispform){
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
        if(_supplyer.contains("HIKARI")){
            return "HIKARI";
        }else{
            return "Unknown";
        }
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

QVector<double> Glass::get_IT_wl()
{
    QVector<double> wlvec;

    for(int i = 0; i < _int_trans.size(); i++)
    {
        wlvec.append(_int_trans[i].first);
    }
    return wlvec;
}

QVector<double> Glass::get_IT_tr()
{
    QVector<double> trvec;

    for(int i = 0; i < _int_trans.size(); i++)
    {
        trvec.append(_int_trans[i].second);
    }
    return trvec;
}


void Glass::computeProperties()
{
    _ne = index("e");
    _ve = (index("e") - 1)/(index("F_") - index("C_"));
    _vd = (index("d") - 1)/(index("F") - index("C"));
    _PgF = Pxy("g","F");
}

void Glass::setDispCoef(QList<double> coefs)
{
    for(int i = 0;i < _dispcoefs.size(); i++)
    {
        if(i < coefs.size()){
            _dispcoefs[i] = coefs[i];
        }else{
            _dispcoefs[i] = 0.0;
        }
    }
}
void Glass::appendIntTrans(double lambdamicron, double trans)
{
    QPair<double, double> p;
    p.first  = lambdamicron;
    p.second = trans;
    _int_trans.append(p);
}

