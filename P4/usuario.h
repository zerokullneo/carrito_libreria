/***************************************************************************
 *            usuario.h
 *
 *  mie mayo 7 11:37:48 2014
 *  Copyright  2014  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * usuario.h
 *
 * Copyright (C) 2014 - Jose M Barba Gonzalez
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
 
#include "../cabeceras.h"
#include "../P1/Cadena/cadena.h"
#include "../P1/Fecha/fecha.h"

class Articulo;
class Numero;
class Tarjeta;

class Clave
{
	public:
		Clave(Cadena clav):clave_(clav){};
		
		Cadena clave()const{return clave_;}
		
		bool verifica(const char* pass);
	private:
		Cadena clave_;
		Cadena encriptar();
		class Incorrecta
		{
			public:
				enum Razon{CORTA, ERROR_CRYPT};
				Incorrecta(enum Razon);
				Razon razon()const{return r_;}
			private:
				Razon r_;
		};
};

class Usuario
{
	public:
		//Constructor
		Usuario(Cadena id, Cadena nom, Cadena apll, Cadena dir, Clave pass);
		//Constructor de copia de un objeto Usuario
		Usuario(const Usuario& user);

		//Métodos observadores de los atributos.
		Cadena id()const {return identificador_;}
		Cadena nombre()const {return nombre_;}
		Cadena apellidos()const {return apellidos_;}
		Cadena direccion()const {return direccion_;}
		const map<Numero, Tarjeta*>& tarjetas(Numero& t)const; //{return &Tarjetas;}
		
		//Métodos modificadores
		void es_titular_de(Tarjeta&);
		void no_es_titular_de(Tarjeta&);

	private:
		Cadena identificador_;
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
		Clave contrasenia_;
		typedef map<Numero, Tarjeta*> Tarjetas;
		typedef map<Articulo*, unsigned> Articulos;
};