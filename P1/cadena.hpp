/***************************************************************************
* cadena.hpp
*
* mie, mar 16 2016 19:00:45
* Copyright 2016 Jose M Barba Gonzalez
* <user@host>
****************************************************************************/
/*
* cadena.hpp
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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CADENA_HPP
#define CADENA_HPP
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include <vector>
#include <iterator>

using namespace std;

class Cadena
{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		static const size_t npos = -1;//numero de posiciones a copiar.

		/*Constructores*/
		//Constructor predeterminado texto_[0]=' ';
		explicit Cadena(){tam_ = 0;s_ = new char[1];s_[0]='\0';}
		//Constructor de conversión
		Cadena(size_t longitud, char caracter);
		//Constructor de espacios vacíos.
		explicit Cadena(size_t tamano);
		//Constructor de copia de un objeto Cadena
		Cadena(const Cadena& frase);
		//Constructor de movimiento de un objeto Cadena
		Cadena(Cadena&& frase);
		//Constructor de copia de una cadena a bajo nivel.
		Cadena(const char* texto);
		//Constructor de una sub-cadena de bajo nivel char*.
		Cadena(const char* texto, size_t n);
		//Constructor de una sub-cadena desde una posicion sobre un objeto Cadena de un tamaño determinado.
		Cadena(const Cadena& frase, size_t pos, size_t n=-1);

		//operadores sobrecargados
		Cadena& operator +=(const Cadena& frase) noexcept;
		Cadena& operator =(const char* texto) noexcept;
		//Asignacion de copia
		Cadena& operator =(const Cadena& frase) noexcept;
		//Asignacion de movimiento
		Cadena& operator =(Cadena&& frase) noexcept;
		char& operator[](size_t i) noexcept;
		char operator[](size_t i) const noexcept;

		//Funcion que extrae una subcadena dentro de otra
		//La variable 'inicio' indica el indice donde comenzara a contar, contando
		//el numero de caracteres especificado en la variable 'num_caracteres'.
		Cadena substr(size_t inicio, size_t num_caracteres) const throw(out_of_range);
		char at(size_t i) const throw(out_of_range);
		char& at(size_t i) throw(out_of_range);

		//funciones observadoras
		char* Cad() const noexcept {return s_;}
		const char* c_str() const noexcept {return s_;};
		//recibe un objeto Cadena para verificar su longitud
		size_t length(Cadena& c)const noexcept {return c.tam_;}
		//devuelve el atributo tamano_ del objeto cadena actual
		size_t length()const noexcept {return tam_;}
		//const char* imprimirP()const;
		void imprimirP()const noexcept {cout << s_;};

		//funciones sobre iteradores
		iterator begin() const noexcept;
		iterator end() const noexcept;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rbegin() const noexcept;
		reverse_iterator rend() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		const_reverse_iterator crend() const noexcept;

		//Destructor de Cadena
		~Cadena(){delete [] s_;};

	private:
		char* s_;
		size_t tam_;
};

//operadores sobrecargados externos de mas de un elemento
Cadena operator+(const Cadena& texto1,const Cadena& texto2);
bool operator ==(const Cadena& texto1,const Cadena& texto2);
bool operator !=(const Cadena& texto1,const Cadena& texto2);
bool operator >=(const Cadena& texto1,const Cadena& texto2);
bool operator >(const Cadena& texto1,const Cadena& texto2);
bool operator <=(const Cadena& texto1,const Cadena& texto2);
bool operator <(const Cadena& texto1,const Cadena& texto2);

//Insercción y extracción de flujo
ostream& operator <<(ostream& out,const Cadena& texto);
istream& operator >>(istream& in,Cadena& texto);

#endif // CADENA_HPP