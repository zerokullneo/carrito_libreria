// $Id: luhn.cpp 218 2013-04-10 19:17:29Z gerardo $
// Verifica un número de tarjeta empleando el algoritmo de Luhn
// Referencias:
//              http://en.wikipedia.org/wiki/Luhn_algorithm
//

// $Id: luhn.cpp 235 2013-05-04 07:56:03Z gerardo $
// Verifica un número de tarjeta empleando el algoritmo de Luhn
// Referencias:
//              http://en.wikipedia.org/wiki/Luhn_algorithm
//
#include "../P1/Cadena/cadena.h"
#include <cstddef>
#include "../P4/tarjeta.h"

// Recibe:
// - Una Cadena formada solo por dígitos [0..9]
// - El tamaño de la Cadena a considerar
// Devuelve:
// - verdad si numero es un número válido de tarjeta
bool luhn(const Cadena& numero, std::size_t n)
{
  std::size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[std::size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}
