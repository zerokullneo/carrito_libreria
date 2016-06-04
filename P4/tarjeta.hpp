/***************************************************************************
 *            tarjeta.hpp
 *
 *  mie mayo 7 11:37:48 2016
 *  Copyright  2016  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * tarjeta.hpp
 *
 * Copyright (C) 2016 - Jose M Barba Gonzalez
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

#ifndef TARJETA_H
#define TARJETA_H

#include <iomanip>
#include <cstddef>
#include <algorithm>
#include <locale>
#include "usuario.hpp"
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Usuario;

class Numero
{
	public:
		//Atributo que indica la no validez del número.
		enum Razon{LONGITUD, DIGITOS, NO_VALIDO};

		//Clase de verificación de número incorrecto.
		class Incorrecto
		{
			public:
				//Constructor de la clase Incorrecto.
				Incorrecto(Razon r):razon_(r){};
				//Método observador del atributo de razon_.
				Razon razon()const {return razon_;}
			private:
				Razon razon_;
		};

		//constructor del numero de tarjeta.
		Numero(const Cadena& n);

		//operador de conversión a cadena de bajo nivel.
		operator const char*()const{return numero_.c_str();}

		//comparacion de dos Numeros.
		friend bool operator <(const Numero&, const Numero&);

	private:
		Cadena numero_;
		struct EsBlanco
		{
			EsBlanco(){}
			locale loc;
			bool operator() (char c) const { return isspace(c,loc); }
		};

		struct EsDigito
		{
			EsDigito(){}
			bool operator() (char c) const { return not isdigit(c); }
		};
};

class Tarjeta
{
	public:
		enum Tipo{VISA,Mastercard,Maestro,JCB,AmericanExpress};
		//Clase de excepcion Caducada.
		class Caducada
		{
			public:
				//Constructor predeterminado.
				Caducada(const Fecha& f):caducada_(f){};
				//Método observador.
				Fecha cuando()const{return caducada_;};
			private:
				Fecha caducada_;
		};

		//Constructor de Tarjeta
		Tarjeta(const Tipo tipo, const Numero& tjt, Usuario& usuario, const Fecha& f_cad);

		//Evitar la copia de una Tarjeta
		Tarjeta(const Tarjeta&)=delete;
		//Evitar la asignacion de una Tarjeta
		Tarjeta& operator=(const Tarjeta&)=delete;

		//Métodos observadores de los atributos de Tarjeta.
		Tipo tipo()const {return tipo_;}
		Numero numero()const{return tarjeta_;}
		Fecha caducidad()const{return f_caducidad_;}
		Cadena titular_facial()const{return titular_facial_;}
		const Usuario* titular()const{return titular_;}
		void anula_titular() noexcept;

		~Tarjeta();

	private:
		Tipo tipo_;
		Numero tarjeta_;
		Usuario* titular_;
		Fecha f_caducidad_;
		Cadena titular_facial_;
};

bool operator <(const Tarjeta& t1, const Tarjeta& t2);
bool operator ==(const Tarjeta& t1, const Tarjeta& t2);
bool operator <(const Numero& n1, const Numero& n2);
ostream& operator << (ostream& out, const Tarjeta::Tipo t);
ostream& operator << (ostream& out, const Tarjeta& tjt);
#endif //TARJETA_H