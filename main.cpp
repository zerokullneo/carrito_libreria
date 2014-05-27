#include "cabeceras.h"
#include "P1/Fecha/fecha.h"
#include "P1/Cadena/cadena.h"
#include "P4/articulo.h"
#include "P4/tarjeta.h"

int main()
{
	Fecha fecM(21,2,1982);
	Fecha fpubli(1,1,1970);
	Fecha f;
	const char *user = "Jose M. Barba";
	Cadena art_id("110");
	Cadena art_nom("Programación C");
	Cadena cadM(user);
	Numero Num_tjtM("1234 9840 9482 3847");
	Tarjeta TjtM(Num_tjtM);
	istringstream is("4/10/2000");
	cout << "---" << endl;
	is >> f;

	Articulo artM(art_id,art_nom,fpubli,50.55,100);
	
	cout << "Main\n" << cadM;
	cout << "." << endl << "Fecha de Nacimiento: "; fecM.visualizar();
Fecha g(--fecM);g.visualizar();g.restadias(3);g.visualizar();
++g;g.visualizar();g.sumadias(2);g.visualizar();
	cout << "---" << endl;
	f.visualizar();
	cout << f;

	cout << "\n---Articulo---\n" << artM;
	cout << "\n---Tarjeta---\n" << TjtM.tarjeta() << endl;

	return 0;
}