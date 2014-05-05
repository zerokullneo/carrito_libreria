#include "cabeceras.h"
#include "P1/Fecha/fecha.h"
#include "P1/Cadena/cadena.h"

int main()
{
	Fecha fecM(21,2,1982), f;
	Cadena cadM("Jose M. Barba");
	istringstream is("14/10/2000");
	cout << "---" << endl;
	is >> f;
	
	cout << "Main\n" << cadM;
	cout << "." << endl << "Fecha de Nacimiento: ";
	fecM.visualizar();
	f.visualizar();

	return 0;
}