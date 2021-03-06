/***************************************************************************
 *            pedido_articulo.cpp
 *
 *  mie mayo 28 14:30:35 20166
 *  Copyright  2016  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * pedido_articulo.cpp
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

#include "pedido-articulo.hpp"

/*##########Clase LineaPedido##########*/
LineaPedido::LineaPedido(double p, unsigned c):precio_venta_(p),cantidad_(c)
{}

ostream& operator <<(ostream& out,const LineaPedido& l)
{
	out << setprecision(2) << fixed << l.precio_venta() << " €\t" << l.cantidad();
	return out;
}

/*##########Clase OrdenaPedidos##########*/

bool OrdenaPedidos::operator()(Pedido* p1,Pedido* p2)const
{
	return (p1->numero() < p2->numero());
}

/*##########Clase OrdenaArticulos##########*/

bool OrdenaArticulos::operator()(Articulo* a1, Articulo* a2)const
{
	return (a1->referencia() < a2->referencia());
}

/*##########Clase Pedido_Articulo##########*/

void Pedido_Articulo::pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad)
{
    //insercción en ambos sentidos de los artículos de un pedido
	Pedido_Articulo_[&pedido].insert(std::make_pair(&articulo,LineaPedido(precio,cantidad)));
	Articulo_Pedido_[&articulo].insert(std::make_pair(&pedido,LineaPedido(precio,cantidad)));
}

void Pedido_Articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad)
{
	pedir(pedido,articulo,precio,cantidad);
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{
	return Pedido_Articulo_[&p];
}

Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& a)
{
	return Articulo_Pedido_[&a];
}

ostream& operator <<(ostream& out, const Pedido_Articulo::ItemsPedido& i)
{
	double precio_total = 0.0;
	if(!i.empty())
	{
		out << "=============================================================================\n";
		out << "PVP\tCant.\tArtículo";
		out << "\n=============================================================================\n";

		for (Pedido_Articulo::ItemsPedido::const_iterator itt = i.begin(); itt!=i.end(); ++itt)
		{
			out << itt->first->precio() << " €\t" << itt->second.cantidad();
			out << "\t[" << itt->first->referencia() << "] \"" << itt->first->titulo() << "\"\n";
			precio_total+=itt->second.precio_venta() * itt->second.cantidad();
		}

		out << "=============================================================================\n";
		out << "Total:\t" << precio_total << " €\n";
	}

	return out;
}

ostream& operator <<(ostream& out, const Pedido_Articulo::Pedidos& p)
{
	out << "[Pedidos: " << p.size() << "]";
	if(!p.empty())
	{
		out << "\n=============================================================================\n";
		out << "PVP\tCant.\tFecha venta";
		out << "\n=============================================================================\n";
		double precio_total = 0.0;
		int cantidad_total = 0;

		for(Pedido_Articulo::Pedidos::const_iterator itt = p.begin(); itt!=p.end(); ++itt)
		{
			out << itt->second.precio_venta() << " €" << "\t" << itt->second.cantidad() << "\t" << itt->first->fecha() << endl;
			precio_total += (itt->second).precio_venta() * itt->second.cantidad();
			cantidad_total += itt->second.cantidad();
		}
		out << "=============================================================================\n";
		out << "Precio Total: " << setprecision(2) << fixed << precio_total << " €\tCantidad Total: " << cantidad_total;
	}
	return out;
}

void Pedido_Articulo::mostrarDetallePedidos(ostream& out)const
{
	double total_ventas = 0.0;

	for(map<Pedido*,ItemsPedido,OrdenaPedidos>::const_iterator i = Pedido_Articulo_.begin(); i != Pedido_Articulo_.end(); ++i)
	{
		out << "Pedido núm.\t" << (i->first)->numero() << " Cliente:\t" << (i->first)->tarjeta()->titular_facial() << "\tFecha:\t" << (i->first)->fecha().cadena() << endl;
		out << i->second;
		total_ventas += (i->first)->total();
	}
	if(!Pedido_Articulo_.empty())
		out << "TOTAL VENTA:\t" << total_ventas << " €";
}

void Pedido_Articulo::mostrarVentasArticulos(ostream& out)const
{
	for(map<Articulo*,Pedidos>::const_iterator i = Articulo_Pedido_.begin(); i != Articulo_Pedido_.end(); ++i)
	{
		out << "Ventas de " << "[" << i->first->referencia() << "] \"" << i->first->titulo() << "\"\t" << i->first->precio() << " €";
		out	<< i->second << endl << endl;
	}
}