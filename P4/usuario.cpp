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

#define _XOPEN_SOURCE
#include "usuario.h"
#include <unistd.h>

/*Clase clave*/
Clave::Clave(Cadena clav):clave_(clav)
{
	if(clave_.longitudE() < 5)throw Incorrecta(Incorrecta::CORTA);

	this->encriptar();
	//if(encriptar(clave_))throw Incorrecta(Incorrecta::ERROR_CRYPT);
}

Clave::Incorrecta::Incorrecta(Razon r):r_(r)
{
	cerr << "Clave: ";
		if(razon()==0) cerr<<"CORTA";
		if(razon()==1) cerr<<"ERROR_CRYPT";
	cerr << endl;
}

void Clave::encriptar()
{
	cout << "<<<" << clave_.c_str() << ">>>" << endl;
	const char* c = crypt(this->clave_.c_str(),"@#");
	Cadena clave_crypt(c);
	clave_crypt_ = clave_crypt;
	cout << "<<<" << clave_crypt.c_str() << ">>>" << endl;
}

bool Clave::verifica(Cadena pass)
{
	if(pass.c_str() == clave_crypt_.c_str())
		return true;
	else
		return false;
}
/*Fin Clase clave*/

/*Clase Usuario*/
Usuario::Usuario(Cadena id, Cadena nom, Cadena apll, Cadena dir, Clave pass):
identificador_(id), nombre_(nom), apellidos_(apll), direccion_(dir), contrasenia_(pass)
{}

Usuario::Id_duplicado::Id_duplicado(const Cadena& id_d)
{
	idd_ = id_d;
	cerr << idd();
}