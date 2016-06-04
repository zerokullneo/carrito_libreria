// cadena.cpp
//
// mie, mar 16 2016 19:00:45
// Copyright 2016 Jose M Barba Gonzalez
// <user@host>
//
// cadena.cpp
//
// Copyright (C) 2016 - Jose M Barba Gonzalez
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

#include <locale>
#include "cadena.hpp"

using namespace std;

/*CONSTRUCTORES*/
//Constructor de conversión
Cadena::Cadena(size_t longitud, char caracter):tam_(longitud)
{
	s_= new char[tam_ + 1];

	if(s_ == NULL)
		cerr << "Cadena: Predeterminado fallo de memoria." << endl;
	else
	{
		for(size_t i = 0; i < tam_; i++)
			s_[i]=caracter;

		s_[tam_] = '\0';
	}
}

//Constructor de espacios vacíos.
Cadena::Cadena(size_t tamano):tam_(tamano)
{
	s_ = new char[tam_ + 1];

	if(s_ == NULL)
		cerr << "Cadena: unsigned int fallo de memoria." << endl;
	else
	{
		for(size_t i = 0; i < tam_; i++)
			s_[i] = ' ';

		s_[tam_]='\0';
	}
}

//Constructor de copia de un objeto Cadena
Cadena::Cadena(const Cadena& frase):tam_(frase.length())
{
	s_ = new char[tam_ + 1];
	if(s_ == NULL)
		cerr << "Cadena: Cadena& fallo de memoria." << endl;
	else
		strncpy(s_, frase.s_, tam_ + 1);
}

//Constructor de movimiento de un objeto Cadena
Cadena::Cadena(Cadena&& frase): s_(frase.s_), tam_(frase.tam_)
{
	frase.s_ = nullptr;
	frase.tam_ = 0;
}

//Constructor de copia de una cadena a bajo nivel.
Cadena::Cadena(const char* texto):tam_(strlen(texto))
{
	s_ = new char[tam_ + 1];
	if(s_ == NULL)
		cerr << "Cadena: const char* fallo de memoria." << endl;
	else
	    strncpy(s_, texto, tam_ + 1);
}

//Constructor de una sub-cadena de bajo nivel char*.
Cadena::Cadena(const char* texto, size_t n):tam_(n)
{
	if(n > strlen(texto))
		tam_ = strlen(texto);

	s_ = new char[tam_ + 1];
	if(s_ == NULL)
		cerr << "Cadena: const char* fallo de memoria." << endl;
	else
	{
		for(size_t i = 0; i < tam_; i++)
			s_[i] = texto[i];

		s_[tam_]='\0';
	}
}

//Constructor de una sub-cadena desde una posicion sobre un objeto Cadena.
Cadena::Cadena(const Cadena& frase, size_t pos, size_t n):tam_(n)
{
	if(n == npos)
		tam_ = n = (frase.length());

	if((pos + n) > frase.length())
		tam_ = n = frase.length() - pos;

	if(((pos >= 0) and (pos < frase.length())) and ((pos + n) <= frase.length()))
	{
		s_ = new char[tam_ + 1];
		if(s_ == NULL)
			cerr << "Cadena: const char* fallo de memoria." << endl;
		else
		{
			for(size_t i = pos; i < (pos + tam_); i++)
				s_[i-pos] = frase[i];
			s_[tam_] = '\0';
		}
	}
	else
		throw std::out_of_range("Error Constructor sub-cadena: caracteres fuera de rango.");
}
/*FIN CONSTRUCTORES*/

/*OPERADORES*/

//se suma al 'texto_' existente la nueva 'frase'
Cadena& Cadena::operator +=(const Cadena& frase) noexcept
{
	char* texto_aux = new char[tam_ + 1];
	strncpy(texto_aux, s_, tam_ + 1);
	tam_ = this->tam_ + frase.length();
	delete[] s_;
	s_ = new char[tam_ + 1];
	strncpy(s_, texto_aux, strlen(texto_aux) + 1);
	strncat(s_, frase.s_,frase.length() + 1);
	return *this;
}

Cadena& Cadena::operator =(const char* texto) noexcept
{
	tam_ = strlen(texto);
	delete[] s_;
	s_ = new char[tam_ + 1];
	strncpy(s_, texto, tam_ + 1);
	return *this;
}

Cadena& Cadena::operator =(const Cadena& frase) noexcept
{
	tam_ = frase.length();
	delete[] s_;
	s_ = new char[tam_ + 1];
	strncpy(s_, frase.s_, tam_ + 1);
	return *this;
}

//Asignacion de movimiento
Cadena& Cadena::operator =(Cadena&& frase) noexcept
{
	tam_ = frase.tam_;
	s_ = frase.s_;
	frase.s_ = nullptr;
	frase.tam_ = 0;
	return *this;
}

char& Cadena::operator [](size_t i) noexcept
{
    return s_[i];
}

char Cadena::operator [](size_t i) const noexcept
{
    return s_[i];
}

Cadena operator +(const Cadena& texto1, const Cadena& texto2)
{
	Cadena frase(texto1);
	frase += texto2;
	return frase;
}

bool operator ==(const Cadena& texto1, const Cadena& texto2)
{
	if(strcmp(texto1.c_str(), texto2.c_str()) == 0)
		return true;
	else
		return false;
}

bool operator !=(const Cadena& texto1, const Cadena& texto2)
{
	if(strcmp(texto1.c_str(), texto2.c_str()) != 0)
		return true;
	else
		return false;
}

bool operator >=(const Cadena& texto1, const Cadena& texto2)
{
	if(strcmp(texto1.c_str(), texto2.c_str()) >= 0)
		return true;
	else
		return false;
}

bool operator >(const Cadena& texto1, const Cadena& texto2)
{
	if(strcmp(texto1.c_str(), texto2.c_str()) > 0)
		return true;
	else
		return false;
}

bool operator <=(const Cadena& texto1, const Cadena& texto2)
{
	if(strcmp(texto1.c_str(), texto2.c_str()) <= 0)
		return true;
	else
		return false;
}

bool operator <(const Cadena& texto1, const Cadena& texto2)
{
	if(strcmp(texto1.c_str(), texto2.c_str()) < 0)
		return true;
	else
		return false;
}
/*FIN OPERADORES*/

/*SUBCADENA*/
Cadena Cadena::substr(size_t inicio, size_t num_caracteres)const throw(out_of_range)
{
	if(((inicio >= 0) and (inicio <= tam_)) and (((num_caracteres > 0) and (num_caracteres < tam_)) and ((inicio + num_caracteres) < tam_)))
	{
		Cadena subtxt(num_caracteres);
		for(size_t i = inicio, j = 0; j < num_caracteres; ++i, ++j)
			subtxt.s_[j]= s_[i];

		return subtxt;
	}

	else
		throw std::out_of_range("Error substr: caracteres fuera de rango.");
}

//at Leer caracter
char Cadena::at(size_t i)const throw(out_of_range)
{
	if((i >= 0 and i <= tam_) and (tam_ > 0))
		return s_[i];

	else
		throw std::out_of_range("Error read at: posicion fuera de rango.");
}

//at Escribir caracter
char& Cadena::at(size_t i) throw(out_of_range)
{
    if((i >= 0 and i <= tam_) and (tam_ >= 0))
        return s_[i];

    else
        throw std::out_of_range("Error write at: posicion fuera de rango.");
}
/*FIN SUBCADENA*/

/*OPERACIONES SOBRE ITERADORES*/
Cadena::iterator Cadena::begin() const noexcept
{
    return &s_[0];
}

Cadena::iterator Cadena::end() const noexcept
{
    return &s_[tam_];
}

Cadena::const_iterator Cadena::cbegin() const noexcept
{
    return &s_[0];
}

Cadena::const_iterator Cadena::cend() const noexcept
{
    return &s_[tam_];
}

Cadena::reverse_iterator Cadena::rbegin() const noexcept
{
    return reverse_iterator(end());
}

Cadena::reverse_iterator Cadena::rend() const noexcept
{
    return reverse_iterator(begin());
}

Cadena::const_reverse_iterator Cadena::crbegin() const noexcept
{
    return const_reverse_iterator(end());
}

Cadena::const_reverse_iterator Cadena::crend() const noexcept
{
    return const_reverse_iterator(begin());
}
/*FIN OPERACIONES SOBRE ITERADORES*/

/*OPERADORES DE FLUJO*/
ostream& operator <<(ostream& out,const Cadena& texto)
{
	out << texto.c_str();
	return out;
}

//Extraccion
istream& operator >>(istream& in, Cadena& texto)
{
	//calcular la longitud del stream "in"
	in.seekg(0, in.end);
	int length = in.tellg();
	in.seekg(0, in.beg);

	// alojar memoria de "in":
	char *buffer = new char [length + 1];
	buffer[length]='\0';
	// leer datos como un bloque:
	while(in.get() == ' ') in.peek();//Se salta los espacios iniciales.
	in.seekg(-1, in.cur);//Coloca el puntero de "in" en el primer caracter a leer despues de saltar los espacios.
	in.getline(buffer,length+1,' ');//lee la entrada hasta el siguiente espacio
	in.putback(' ');//deja el puntero de "in" en el espacio

	if(strspn(buffer, " \t\r\n\v") > 0)// or buffer == '\0')
	{
		const Cadena z;
		texto = z.c_str();
		return in;
	}
	else
	{
		texto = buffer;
		return in;
	}
}
/*FIN OPERADORES DE FLUJO*/