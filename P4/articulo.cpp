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
 * along with this protitgram. If not, see <http://www.gnu.org/licenses/>.
 */

#include "articulo.h"

Articulo::Articulo(Cadena ref, Cadena tit, Fecha fec, double pvp, unsigned stk)
{
	referencia_ = ref;
	titulo_ = tit;
	f_publi_ = fec;
	precio_ = pvp;
	stock_ = stk;
}

ostream& operator <<(ostream& out, const Articulo& art)
{
	out << "[" << art.referencia() << "] " << "\"" << art.titulo() << "\", " << art.f_publi().visualizar_anyo() << ". " << art.precio() << "€" << endl;
	return out;
}