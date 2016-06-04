// fecha.cpp
//
// mie, mar 16 2016 18:55:46
// Copyright 2016 Jose M Barba Gonzalez
// <user@host>
//
// fecha.cpp
//
// Copyright (C) 2016 - Jose M Barba Gonzalez
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

#include "fecha.hpp"
#include <string.h>

using namespace std;



bool bisiesto(int a)
{
	return !(a%4) && ((a%100) || !(a%400));
}

//CONSTRUCTORES
Fecha::Fecha(int dia, int mes, int anyo):d_(dia),m_(mes),a_(anyo)
{
	if(!dia or !mes or !anyo)
	{
		get_fecha_ = time(0);
		info_fecha_ = localtime(&get_fecha_);
	}

	if(!d_ or dia == 0)
		this->default_d_();

	if(!mes or mes == 0)
		this->default_m_();

	if(!anyo or anyo == 0)
		this->default_a_();

	comprueba_fecha(d_, m_, a_);
}

//Constructor de conversión de Cadena a Fecha.
Fecha::Fecha(const char* string_fecha)
{
	if(sscanf(string_fecha,"%d/%d/%d", &d_, &m_, &a_))
	{
		if(!d_ or !m_ or !a_)
		{
			get_fecha_ = time(0);
			info_fecha_ = localtime(&get_fecha_);
		}

		if(!a_ or a_ == 0)
			this->default_a_();
		if(!m_ or m_ == 0)
			this->default_m_();
		if(!d_ or d_ == 0)
			this->default_d_();

		comprueba_fecha(d_, m_, a_);
	}
	else
		throw Fecha::Invalida("Entrada Incorrecta en Constructor de cadena .");
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

Fecha& Fecha::operator ++()//postincremento
{
	this->sumadias(1);
	return *this;
}

Fecha Fecha::operator ++(int)//preincremento
{
	Fecha f(*this);
	this->sumadias(1);
	return f;
}

Fecha& Fecha::operator --()//postdecremento
{
	this->restadias(1);
	return *this;
}

Fecha Fecha::operator --(int)//predecremento
{
	Fecha f(*this);
	this->restadias(1);
	return f;
}

bool Fecha::operator +(int incremento)
{
	if(incremento > 31)
	{
		int fec[3] = {((incremento % 365)%30),((incremento % 365)/30),(incremento / 365)};

		if(fec[2] > 0 )
		{
			cout << "año - " << fec[2] << endl;
			this->sumayear(fec[2]);
		}
		if(fec[1] > 0 )
		{
			cout << "mes - " << fec[1] << endl;
			this->sumames(fec[1]);
		}
		if(fec[0] > 0 )
		{
			cout << "dia - " << fec[0] << endl;
			this->sumadias(fec[0]);
		}
		return true;
	}

    else
	{
		this->sumadias(incremento);
		return true;
	}
}

bool Fecha::operator -(int decremento)
{
	if(decremento > 31)
		return false;

	this->restadias(decremento);
	return true;
}

/*------------------FIN OPERADORES---------------------*/

/*--------------------MODIFICADORAS--------------------*/
Fecha& Fecha::sumadias(int incmt_d)
{
	int dm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	this->d_ += incmt_d;
	if(bisiesto(this->a_)) dm[1] = 29; else dm[1] = 28;

	while(this->d_ > dm[this->m_-1])
	{
		this->d_ -= dm[this->m_-1];
		this->m_ += 1;
		if(this->m_ > 12)
		{
			this->m_ = 1;
			this->a_+=1;
			if(bisiesto(this->a_)) dm[1] = 29; else dm[1] = 28;
		}
	}

	if(a_ >	AnnoMaximo)
		throw Invalida("Año Incorrecto.");

	return *this;
}

Fecha& Fecha::restadias(int decmt_d)
{
	int dm[] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},sum,i;

	this->d_ -= decmt_d;
	if(bisiesto(this->a_)) dm[1] = 29; else dm[1] = 28;

	sum = this->d_;

	for(((dm[this->m_-1] < 1) ? i = dm[12] :(i = dm[this->m_-1])); (sum < i || sum < dm[this->m_-1])&& (sum <= (dm[this->m_]));)
	{
		if(sum == 0)
		{
			this->m_= this->m_ - 1;
			if(this->m_ < 1)
			{
				this->m_ = 12;
				this->a_-=1;
				if(bisiesto(this->a_)) dm[1] = 29; else dm[1] = 28;
			}
			this->d_ = this->d_ + dm[this->m_];
			sum = dm[this->m_];
		}
		else
		{
			this->m_ = this->m_ - 1;

			if(this->m_ < 1)
			{
				this->m_ = 12;
				this->a_-=1;
				if(bisiesto(this->a_)) dm[1] = 29; else dm[1] = 28;
			}
			if((sum = this->d_ + dm[this->m_]) < 32)
			{
				this->d_ = this->d_ + dm[this->m_];
				sum = this->d_ + dm[this->m_];
			}
			else
				this->m_ = this->m_ + 1;
		}
	}

	if(a_ <	AnnoMinimo)
		throw Invalida("Año Incorrecto.");
	return *this;
}

Fecha& Fecha::sumames(int incmt_m)
{
	if (incmt_m == 12)
	{
		this->m_ = 1;
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
	}
	else
		this->m_ = decmt_m;

	return *(this);
}

Fecha& Fecha::sumayear(int incmt_a)
{
	this->a_ = a_ + incmt_a;
	if(a_ >	AnnoMaximo)
		throw Invalida("Año Incorrecto.");

	return *this;
}

Fecha& Fecha::restayear(int decmt_a)
{
	this->a_ = a_ - decmt_a;

	if(a_ <	AnnoMaximo)
		throw Invalida("Año Incorrecto.");

	return *this;
}
/*-----------------FIN MODIFICADORAS--------------------*/

/*------------------OBSERVADORAS------------------------*/
const char* Fecha::cadena()const noexcept
{
	static char f_explicita[40];
	tm timeinfo = { 0, 0, 0, d_, m_ - 1, a_ - 1900, 0, 0, -1 };
	mktime(&timeinfo);
	const char* const weekday[7] = {"domingo","lunes","martes","miércoles","jueves","viernes","sábado"};
	const char* const month[12] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};
	sprintf(f_explicita,"%s %d de %s de %4d", weekday[timeinfo.tm_wday], dia(), month[timeinfo.tm_mon], anno());
	return f_explicita;
}
/*------------------FIN OBSERVADORAS---------------------*/

bool Fecha::comprueba_fecha(int& dia, int& mes, int& anyo)
{
	if ((anyo < AnnoMinimo) || (anyo > AnnoMaximo))
		throw(Invalida("Año Incorrecto."));//year

	else
	{
		switch(mes)
		{
			case 1:
				case 3:
					case 5:
						case 7:
							case 8:
								case 10:
									case 12:
									{
										if(dia < 1 || dia > 31)
											throw(Invalida("Dia31: Dia incorrecto del mes."));//dia
										break;
									}
			case 4:
				case 6:
					case 9:
						case 11:
						{
							if(dia < 1 || dia > 30)
								throw(Invalida("Dia30: Dia incorrecto del mes."));//dia
							break;
						}
			case 2:
			{
				if((anyo % 4) == 0)
				{
					if (dia < 1 || dia > 29)
                        throw(Invalida("Dia29: Febrero."));//dia
				}
				else
				{
					if(dia < 0 || dia > 28)
						throw(Invalida("Dia28: Febrero."));//dia
				}
				break;
			}
			default:
				throw(Invalida("Mes incorrecto."));//mes
		}
	}

	return true;
}


/*---OPERADORES EXTERNOS---*/

bool operator ==(const Fecha& fec1, const Fecha& fec2)
{
	return ((fec1.dia() == fec2.dia()) and (fec1.mes() == fec2.mes()) and (fec1.anno() == fec2.anno()));
}

bool operator <(const Fecha& fec1, const Fecha& fec2)
{
	return (fec1.anno() < fec2.anno() or ((fec1.anno() == fec2.anno() and fec1.mes() < fec2.mes()) or (fec1.mes() == fec2.mes() and fec1.dia() < fec2.dia())));
}

bool operator >(const Fecha& fec1, const Fecha& fec2)
{
	return ((fec1.anno() > fec2.anno()) or ((fec1.anno() == fec2.anno() and fec1.mes() > fec2.mes()) or (fec1.mes() == fec2.mes() and fec1.dia() > fec2.dia())));
}

bool operator <=(const Fecha& fec1, const Fecha& fec2)
{
	return (fec1.anno() < fec2.anno() or ((fec1.anno() == fec2.anno() and fec1.mes() < fec2.mes()) or (fec1.mes() == fec2.mes() and fec1.dia() <= fec2.dia())));
}

bool operator >=(const Fecha& fec1, const Fecha& fec2)
{
	return ((fec1.anno() > fec2.anno()) or ((fec1.anno() == fec2.anno() and fec1.mes() > fec2.mes()) or (fec1.mes() == fec2.mes() and fec1.dia() >= fec2.dia())));
}

bool operator !=(const Fecha& fec1, const Fecha& fec2)
{
	return not ((fec1.dia() == fec2.dia()) and (fec1.mes() == fec2.mes()) and (fec1.anno() == fec2.anno()));
}

ostream& operator <<(ostream& os, const Fecha& fec)
{
	os << fec.cadena();
	return os;
}

istream& operator >>(istream& is, Fecha& fec)
{
	static char fecha[11];
	int dt,mt,at;

	sprintf(fecha, "%d/%d/%d",fec.dia(), fec.mes(), fec.anno());

	int istream_tam = is.readsome(fecha,12);
	is.seekg(0, is.beg);

	if((istream_tam < 8) or (istream_tam > 11))
		throw(Fecha::Invalida("Desbordamiento de fecha."));

	if((sscanf(fecha,"%d/%d/%d", &dt, &mt, &at)) != 3)
		throw(Fecha::Invalida("Entrada incorrecta en extraccion."));

	is >> fecha;
	fec=fecha;
	return is;
}

Fecha operator + (int incremento, const Fecha& fec)
{
	Fecha tmp(fec);
	tmp += incremento;
	return tmp;
}

Fecha operator + (const Fecha& fec, int incremento)
{
	Fecha tmp(fec);
	tmp += incremento;
	return tmp;
}

Fecha operator - (int decremento, const Fecha& fec)
{
	Fecha tmp(fec);
	tmp -= decremento;
	return tmp;
}

Fecha operator - (const Fecha& fec, int decremento)
{
	Fecha tmp(fec);
	tmp -= decremento;
	return tmp;
}

long int operator - (const Fecha& f1, const Fecha& f2)
{
	tm minuendo{0,0,0,f1.dia(),f1.mes()-1, f1.anno()-1900,0,0,0};
	tm sustraendo{0,0,0,f2.dia(),f2.mes()-1, f2.anno()-1900,0,0,0};
	long diferencia = difftime(mktime(&minuendo),mktime(&sustraendo)) / 86400;
	return diferencia;
}