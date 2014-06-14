#include "cabeceras.h"
#include "P1/Fecha/fecha.h"
#include "P1/Cadena/cadena.h"
#include "P4/articulo.h"
#include "P4/tarjeta.h"

Articulo::Autores crea_autores(Autor& autor);

int main()
{
	Fecha fecM(21,2,1982);
	Fecha fpubli(1,1,1970);
	Fecha fexp(31,12,2015);
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
	ostringstream os("");
	cout << "---" << endl;
	is >> f;

	Usuario userM(userid,userNom,userApll,userDir,userPass);
	Autor autM(userNom,userApll,userDir);
	Articulo::Autores autores = crea_autores(autM);
	Libro artM(autores,art_id,art_nom,fpubli,50.55,200,100);
	InformeDigital InfDigM(autores,art_id,art_nom,fpubli,50.55,fexp);
	
	cout << "Main\n" << cadM << "." << endl;
	cout << "---Fecha---" << endl;
	cout << "Fecha de Nacimiento: "; fecM.visualizar();
Fecha g(--fecM);g.visualizar();g.restadias(3);g.visualizar();
++g;g.visualizar();g.sumadias(2);g.visualizar();
	cout << "---" << endl;
	f.visualizar();
	cout << f;

	cout << "\n---Articulo Libro---\n" << artM;
	cout << "\n---Articulo InformeDigital---\n" << "A la venta hasta el "; InfDigM.imp_esp(os);
	cout << "\n---Tarjeta---\n" << TjtM.tarjeta() << endl;
	cout << "\n---Usuario---\n" << userM.id() << "|" << userM.nombre() << " " << userM.apellidos() << "|" << userM.direccion() << "|" << userPass.clave() << endl;

	if(userPass.verifica("holas"))
		cout << "Verificada" << endl;
	else
		cout << "No Verificada" << endl;

	return 0;
}

Articulo::Autores crea_autores(Autor& autor) {
  Articulo::Autores autores;
  autores.insert(&autor);
  return autores;
}