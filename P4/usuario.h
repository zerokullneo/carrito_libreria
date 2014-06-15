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

#ifndef USUARIO_H
#define USUARIO_H

#include "../cabeceras.h"
#include "../P1/Cadena/cadena.h"
#include "../P1/Fecha/fecha.h"
#include "articulo.h"
#include "tarjeta.h"

class Tarjeta;
class Numero;

class Clave
{
	private:
		Cadena clave_;
		class Incorrecta
		{
			public:
				enum Razon{CORTA, ERROR_CRYPT};
				Incorrecta(Razon r);
				Razon razon()const{return r_;}
			private:
				Razon r_;
		};

	public:
		Clave(const char* clav)throw (Incorrecta);
		
		const char* clave()const{return clave_.c_str();}
		
		bool verifica(const char* pass);
};

class Usuario
{
	public:
		typedef set<int*,Usuario*> Usuarios;
		typedef map<Numero, Tarjeta*> Tarjetas;
		typedef map<Articulo*, unsigned> Articulos;
		//Constructor
		Usuario(Cadena id, Cadena nom, Cadena apll, Cadena dir, Clave pass);

		//Métodos observadores de los atributos.
		Cadena id()const {return identificador_;}
		Cadena nombre()const {return nombre_;}
		Cadena apellidos()const {return apellidos_;}
		Cadena direccion()const {return direccion_;}
		size_t n_articulos()const{return articulos_.size();}
		const Tarjetas& tarjetas()const{return tarjetas_;}
		const Articulos& compra()const{return articulos_;}

		//Métodos modificadores
		void es_titular_de(Tarjeta& T);
		void no_es_titular_de(Tarjeta& T);
		void compra(Articulo& A, unsigned int i);

	private:
		//Evitar la copia de un objeto Usuario
		Usuario(const Usuario&);
		Usuario& operator =(const Usuario&);

		Cadena identificador_;
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
		Clave contrasenia_;
		Articulos articulos_;
		Tarjetas tarjetas_;

		class Id_duplicado
		{
			public:
				//Constructor predeterminado
				Id_duplicado(const Cadena& id_d);

				//Método observador
				Cadena idd()const {return idd_;}

			private:
				Cadena idd_;
		};
};
#endif //USUARIO_H