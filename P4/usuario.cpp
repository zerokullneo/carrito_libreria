/***************************************************************************
 *            usuario.cpp
 *
 *  mie mayo 7 11:37:48 2014
 *  Copyright  2014  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * usuario.cpp
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
#include <unistd.h>
#include <random>
#include <assert.h>
#include "usuario.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

struct  GNA {
	GNA() {	srand(time(0));}
	};

GNA g;

/*CLASE CLAVE*/
Clave::Clave(const char* clav)
{
	if(strlen(clav) < 5)throw Incorrecta(CORTA);

	const char* const salt_chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789./";

	char salt[] = {salt_chars[rand()%64],salt_chars[rand()%64]};

	const char* c = crypt(clav,salt);

	if (c == nullptr) throw Incorrecta(ERROR_CRYPT);

	clave_ = c;

	if(!clave_.length())throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* pass) const noexcept
{

	char* poss = crypt(pass,clave_.c_str());

	return (0 == strcmp(poss, clave_.c_str()));
}
/*FIN CLASE CLAVE*/

/*CLASE USUARIO*/
//Columna de identificadores de usuarios.
static Usuario::Usuarios id_;

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apll, const Cadena& dir, const Clave& pass):
identificador_(id), nombre_(nom), apellidos_(apll), direccion_(dir), contrasenia_(pass)
{
	//comprobamos si ese identificador de usuario ya existe.
	if(id_.insert(identificador_).second == false)
		throw Id_duplicado(id);
}

void Usuario::es_titular_de(Tarjeta& tjt) noexcept
{
	if(tjt.titular() == this)
		if(tarjetas_.find(tjt.numero()) == tarjetas_.end())
			//insertamos el par Numero-Tarjeta en el map de tarjetas_
			tarjetas_.insert(pair<Numero,Tarjeta*>(tjt.numero(),&tjt));
}

void Usuario::no_es_titular_de(Tarjeta& tjt) noexcept
{
	//eliminamos el par de tarjetas_ dada la tarjeta tjt
	tarjetas_.erase(tjt.numero());
	//anulamos el titular de tjt
	tjt.anula_titular();
}

void Usuario::compra(Articulo& art, unsigned i) noexcept
{
	if(i == 0)//si se recibe un 0 como cantidad se vacía el carro.
		articulos_.erase(&art);
	else
	{
		//si no existe el Articulo se inserta en el par y se indica la cantidad
		if(!articulos_.insert(pair<Articulo*,unsigned>(&art,i)).second)
			articulos_[&art] = i;
	}
}

Usuario::~Usuario()
{
	//Eliminación de usuario.
	id_.erase(identificador_);
	//Eliminamos todas las tarjetas que tenga el usuario.
	for(Usuario::Tarjetas::const_iterator it=tarjetas_.begin(); it!=tarjetas_.end(); it++)
		(it->second)->anula_titular();
}
/*FIN CLASE USUARIO*/

ostream& operator <<(ostream& out, const Usuario& u)
{
	out << u.id() << " [" << u.clave().clave() << "] " << u.nombre() << " " << u.apellidos() << endl << u.direccion() << endl << "Tarjetas:\n";

	for(Usuario::Tarjetas::const_iterator it = u.tarjetas().begin(); it != u.tarjetas().end(); it++)
		out << *((*it).second) << endl;

	return out;
}

ostream& mostrar_carro(ostream& out, const Usuario& u)
{
	out << "Carrito de compras de " << u.id() << " [Artículos: " << u.n_articulos() << "]\n";

	if(u.n_articulos() != 0)
	{
		out << " Cant. Artículo\n";
		out << "=======================================================================\n";
		for(Usuario::Articulos::const_iterator it = u.compra().begin(); it != u.compra().end(); it++)
		{
			out << (*it).second << " " << "[" << it->first->referencia() << "] \"" << it->first->titulo() << "\", " << it->first->f_publi().anno();
			out << ". " << setprecision(2) << fixed << it->first->precio() << " €" << endl;
		}
	}

	return out;
}