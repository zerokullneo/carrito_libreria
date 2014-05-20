/***************************************************************************
 *            fecha.h
 *
 *  vie diciembre 20 01:57:48 2013
 *  Copyright  2013  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * fecha.h
 *
 * Copyright (C) 2013 - Jose M Barba Gonzalez
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../../cabeceras.h"
#include "../Cadena/cadena.h"

#define YEAR_MINIMO 1000
#define YEAR_MAXIMO 2500

#ifndef _FECHA_H_
#define _FECHA_H_
class Fecha
{	
	public:
		explicit Fecha ();
		//Constructor de enteros con los 3 parámetros.
		Fecha(int dia, int mes, int year);
		//Constructor de enteros con los 2 parámetros.
		Fecha(int dia, int mes);
		//Constructor de enteros con los 1 parámetro.
		Fecha(int dia);
		//Constructor de conversión de Cadena a Fecha.
		Fecha(char* string_fecha);

		//operadores sobrecargados
		Fecha& operator += (int incremento);
		Fecha& operator -= (int decremento);
		Fecha& operator ++ ();//postincremento
		Fecha& operator -- ();//postdecremento
		Fecha operator ++(int);//preincremento
		Fecha operator --(int);//predecremento
		Fecha& operator = (const Fecha& fec);
		//funciones modificadoras
		Fecha& sumadias(int incmt_d);
		Fecha& restadias(int decmt_d);
		Fecha& sumames(int incmt_m);
		Fecha& restames(int decmt_m);
		Fecha& sumayear(int incmt_a);
		Fecha& restayear(int decmt_a);
		//funciones observadoras
		void observadorPublico()const;
		void visualizar()const;
		int visualizar_anyo()const{return a_;}
		int visualizar_mes()const{return m_;}
		int visualizar_dia()const{return d_;}
		//~Fecha ();

	private:
		int d_, m_, a_;
		int getd_, getm_, geta_;
		time_t get_fecha_;
		struct tm * info_fecha_;
		inline void unix_secs(){time(&get_fecha_);};
		inline void unix_tm(){info_fecha_ = localtime(&get_fecha_);};
		inline void fecha_default(){getd_ = info_fecha_->tm_mday, getm_ = ((info_fecha_->tm_mon) + 1), geta_ = ((info_fecha_->tm_year) + 1900);}
		inline void defecto_(){unix_secs();unix_tm();fecha_default();};

		bool comprueba_fecha(int& dia, int& mes, int& year);
		void observadorPrivado()const{cout << "%i/" << d_ << "%i/" << m_ << "%i" << a_ << endl;}

		class Invalida
		{
			public:
				Invalida(const char* t);
				
				const char* por_que(const char* t)const{return tp_;}
			private:
				const char* tp_;
		};
	protected:
		bool operator + (int incremento);
		bool operator - (int decremento);
};

/*operadores sobrecargados de mas de un argumento*/
//Sobrecarga el operador Igualdad para poder comparar dos clases Fecha.
bool operator ==(const Fecha& fec1, const Fecha& fec2);

//Sobrecarga el operador Menor para poder comparar dos clases Fecha.
bool operator <(const Fecha& fec1, const Fecha& fec2);

//Sobrecarga el operador Mayor para poder comparar dos clases Fecha.
bool operator >(const Fecha& fec1, const Fecha& fec2);

//Sobrecarga el operador MenorIgual para poder comparar dos clases Fecha.
bool operator <=(const Fecha& fec1, const Fecha& fec2);

//Sobrecarga el operador MayorIgual para poder comparar dos clases Fecha.
bool operator >=(const Fecha& fec1, const Fecha& fec2);

//Sobrecarga el operador Distinto para poder comparar dos clases Fecha.
bool operator !=(const Fecha& fec1, const Fecha& fec2);
//bool operator + (int incremento, const Fecha& fec);
//bool operator - (int decremento, const Fecha& fec);

//Sobrecarga el operador Flujo de Salida para que la fecha sea legible por pantalla.
ostream& operator <<(ostream& os, const Fecha& fec);

//Sobrecarga el operador Flujo de Entrada para construir una Fecha de forma directa.
istream& operator >>(istream& is, Fecha& fec);
#endif	/* _FECHA_H_ */