// $Id: compra_check.cpp 301 2016-03-11 20:47:35Z gerardo $
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchersInternal.h"
#include "clang/ASTMatchers/ASTMatchersMacros.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
 
#include "llvm/Support/CommandLine.h"
#include "clang/Rewrite/Frontend/Rewriters.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>

using namespace clang::tooling;
using namespace llvm;

using namespace clang;
using namespace clang::ast_matchers;

using namespace std;

namespace clang{
	namespace ast_matchers{
	
		//Zona para definir matchers respecto a métodos incluidos en las clases.
		
		/*AST_MATCHER(clang::CXXConstructorDecl, isCopyConstructor) {
			return Node.isCopyConstructor();
		}

		AST_MATCHER(clang::CXXMethodDecl, isCopyAssignmentOperator) {
			return Node.isCopyAssignmentOperator();
		}

		AST_MATCHER(clang::CXXRecordDecl, hasCopyAssignmentWithConstParam) {
			return Node.hasCopyAssignmentWithConstParam();
		}

		AST_MATCHER(clang::CXXRecordDecl, hasCopyConstructorWithConstParam) {
			return Node.hasCopyConstructorWithConstParam();
		}

		AST_MATCHER(clang::FunctionDecl, isDeleted) {
                        return Node.isDeleted();
                }*/

		AST_MATCHER(clang::FunctionDecl, isImplicitFunction) {
			return Node.isImplicit();
		}		
	
		AST_MATCHER(clang::CXXConstructorDecl, hasBodyConstructor) {
			return Node.hasBody();
		}
	}
}

/*****************************************************************************/

DeclarationMatcher Clase_Articulo_Matcher =
            recordDecl(
                     hasName("Articulo")
            ).bind("clase_articulo");

DeclarationMatcher Clase_Tarjeta_Matcher =
            recordDecl(
                     hasName("Tarjeta")
            ).bind("clase_tarjeta");

DeclarationMatcher Clase_Usuario_Matcher =
            recordDecl(
                     hasName("Usuario")
            ).bind("clase_usuario");


/*DeclarationMatcher Copy_Constructor_Tarjeta_Matcher =
            recordDecl(
        	has( 
			constructorDecl(
				isCopyConstructor(),
				ofClass(recordDecl(hasCopyConstructorWithConstParam())),
				isDeleted()
			).bind("copy_constructor_tarjeta")
		),
		hasName("Tarjeta")
	    );

DeclarationMatcher Copy_Assignment_Tarjeta_Matcher =
            recordDecl(
        	has( 
			methodDecl(
				isCopyAssignmentOperator(),
				ofClass(recordDecl(hasCopyAssignmentWithConstParam())),	
				isDeleted()
			).bind("copy_assignment_tarjeta")
		),
		hasName("Tarjeta")
	    );

DeclarationMatcher Copy_Constructor_Usuario_Matcher =
            recordDecl(
        	has( 
			constructorDecl(
				isCopyConstructor(),
				ofClass(recordDecl(hasCopyConstructorWithConstParam())),	
				isDeleted()
			).bind("copy_constructor_usuario")
		),
		hasName("Usuario")
	    );

DeclarationMatcher Copy_Assignment_Usuario_Matcher =
 	recordDecl(
        	has( 
			methodDecl(
				isCopyAssignmentOperator(),
				ofClass(recordDecl(hasCopyAssignmentWithConstParam())),	
				isDeleted()
			).bind("copy_assignment_usuario")
		),
		hasName("Usuario")
	    );*/

DeclarationMatcher One_Constructor_Usuario_Matcher =
            recordDecl(
                forEach(
                        constructorDecl(hasBodyConstructor(), unless(isImplicit())).bind("one_constructor")
                ),
                hasName("Usuario")
            );

DeclarationMatcher Funciones_Estandar_Matcher =
        functionDecl(
                unless(isImplicitFunction()),
                forEachDescendant(
                        declRefExpr(
                                to(
                                        functionDecl(
                                                anyOf(
                                                        hasName("strlen"),
                                                        hasName("strcat"),
                                                        hasName("memset"),
                                                        hasName("strcpy"),
							hasName("strcmp")
                                                )
                                        ).bind("method_cstring")
                                )
                        )
                )
           );

DeclarationMatcher Friend_Matcher =
	recordDecl(
		hasDescendant(
			friendDecl(                                
				unless(
					has(
	                                        functionDecl(
							hasName("operator<<"),
                                                        hasAncestor(recordDecl(hasName("Usuario")))
                                                ).bind("friend_operator_usuario")
                                        )
                                )
			)
                )
        ).bind("friend_class");

DeclarationMatcher Friend_Operator_Usuario_Matcher = 
	recordDecl(
                hasDescendant(
                        friendDecl(
                                has(
                                	functionDecl(
                                        	hasName("operator<<")
                                        ).bind("friend_operator_usuario")
                                )
                        )
                )
        );

DeclarationMatcher Private_Fields_Matcher =
	recordDecl(
		forEach(
			fieldDecl().bind("field_decl")
		)
	);
/*****************************************************************************/

class CompraCheck : public MatchFinder::MatchCallback {
public :
  CompraCheck(): clase_encontrada(false), /*copy_constructor(false), copy_assignment(false),*/ one_constructor(0), cstring(true), friend_member(false), 
		 atributo_no_privado(false), friend_operator_usuario(false) {
  }

  virtual void run(const MatchFinder::MatchResult &Result) {
	Context = Result.Context;
    	Rewrite.setSourceMgr(Context->getSourceManager(), Context->getLangOpts());

	if(!clase_encontrada)
		apply_clase(Result);
	else{
		apply_busqueda_cstring(Result);
		apply_friend(Result);
		apply_acceso_atributo(Result);

		if(isFileArticulo()){

		}
		else if(isFileTarjeta()){
			/*apply_copy_constructor_tarjeta(Result);
			apply_copy_assignment_tarjeta(Result);*/
		}
		else if(isFileUsuario()){
			/*apply_copy_constructor_usuario(Result);
			apply_copy_assignment_usuario(Result);*/
			apply_one_constructor(Result);
			apply_friend_operator(Result);
		}
	}
  }
  
  /*bool tiene_delete_copy_constructor(){
	return copy_constructor && copy_assignment;
  }*/

  bool is_clase_encontrada(){
	return clase_encontrada;
  }

  bool tiene_one_constructor(){
	return one_constructor == 1 ? true : false;
  }

  bool encuentra_cstring(){
        return cstring;
  }

  bool existe_member_friend(){
	return friend_member;
  }

  bool tiene_atributo_no_privado(){
	return atributo_no_privado;
  }
 
  bool tiene_friend_operator_usuario(){
	return friend_operator_usuario;
  } 

  void setClase(string s){
	this->clase = s;
  }

private: 

  void apply_clase(const MatchFinder::MatchResult &Result){
	
	if (Result.Nodes.getNodeAs<clang::CXXRecordDecl>("clase_articulo") && isFileArticulo()){
		clase_encontrada = true;
	}
	else if(Result.Nodes.getNodeAs<clang::CXXRecordDecl>("clase_tarjeta") && isFileTarjeta()){
		clase_encontrada = true;
	}
	else if(Result.Nodes.getNodeAs<clang::CXXRecordDecl>("clase_usuario") && isFileUsuario()){
		clase_encontrada = true;
	}
  }

  /*void apply_copy_constructor_tarjeta(const MatchFinder::MatchResult &Result){
	if (Result.Nodes.getNodeAs<clang::CXXConstructorDecl>("copy_constructor_tarjeta")){
		copy_constructor = true;
	}
  }

   void apply_copy_assignment_tarjeta(const MatchFinder::MatchResult &Result){
	if (Result.Nodes.getNodeAs<clang::CXXMethodDecl>("copy_assignment_tarjeta")){
		copy_assignment = true;
	}
  }

  void apply_copy_constructor_usuario(const MatchFinder::MatchResult &Result){
	if (Result.Nodes.getNodeAs<clang::CXXConstructorDecl>("copy_constructor_usuario")){
		copy_constructor = true;
	}
  }

  void apply_copy_assignment_usuario(const MatchFinder::MatchResult &Result){
	if (Result.Nodes.getNodeAs<clang::CXXMethodDecl>("copy_assignment_usuario")){
		copy_assignment = true;
	}
  }*/

  void apply_one_constructor(const MatchFinder::MatchResult &Result){
        if (Result.Nodes.getNodeAs<clang::CXXConstructorDecl>("one_constructor")){
		one_constructor++;
        }
  }

  void apply_busqueda_cstring(const MatchFinder::MatchResult &Result){
        if (const FunctionDecl *FS = Result.Nodes.getNodeAs<clang::FunctionDecl>("method_cstring")){
                FullSourceLoc FullLocation1 = Context->getFullLoc(FS->getLocStart());

                if (FullLocation1.isValid() ){
                        //Si la cabecera es string.h, con esto vale. Pero si es cstring, lo que te encuentra este fullLocation es la posición de string.h 
                        //dentro de cstring.h. Por eso hay que discernir en qué situación nos encontramos y si estamos en la segunda, buscar una nueva
                        //localización
                        FullSourceLoc FullLocation2 = Context->getFullLoc(
                                                                Context->getSourceManager().getIncludeLoc(FullLocation1.getFileID())
                                                        );

                        if(FullLocation2.isValid()){
                                if( string(Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName()).find("cstring") != std::string::npos){
                                        FullLocation2 = Context->getFullLoc(
                                                                Context->getSourceManager().getIncludeLoc(FullLocation2.getFileID())
                                                        );
                                }
                        }

                        if(!FullLocation2.isValid() || Context->getSourceManager().isInSystemHeader(FullLocation2)){
                                cstring = false;
                        }
                }
        }
  }

  void apply_friend(const MatchFinder::MatchResult &Result){
	if (const CXXRecordDecl *FS = Result.Nodes.getNodeAs<clang::CXXRecordDecl>("friend_class")){

		FullSourceLoc FullLocation1 = Context->getFullLoc(FS->getLocStart());

		if (FullLocation1.isValid() 
			&& !Context->getSourceManager().isInSystemHeader(FullLocation1) 
		){
                        string file = Context->getSourceManager().getFilename(FullLocation1);
                        if((isFileArticulo() && file.find("articulo.h") != std::string::npos) ||
                           (isFileUsuario() && file.find("usuario.h") != std::string::npos) ||
                           (isFileTarjeta() && file.find("tarjeta.h") != std::string::npos))
                        {
                        //llvm::outs () <<"Friend member: " << FS->getNameAsString() << " \n";
                        friend_member = true;
                        }
		}
	}
  } 

  void apply_acceso_atributo(const MatchFinder::MatchResult &Result){ 
	if (const FieldDecl *FS = Result.Nodes.getNodeAs<clang::FieldDecl>("field_decl")){
		FullSourceLoc FullLocation1 = Context->getFullLoc(FS->getLocStart());

                if (FullLocation1.isValid()
                        && !Context->getSourceManager().isInSystemHeader(FullLocation1)
                ){
			//Pare evitar que informe dos veces del mismo fallo al estar varias cabeceras incluidas unas en otras, 
			//tengo que comprobar qué fichero se está analizando
			string file = Context->getSourceManager().getFilename(FullLocation1);
			if((isFileArticulo() && file.find("articulo.h") != std::string::npos) ||
			   (isFileUsuario() && file.find("usuario.h") != std::string::npos) ||
			   (isFileTarjeta() && file.find("tarjeta.h") != std::string::npos))
			{
				//llvm::outs() << FS->getNameAsString() << "\n";
				if(FS->getAccess() != AS_private){
					atributo_no_privado = true;
				}
			}
		}
	}
  }

  void apply_friend_operator(const MatchFinder::MatchResult &Result){
	if (/*const FunctionDecl *FS = */Result.Nodes.getNodeAs<clang::FunctionDecl>("friend_operator_usuario")){
		//llvm::outs() << "Entro friend operator\n";
		friend_operator_usuario = true;
	}
  }

  bool isFileArticulo(){
	return clase == "Articulo";
  }

  bool isFileTarjeta(){
	return clase == "Tarjeta";
  }

  bool isFileUsuario(){
	return clase == "Usuario";
  }

  bool clase_encontrada;
  //bool copy_constructor;
  //bool copy_assignment;
  unsigned one_constructor;
  bool cstring;
  bool friend_member;
  bool atributo_no_privado;
  bool friend_operator_usuario;

  string clase;
  ASTContext *Context;
  Rewriter Rewrite;
};	

list<string> cabeceras_leidas(string file_name, string orden){

  int res = system(orden.c_str());
  ifstream read_file;

  read_file.open(file_name.c_str(), std::ifstream::in);
  list<string> lstr;

  if (read_file.is_open() && res ==0) {
        string s;
        getline(read_file, s);

        while (! read_file.eof()) {
                if(s != ""){
                        std::size_t first = s.find_first_not_of(' ');
                        s = s.substr(first);
                        lstr.push_back(string("-isystem" + s));
                }
                getline(read_file, s);
        }
        read_file.close();
  }
  return lstr;
}

static llvm::cl::OptionCategory MyToolCategory("compra_check options");

int main(int argc, const char **argv) {

  string option = argv[1];

  if(option.compare("--help") == 0){
	llvm::outs() << "Comando: ./compra_check articulo.cpp tarjeta.cpp usuario.cpp -- -std=c++11\n";
	exit(EXIT_SUCCESS);
  }

  int fixed = 0;
  for(int i = 2; i < argc; i++){	//argv[0] is "mucpp" and argv[1] is the option, so we begin in 2
	string arg = argv[i];
	if(arg.compare("--")==0){
		fixed = argc - i;
		break;		
	}
  }
 
  string file= "";
  unsigned startSources = 1;
  list<string> listSources;
  list<string>::iterator it;

  while(argc - fixed > int(startSources)){
	file = (string(argv[startSources]));
	
	it = find(listSources.begin(), listSources.end(), file);
	if(listSources.empty() || it == listSources.end()){
		listSources.push_back(file);
	}

	startSources++;
  }

  string file_name = "compra_check.tmp";
  string orden =  "echo | clang -E -v -x c++ - 2>&1 | sed -n '/<...> search starts here/,/End of search list./p' | sed 's/End of search list.//g' | sed 's/#include <...> search starts here://g' >" + file_name;

  list<string> lstr = cabeceras_leidas(file_name, orden);

  orden =  "echo | LANG=C cpp -v -x c++ - 2>&1 | sed -n '/<...> search starts here/,/End of search list./p' | sed 's/End of search list.//g' | sed 's/#include <...> search starts here://g' >" + file_name;

  list<string> lstr_clang = cabeceras_leidas(file_name, orden);
  lstr.insert(lstr.end(), lstr_clang.begin(), lstr_clang.end());

  for(auto pos = lstr.begin(); pos != lstr.end(); pos++){
        argv[argc] = (*pos).c_str();
        //llvm::outs() << argv[argc] << " ";
        argc++;
  }

  //for(int i=0; i< argc; i++)
  //    llvm::outs() << argv[i] << " ";

  orden = "rm " + file_name  + " > /dev/null 2>&1";

  system(orden.c_str());
 
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory); 
  bool sin_fallos;
	
  for(auto pos = listSources.begin(); pos != listSources.end(); pos++){
	CompraCheck FC;	
	ClangTool Tool(OptionsParser.getCompilations(), *pos);
	MatchFinder FinderClase;
	MatchFinder Finder;
	string clase = "";

	//General
	Finder.addMatcher(Funciones_Estandar_Matcher, &FC);
	Finder.addMatcher(Friend_Matcher, &FC);
	Finder.addMatcher(Private_Fields_Matcher, &FC);

	if(*pos == "articulo.cpp"){
		FinderClase.addMatcher(Clase_Articulo_Matcher, &FC);
		clase = "Articulo";
		FC.setClase(clase);
		Tool.run(newFrontendActionFactory(&FinderClase).get());

		llvm::outs() << "* articulo.cpp:\n";

		if(FC.is_clase_encontrada()){
			sin_fallos = true;

			Tool.run(newFrontendActionFactory(&Finder).get());
		}
		else
			llvm::outs() << "No se ha encontrado la clase 'Artículo'\n";
	}
	else if(*pos == "tarjeta.cpp"){
		FinderClase.addMatcher(Clase_Tarjeta_Matcher, &FC);
		clase = "Tarjeta";
		FC.setClase(clase);
		Tool.run(newFrontendActionFactory(&FinderClase).get());

		llvm::outs() << "* tarjeta.cpp:\n";
		
		if(FC.is_clase_encontrada()){
			sin_fallos = true;
// 			Finder.addMatcher(Copy_Constructor_Tarjeta_Matcher, &FC);
//			Finder.addMatcher(Copy_Assignment_Tarjeta_Matcher, &FC);

			Tool.run(newFrontendActionFactory(&Finder).get());
		
/*			if(!FC.tiene_delete_copy_constructor()){
				sin_fallos = false;
				llvm::outs() << "Revisa el enunciado respecto a la copia de objetos.\n";
			}	*/
		}
		else
			llvm::outs() << "No se ha encontrado la clase 'Tarjeta'\n";
	}
	else if(*pos == "usuario.cpp"){
		FinderClase.addMatcher(Clase_Usuario_Matcher, &FC);
		clase = "Usuario";
		FC.setClase(clase);
		Tool.run(newFrontendActionFactory(&FinderClase).get());

		llvm::outs() << "* usuario.cpp:\n";
		
		if(FC.is_clase_encontrada()){

			sin_fallos = true;
// 			Finder.addMatcher(Copy_Constructor_Usuario_Matcher, &FC);
//			Finder.addMatcher(Copy_Assignment_Usuario_Matcher, &FC);
			Finder.addMatcher(One_Constructor_Usuario_Matcher, &FC);
			Finder.addMatcher(Friend_Operator_Usuario_Matcher, &FC);

			Tool.run(newFrontendActionFactory(&Finder).get());

/*			if(!FC.tiene_delete_copy_constructor()){
				sin_fallos = false;
				llvm::outs() << "Revisa el enunciado respecto a la copia de objetos.\n";
			}
*/
			if(!FC.tiene_one_constructor()){
				sin_fallos = false;
                                llvm::outs() << "Revisa el enunciado respecto a la construcción de objetos.\n";
			}

			if(!FC.tiene_friend_operator_usuario()){
				sin_fallos = false;
				llvm::outs() << "Revisa el enunciado respecto al operador de inserción.\n";
			}
		}
		else
			llvm::outs() << "No se ha encontrado la clase 'Usuario'\n";
	}
	
	//General
	if(FC.is_clase_encontrada()){
		//llvm::outs() << "-------------\n";
		if(!FC.encuentra_cstring()){
        		sin_fallos = false;
                	llvm::outs() << "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...\n";
		}

		if(FC.existe_member_friend()){
			sin_fallos = false;
			llvm::outs() << "Revisa por qué es necesario incluir 'friend'.\n";
		}
	
		if(FC.tiene_atributo_no_privado()){
                        sin_fallos = false;
                        llvm::outs() << "Revisa el acceso a los atributos.\n";
		}

		if(sin_fallos)
                                llvm::outs() << "Verificación correcta de la clase " << clase  << ".\n";
	}
	//if(sin_fallos)
        //	llvm::outs() << "Verificación completa de compra.\n";
  }

  exit(EXIT_SUCCESS);
}
