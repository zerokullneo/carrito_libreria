//           fecha.cpp
//  vie diciembre 20 01:57:48 2013
//  Copyright  2013  Jose M Barba Gonzalez
//  <user@host>
// fecha.cpp
//
// Copyright (C) 2013 - Jose M Barba Gonzalez
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "fecha.h"

using namespace std;

//CONSTRUCTORES

Fecha::Fecha()
{
	d_ = 1;
	m_ = 1;
	a_ = 1970;
}

//inline Fecha::Fecha(int dia, int mes, int year){ Fecha.d_ = dia; Fecha.m_ = mes; Fecha.a_ = year;}

Fecha::Fecha (int dia, int mes, int year)
{
	if(!dia) d_ = getd_;
	d_ = dia;

	if(!mes) m_ = getm_;
	m_ = mes;

	if(!year) a_ = geta_;
	a_ = year;

	if(comprueba_fecha(d_, m_, a_) != true)
		cout<<"FIncorrecta"<<endl;
}

Fecha::FIncorrecta::FIncorrecta(enum tipo_ t)
{
	tp_ = t;
	porque(tp_);
}
//FIN CONSTRUCTORES

//OPERADORES

Fecha& Fecha::operator +=(int incremento)
{
	this->sumadias(incremento);
	return *this;
}

Fecha& Fecha::operator -=(int decremento)
{
	this->restadias(decremento);
	return *this;
}

Fecha& Fecha::operator ++()
{
        this->d_ ++;
        return *this;
}

Fecha& Fecha::operator --()
{
       this->d_ -=1;
        return *this;
}

Fecha& Fecha::operator =(const Fecha& fec)
{
	if(this != &fec)
	{
            d_ = fec.d_;
            m_ = fec.m_;
            a_ = fec.a_;
	}
	return *this;
}

bool Fecha::operator +(int incremento)
{
	if(incremento > 31)
		return false;

	this->sumadias(incremento);
	return true;
}

bool Fecha::operator -(int decremento)
{
	if(decremento > 31)
		return false;

	this->restadias(decremento);
	return true;
}

bool operator ==(const Fecha& fec1, const Fecha& fec2)
{
	if ((fec1.visualizar_dia () == fec2.visualizar_dia ()) && (fec1.visualizar_mes () == fec2.visualizar_mes ()) && (fec1.visualizar_anyo () == fec2.visualizar_anyo ()))
		return true;
	else
		return false;
}

bool operator <(const Fecha& fec1, const Fecha& fec2)
{
	if ((fec1.visualizar_anyo () < fec2.visualizar_anyo ()) && (fec1.visualizar_mes () < fec2.visualizar_mes ()) && (fec1.visualizar_dia () < fec2.visualizar_dia ()))
	    return true;
	else
	    return false;
}

bool operator >(const Fecha& fec1, const Fecha& fec2)
{
	if ((fec1.visualizar_dia () > fec2.visualizar_dia ()) && (fec1.visualizar_mes () > fec2.visualizar_mes ()) && (fec1.visualizar_anyo () > fec2.visualizar_anyo ()))
	    return true;
	else
	    return false;
}

bool operator <=(const Fecha& fec1, const Fecha& fec2)
{
	if ((fec1.visualizar_anyo () <= fec2.visualizar_anyo ()) && (fec1.visualizar_mes () <= fec2.visualizar_mes ()) && (fec1.visualizar_dia () <= fec2.visualizar_dia ()))
	    return true;
	else
	    return false;
}

bool operator >=(const Fecha& fec1, const Fecha& fec2)
{
	if ((fec1.visualizar_dia () >= fec2.visualizar_dia ()) && (fec1.visualizar_mes () >= fec2.visualizar_mes ()) && (fec1.visualizar_anyo () >= fec2.visualizar_anyo ()))
	    return true;
	else
	    return false;
}

bool operator !=(const Fecha& fec1, const Fecha& fec2)
{
	if ((fec1.visualizar_dia () == fec2.visualizar_dia ()) && (fec1.visualizar_mes () == fec2.visualizar_mes ()) && (fec1.visualizar_anyo () == fec2.visualizar_anyo ()))
	    return false;
	else
	    return true;
}

/*------------------FIN OPERADORES---------------------*/

/*--------------------MODIFICADORAS--------------------*/

Fecha& Fecha::sumadias(int incmt_d)
{
    //for(incmt_d; incmt_d > 0; incmt_d--)
	while(incmt_d > 0)
	{
		if((d_ + incmt_d) > 31)
		{
			m_=m_ + (incmt_d%12);
			d_=(incmt_d - d_)%31;
		}
		incmt_d --;
	}
	return *this;
}

Fecha& Fecha::restadias(int decmt_d)
{
	//for(decmt_d; decmt_d > 0; decmt_d--)
	while(decmt_d > 0)
	{
		if((d_ - decmt_d) < 1)
		{
			m_ = m_ - (decmt_d%12);
			d_ = (decmt_d - d_)%31;
		}
		decmt_d --;
	}
	return *this;
}

Fecha& Fecha::sumames(int incmt_m)
{
    if (incmt_m == 12)
    {
        this->m_ = 1;
        this->a_ ++;
    }
    else
        this->m_ = incmt_m;

    return *(this);
}

Fecha& Fecha::restames(int decmt_m)
{
    if (decmt_m == 1)
    {
        this->m_ = 12;
        this->a_ --;
    }
    else
        this->m_ = decmt_m;

    return *(this);
}

Fecha& Fecha::sumayear(int incmt_a)
{
    this->a_ += incmt_a;
    return *this;
}

Fecha& Fecha::restayear(int decmt_a)
{
    this->a_ -= decmt_a;
    return *this;
}
/*-----------------FIN MODIFICADORAS--------------------*/

/*------------------OBSERVADORAS------------------------*/

void Fecha::observadorPublico() const
{
	tm timeinfo = { 0, 0, 0, d_, m_ - 1, a_ - 1900, 0, 0, -1 };
	mktime(&timeinfo);
	const char* const weekday[7] = {"Lunes","Martes","Miercoles","Jueves","Viernes","Sábado","Domingo"};
	cout << "El día " << d_ << "/" << m_ << "/" << a_ << " fue " << weekday[timeinfo.tm_wday] << endl;
}

void Fecha::visualizar() const
{
    cout << d_ << "/" << m_ << "/" << a_ << endl;
}
/*------------------FIN OBSERVADORAS---------------------*/

bool Fecha::comprueba_fecha(int& dia, int& mes, int& year)
{
    if ((year < 1000) || (year > 2500))
	{
		cout << "año\n";
        throw FIncorrecta(ANYO);//year
	}

    if (mes > 1 && mes < 12)
    switch (mes)
    {
        case 1:
            case 3:
                case 5:
                    case 7:
                        case 8:
                            case 10:
                                case 12:
                                {
                                    if (dia < 1 && dia > 31)
									{
										cout << "dia31\n";
                                        throw FIncorrecta(DIA);//dia
									}
									break;
                                }
        case 4:
            case 6:
                case 9:
                    case 11:
                    {
                        if (dia < 1 && dia > 30)
                        {
							cout << "dia30\n";
                            throw FIncorrecta(DIA);//dia
                        }
						break;
                    }
        case 2:
        {
            if ((year % 4) == 0)
			{
				if (dia < 1 && dia > 29)
				{
					cout << "dia29\n";
					throw FIncorrecta(DIA);//dia
				}
			}
            else
                if (dia < 1 && dia > 28)
                {
					cout << "dia28\n";
                    throw FIncorrecta(DIA);//dia
                }
			break;
        }
		default:
		{
			cout << "defmes\n";
			throw FIncorrecta(MES);//mes
		}
    }
	else
	{
		cout << "mes\n";
		throw FIncorrecta(MES);//mes
	}
	
	return true;
}

ostream& operator << (ostream& os, const Fecha& fec)
{
    os << "Fecha actual: " << fec.visualizar_dia() << "/" << fec.visualizar_mes() << "/" << fec.visualizar_anyo() << endl;
    return os;
}

istream& operator >>(istream& is, Fecha& fec)
{
	int d,m,a;
	char *fecha;
	fecha = strtok("1/1/1970","/");
	d = atoi(fecha);
	m = atoi(fecha);
	a = atoi(fecha);
	printf("Dia %i, mes %i, ano %i.", d, m, a);
	//is = ;
	return is;
}
