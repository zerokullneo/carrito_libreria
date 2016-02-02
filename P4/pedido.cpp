/***************************************************************************
 *            pedido.cpp
 *
 *  mie mayo 28 14:30:35 2014
 *  Copyright  2014  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * pedido.cpp
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

#include "pedido.h"
#include "usuario-pedido.h"
#include "pedido-articulo.h"
#include "articulo.h"

int Pedido::n_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& u, const Tarjeta& t, const Fecha& f):num_(n_pedidos+1),total_(0.0),tarjeta_(&t),fecha_pedido_(f)
{
	if(u.compra().empty())
		throw(Vacio(u));

	if(tarjeta_->titular() != &u)
		throw Impostor(u);

	if(tarjeta_->caducidad() < fecha_pedido_)
		throw Tarjeta::Caducada(tarjeta_->caducidad());

	Usuario::Tarjetas tjt(u.tarjetas());

	Usuario::Articulos art(u.compra());

	Usuario::Articulos::iterator it;

	for(it = art.begin(); it != art.end(); it++)
	{
		LibroDigital* ld = dynamic_cast<LibroDigital*>(it->first);
		ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*>(it->first);
		//Comprobar si se trata de un puntero a un objeto a LibroDigital
		if(ld)
		{
			if(fecha_pedido_ <= ld->f_expir())
			{
				u.compra(*(it->first),(*it).second);
				//añadir el precio del articulo al total_
				total_ += (*(it->first)).precio() * (*it).second;
				//Asociar Pedido con Articulo
				p_a.pedir(*this,(*(it->first)),(*(it->first)).precio(),(*it).second);
			}
			else
			{
				u.compra(*it->first,0);
				ld->f_expir();
			}
		}
		else if(aa)
		{
			if(aa->stock() < (*it).second)
			{
				u.compra(*it->first,0);
				throw SinStock(*it->first);
			}
			else
			{
				u.compra(*(it->first),(*it).second);
				//añadir el precio del articulo al total_
				total_ += (*(it->first)).precio() * (*it).second;
				//Asociar Pedido con Articulo
				p_a.pedir(*this,(*(it->first)),(*(it->first)).precio(),(*it).second);
				//Actualizacion de el stock
				aa->stock() -= (*it).second;
			}
		}
		else
		{
			ld->f_expir();
		}
	}
	if(!u.n_articulos())
		throw Vacio(u);

	//Vaciar el Carrito
	for(Usuario::Articulos::iterator jt = art.begin(); jt != art.end(); jt++)
		u.compra(*(jt->first),0);

	//Asociar usuario con Pedido
	u_p.asocia(u,*this);

	++n_pedidos;
}

ostream& operator <<(ostream& out,const Pedido& p)
{
	out << "Núm. pedido:\t" << p.numero() << endl;
	out << "Fecha:\t"<< p.fecha().cadena() << endl;
	out << "Pagado con:\t" << p.tarjeta()->tarjeta() << endl;
	out << "Importe:\t" << p.total() << " €";
	return out;
}