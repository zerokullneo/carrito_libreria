//           cadena.cpp
//  vie diciembre 20 01:53:35 2013
//  Copyright  2013  Jose M Barba Gonzalez
//  <user@host>
// cadena.cpp
//
// Copyright (C) 2013 - Jose M Barba Gonzalez
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "cadena.h"

using namespace std;

/*CONSTRUCTORES*/
Cadena::Cadena(unsigned int longitud, const char caracter)
{
	unsigned int i;

	tamano_ = longitud;

	texto_= new char[tamano_ + 1];
	for(i=0; i<tamano_; i++)
		texto_[i]=caracter;

	texto_[i+1]='\0';
}

Cadena::Cadena(const Cadena& frase)
{
	tamano_ = frase.tamano_;
	texto_ = new char[tamano_+1];
	strncpy(texto_,frase.texto_,tamano_);
}

Cadena::Cadena(const char* texto)
{
	tamano_= strlen(texto);
	texto_ = new char[tamano_+1];
	strncpy(texto_,texto,tamano_);
}

Cadena::Cadena(unsigned int tamano)
{
	tamano_ = tamano;
	texto_= new char[tamano_ + 1];

	for(unsigned int i =0; i<tamano; i++)
		texto_[i]=' ';

	texto_[tamano_ + 1]='\0';
}

/*FIN CONSTRUCTORES*/

/*OPERADORES*/

//se suma al 'texto_' existente la nueva 'frase'
Cadena& Cadena::operator += (const Cadena& frase)
{
	int i, n1 = tamano_, n2 = frase.tamano_;

	char* texto_aux = new char[n1+n2+1];

	for(i = 0; i <= n1; i++)
		texto_aux[i] = texto_[i];
	for(i++; i <= n2; i++)
		texto_aux[i] = frase.texto_[i];

	texto_aux[i+1] = '\0';

	this->~Cadena();
	return *this;
	//Cadena(texto_aux);
	delete texto_aux;
}

const char* Cadena::operator =(const char* texto)
{
	//this->~Cadena();
	return texto;
}

Cadena& Cadena::operator =(const Cadena& frase)
{
	this->~Cadena();
	strcpy(texto_, frase.texto_);
	return *this;
}

char Cadena::operator[](unsigned int i) const
{
	return *(texto_+i);
}

char& Cadena::operator[](unsigned int i)
{
	return *(texto_+i);
}

Cadena operator+(const Cadena& texto1,const Cadena& texto2)
{
	Cadena frase(texto1);
	frase += texto2;
	return frase;
}

bool operator ==(const Cadena& texto1,const Cadena& texto2)
{
	unsigned int tam_texto1 = texto1.longitudE();

	unsigned int tam_texto2 = texto2.longitudE();

	if(tam_texto1 == tam_texto2)
		return true;
	else
		return false;
}

bool operator !=(const Cadena& texto1,const Cadena& texto2)
{
	unsigned int tam_texto1 = texto1.longitudE();

	unsigned int tam_texto2 = texto2.longitudE();

	if(tam_texto1 != tam_texto2)
		return true;
	else
		return false;
}

bool operator >=(const Cadena& texto1,const Cadena& texto2)
{
	unsigned int tam_texto1 = texto1.longitudE();

	unsigned int tam_texto2 = texto2.longitudE();

	if(tam_texto1 >= tam_texto2)
		return true;
	else
		return false;
}

bool operator >(const Cadena& texto1,const Cadena& texto2)
{
	unsigned int tam_texto1 = texto1.longitudE();

	unsigned int tam_texto2 = texto2.longitudE();

	if(tam_texto1 > tam_texto2)
		return true;
	else
		return false;
}

bool operator <=(const Cadena& texto1,const Cadena& texto2)
{

	unsigned int tam_texto1 = texto1.longitudE();

	unsigned int tam_texto2 = texto2.longitudE();

	if(tam_texto1 <= tam_texto2)
		return true;
	else
		return false;
}

bool operator <(const Cadena& texto1,const Cadena& texto2)
{
	unsigned int tam_texto1 = texto1.longitudE();

	unsigned int tam_texto2 = texto2.longitudE();

	if(tam_texto1 < tam_texto2)
		return true;
	else
		return false;
}
/*FIN OPERADORES*/

/*SUBCADENA*/
Cadena Cadena::subcadena(unsigned int inicio, unsigned int num_caracteres)throw(out_of_range)
{
	if((inicio < 0) || (num_caracteres < 0) || ((inicio+num_caracteres) > tamano_) || (inicio > tamano_) || (num_caracteres > tamano_))
		throw out_of_range("El indice de comienzo o el numero de caracteres indicado está fuera de rango.\n");
	else
	{
		Cadena subtxt(num_caracteres);
		for (unsigned int i = inicio; i < num_caracteres; i++)
			subtxt[i]= texto_[i];
		return subtxt;
	}
}

char Cadena::at(unsigned int i)const throw(out_of_range)
{
	if((i>=tamano_) || (i<0))
		throw out_of_range("El índice indicado está fuera de rango.\n");
	else
		return texto_[i];
}

char& Cadena::at(unsigned int i)throw(out_of_range)
{
	if((i >= tamano_) || (i<0))
		throw out_of_range("El índice indicado está fuera de rango.\n");
	else
		return texto_[i];
}
/*FIN SUBCADENA*/

/*OPERADORES DE FLUJO*/
ostream& operator <<(ostream& out,const Cadena& texto)
{
	out << "Nombre: " << texto.texto_;
	return out;
}

istream& operator >>(istream& in,Cadena& texto)
{
	char* txt = new char[texto.longitudE()];
	in.width(texto.longitudE());
	strcpy(txt,texto.texto_);
	in >> txt;
	return in;
}

/*FIN OPERADORES DE FLUJO*/

/*OBSERVADORAS*/
unsigned int Cadena::longitudC(Cadena& c) const
{
	unsigned int i;

	for(i=0; c.texto_[i]!='\0'; i++);

	return i;
}
//const char*
void Cadena::imprimirP()const
{
	cout << texto_;
}
/*FIN OBSERVADORAS*/