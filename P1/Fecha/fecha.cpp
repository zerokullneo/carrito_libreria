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
	defecto_();
	d_ = getd_;
	m_ = getm_;
	a_ = geta_;
}

//inline Fecha::Fecha(int dia, int mes, int year){ Fecha.d_ = dia; Fecha.m_ = mes; Fecha.a_ = year;}

Fecha::Fecha(int dia, int mes, int year)
{
	defecto_();
	if(!dia || dia == 0) d_ = getd_;
	else d_ = dia;

	if(!mes || mes == 0) m_ = getm_;
	else m_ = mes;

	if(!year || year == 0) a_ = geta_;
	else a_ = year;

	comprueba_fecha(d_, m_, a_);
}

Fecha::Fecha(int dia, int mes)
{
	defecto_();

	if(!dia || dia == 0) d_ = getd_;
	else d_ = dia;

	if(!mes || mes == 0) m_ = getm_;
	else m_ = mes;

	a_ = geta_;

	comprueba_fecha(d_, m_, a_);
}

Fecha::Fecha(int dia)
{
	defecto_();

	if(!dia || dia == 0) d_ = getd_;
	else d_ = dia;

	m_ = getm_;
	a_ = geta_;

	comprueba_fecha(d_, m_, a_);
}

//Constructor de conversión de Cadena a Fecha.
Fecha::Fecha(char* string_fecha)
{
	char *fecha;
	fecha = strtok(string_fecha,"/-");
	d_ = atoi(fecha);
	fecha = strtok(NULL, "/-");
	m_ = atoi(fecha);
	fecha = strtok(NULL, "/-");
	a_ = atoi(fecha);

	comprueba_fecha(d_, m_, a_);
}

Fecha::Invalida::Invalida(const char* t)
{
	tp_ = t;
	cerr << por_que(tp_);
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
	this->sumadias(1);
	return *this;
}

Fecha Fecha::operator ++(int)
{
	this->sumadias(1);
	return *this;
}

Fecha& Fecha::operator --()
{
	this->restadias(1);
	return *this;
}

Fecha Fecha::operator --(int)
{
	this->restadias(1);
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
		switch(d_ + incmt_d)
		{
			case 32:
			{
				if(m_ + (incmt_d % 12) > 12)
				{
					sumayear(1);
					sumames(1);
				}
				else
					m_ = m_ + (incmt_d % 12);
				d_ = (d_ + incmt_d) % 31;
				break;
			}
			case 31:
			{
				if(m_ + (incmt_d % 12) > 12)
				{	
					sumayear(1);
					sumames(1);
				}
				else
					m_ = m_ + (incmt_d % 12);
				d_ = (d_ + incmt_d) % 30;
				break;
			}
			case 30:
			{
				if(m_ + (incmt_d % 12) > 12)
				{	
					sumayear(1);
					sumames(1);
				}
				else
					m_ = m_ + (incmt_d % 12);
				d_ = (d_ + incmt_d) % 29;
				break;
			}
			case 29:
			{
				if(m_ + (incmt_d % 12) > 12)
				{	
					sumayear(1);
					sumames(1);
				}
				else
					m_ = m_ + (incmt_d % 12);
				d_ = (d_ + incmt_d) % 28;
				break;
			}
			default:
			{
				d_ += 1;
				break;
			}
		}
		incmt_d --;
	}
	return *this;
}

Fecha& Fecha::restadias(int decmt_d)
{
	while(decmt_d > 0)
	{
		if((d_ - decmt_d) < 1)
		{
			if(m_ - (decmt_d % 12) < 1)
			{
				restayear(1);
				restames(1);
			}

			else m_ = m_ - (decmt_d % 12);

			switch(m_)
			{
				case 1:case 3:case 5:case 7:case 8:case 10:case 12:
				{
					d_ = 31;
					break;
				}
				case 4:case 6:case 9:case 11:
				{
					d_ = 30;
					break;
				}
				case 2:
				{
					if ((a_ % 4) == 0) d_ = 29;
					else d_ = 28;
					break;
				}
			}

		//d_ = d_ % 31;
		}
		else
			d_ -= 1;

		decmt_d--;
	}
	return *this;
}

Fecha& Fecha::sumames(int incmt_m)
{
    if (incmt_m == 12)
    {
        this->m_ = 1;
       // this->a_ ++;
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
        //this->a_ --;
    }
    else
        this->m_ = decmt_m;

    return *(this);
}

Fecha& Fecha::sumayear(int incmt_a)
{
    this->a_ = a_ + incmt_a;
    return *this;
}

Fecha& Fecha::restayear(int decmt_a)
{
    this->a_ = a_ - decmt_a;
    return *this;
}
/*-----------------FIN MODIFICADORAS--------------------*/

/*------------------OBSERVADORAS------------------------*/

ostream& Fecha::observadorPublico() const
{
	tm timeinfo = { 0, 0, 0, d_, m_ - 1, a_ - 1900, 0, 0, -1 };
	mktime(&timeinfo);
	const char* const weekday[7] = {"Lunes","Martes","Miercoles","Jueves","Viernes","Sábado","Domingo"};
	const char* const month[12] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
	return cout << "Día " << weekday[timeinfo.tm_wday] << " " << d_ << " de " << month[timeinfo.tm_mon] << " del " << a_ << "." << endl;
}

void Fecha::visualizar() const
{
   if(d_ > 0 && d_ < 10) cout << "0"; cout << d_ << "/";if(m_ > 0 && m_ < 10) cout << "0"; cout << m_ << "/" << a_ << endl;
}
/*------------------FIN OBSERVADORAS---------------------*/

bool Fecha::comprueba_fecha(int& dia, int& mes, int& year)
{
    if ((year < YEAR_MINIMO) || (year > YEAR_MAXIMO))
	{
        throw Invalida("Año Incorrecto\n");//year
	}

    if (mes > 0 && mes < 13)
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
                                    if (dia < 1 || dia > 31)
									{
                                        throw Invalida("dia31\n");//dia
									}
									break;
                                }
        case 4:
            case 6:
                case 9:
                    case 11:
                    {
                        if (dia < 1 || dia > 30)
                        {
                            throw Invalida("dia30");//dia
						}
						break;
                    }
        case 2:
        {
            if ((year % 4) == 0)
			{
				if (dia < 1 || dia > 29)
				{
					throw Invalida("dia29\n");//dia
				}
			}
            else
                if (dia < 0 || dia > 28)
                {
                    throw Invalida("dia28\n");//dia
                }
			break;
        }
		default:
		{
			throw Invalida("defmes\n");//mes
		}
    }
	else
	{
		throw Invalida("mes\n");//mes
	}
	
	return true;
}

ostream& operator <<(ostream& os, const Fecha& fec)
{
	
    os << "Fecha etiquetada: ";
		if(fec.visualizar_dia() > 0 && fec.visualizar_dia() < 10) os << "0";
	os << fec.visualizar_dia() << "/";
		if(fec.visualizar_mes() > 0 && fec.visualizar_mes() < 10) os << "0";
	os << fec.visualizar_mes() << "/" << fec.visualizar_anyo() << endl;
    return os;
}

istream& operator >>(istream& is, Fecha& fec)
{
	char fc[21];
	is.width(21);
	is >> fc;
	fec = Fecha(fc);
	return is;
}