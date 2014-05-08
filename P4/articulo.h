/***************************************************************************
 *            articulo.h
 *
 *  mar mayo 6 12:52:48 2014
 *  Copyright  2014  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * articulo.h
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

class Articulo
{
	public:
		//Constructores
		Articulo(const Cadena& ref, const Cadena& tit, const Fecha& fec, double pvp, unsigned stk);

		//Métodos observadores
		Cadena referencia()const{return referencia_;}
		Cadena titulo()const{return titulo_;}
		Fecha f_publi()const{return f_publi_;}
		double precio()const{return precio_;}
		unsigned stock()const{return stock_;}
		
		//Métodos modificadores
		//modifica el atributo precio_ con el nuevo valor indicado en pvp.
		double& precio(double& pvp){return precio_ = pvp;}
		//modifica el atributo stock_ con el nuevo valor indicado en stk.
		unsigned& stock(unsigned& stk){return stock_ = stk;}

		virtual ~Articulo(){};

	private:
		Cadena referencia_;
		Cadena titulo_;
		Fecha f_publi_;
		double precio_;
		unsigned stock_;
};

//Operadores sobrecargados
ostream& operator <<(ostream& out, const Articulo& art);