/***************************************************************************
 *            autor.h
 *
 *  mie mayo 28 14:30:35 2014
 *  Copyright  2014  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * autor.h
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
#ifndef AUTOR_H
#define AUTOR_H

class Autor
{
	public:
		Autor(Cadena nom, Cadena apll, Cadena dir):nombre_(nom), apellidos_(apll), direccion_(dir){};

		//Métodos observadores de los atributos.
		Cadena nombre()const {return nombre_;}
		Cadena apellidos()const {return apellidos_;}
		Cadena direccion()const {return direccion_;}

		~Autor();

	private:
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
};

#endif // AUTOR_H
