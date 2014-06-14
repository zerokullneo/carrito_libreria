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
	Cadena userid("001");
	Cadena userNom("Jose M");
	Cadena userApll("Barba Gonzalez");
	Cadena userDir("su casa");
	Clave userPass("holas");
	istringstream is("4/10/2000");
	cout << "---" << endl;
	is >> f;

	Usuario userM(userid,userNom,userApll,userDir,userPass);
	Autor autM(userNom,userApll,userDir);
	Libro artM(autM,art_id,art_nom,fpubli,50.55,200,100);
	
	cout << "Main\n" << cadM << "." << endl;
	cout << "---Fecha---" << endl;
	cout << "Fecha de Nacimiento: "; fecM.visualizar();
Fecha g(--fecM);g.visualizar();g.restadias(3);g.visualizar();
++g;g.visualizar();g.sumadias(2);g.visualizar();
	cout << "---" << endl;
	f.visualizar();
	cout << f;

	cout << "\n---Articulo---\n" << artM;
	cout << "\n---Tarjeta---\n" << TjtM.tarjeta() << endl;
	cout << "\n---Usuario---\n" << userM.id() << "|" << userM.nombre() << " " << userM.apellidos() << "|" << userM.direccion() << "|" << userPass.clave() << endl;

	if(userPass.verifica("holas"))
		cout << "Verificada" << endl;
	else
		cout << "No Verificada" << endl;

	return 0;
}