#include "cabeceras.h"
#include "P1/Fecha/fecha.h"
#include "P1/Cadena/cadena.h"
#include "P4/articulo.h"

int main()
{
	Fecha fecM(21,2,1982), fpubli(1,1,1970), f;
	const char *user = "Jose M. Barba";
	Cadena artid("110");
	Cadena artnom("Programación C");
	Cadena cadM(user);
	istringstream is("14/10/2000");
	cout << "---" << endl;
	is >> f;

	Articulo artM(artid,artnom,fpubli,50,100);
	
	cout << "Main\n" << cadM;
	cout << "." << endl << "Fecha de Nacimiento: ";
	fecM.visualizar();
	f.visualizar();
	cout << "\n---" << artM;

	return 0;
}