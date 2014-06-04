/***************************************************************************
 *            tarjeta.h
 *
 *  mie mayo 7 11:37:48 2014
 *  Copyright  2014  Jose M Barba Gonzalez
 *  <user@host>
 ****************************************************************************/
/*
 * tarjeta.h
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

#include "tarjeta.h"

/*VALIDACIÓN DEL NÚMERO DE TARJETA*/ //static
int Numero::isValidNumber(char* number)
{
	int n, i, alternate, sum;

	if (!number)
		return 0;

	n = strlen(number);

	if (n < 13 || n > 19)
		return 0;

	for (alternate = 0, sum = 0, i = n - 1; i > -1; --i)
	{
		if (!isdigit(number[i]))
			return -1;

		n = number[i] - '0';

		if (alternate)
		{
			n *= 2;
			if (n > 9)
			n = (n % 10) + 1;
		}
		alternate = !alternate;

		sum += n;
	}

	return (sum % 10 == 0);
}
/*FIN VALIDACIÓN*/

/*CLASE TARJETA*/
Tarjeta::Tarjeta(const Numero& tjt):tarjeta_(tjt)
{}
/*FIN CLASE TARJETA*/

/*CLASE NUMERO*/
Numero::Numero(const Cadena& n)throw (Incorrecto):numero_(n)
{
	char digitos[19];
	int i, j = 0;
	
	for(i = 0; numero_[i] != '\0'; i++)
		if (isdigit(numero_[i]))
		{
			digitos[j] = numero_[i];
			j++;
		}
	numero_ = digitos;
	
	if(numero_.longitudE() < 13 || numero_.longitudE() > 19)
		throw Incorrecto(Incorrecto::LONGITUD);

	if(isValidNumber(numero_.imprimir()) == -1)
		throw Incorrecto(Incorrecto::DIGITOS);

	if(isValidNumber(numero_.imprimir()) == 0)
		throw Incorrecto(Incorrecto::NO_VALIDO);
}

Numero::Incorrecto::Incorrecto(Razon r):razon_(r)
{
	cerr << "Número: ";
		switch(razon())
		{
			case 0:
				cerr<<"LONGITUD";
				break;
			case 1:
				cerr<<"DIGITOS";
				break;
			case 2:
				cerr<<"NO_VALIDO";
				break;
		}
	cerr << endl;
}
/*FIN CLASE NUMERO*/