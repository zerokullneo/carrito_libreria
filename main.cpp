#include "cabeceras.h"
#include "P1/Fecha/fecha.h"
#include "P1/Cadena/cadena.h"

int main()
{
	Fecha fec;
	Cadena cad;

	fec = Fecha (21,2,1982);
	cad = Cadena("Jose M. Barba");
	
	cout << "Nombre: ";
	cad.imprimirP();
	cout << "." << endl << "Fecha de Nacimiento: ";
	fec.visualizar();
	cout << cad.longitudE() << endl;

	return 0;
}