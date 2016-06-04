/* $Id: cadena_check.cpp 293 2016-03-04 20:02:42Z gerardo $
 * Pruebas estáticas de código fuente para la clase Cadena de P0
 */
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
#include <stdlib.h>

using namespace clang::tooling;
using namespace llvm;

using namespace clang;
using namespace clang::ast_matchers;

using namespace std;

namespace clang{
  namespace ast_matchers{
    
    //Zona para definir matchers respecto a métodos incluidos en las clases.
    
    AST_MATCHER(clang::CXXConstructorDecl, isDefaultConstructor)
    {
      return Node.isDefaultConstructor();
    }
    
    AST_MATCHER(clang::CXXConstructorDecl, isCopyConstructor) {
      return Node.isCopyConstructor();
    }

    AST_MATCHER(clang::CXXRecordDecl, hasCopyConstructorWithConstParam) {
      return Node.hasCopyConstructorWithConstParam();
    }

    AST_MATCHER(clang::CXXMethodDecl, isImplicitMethod) {
      return Node.isImplicit();
    }

    AST_MATCHER(clang::FunctionDecl, isImplicitFunction) {
      return Node.isImplicit();
    }		
	
    AST_MATCHER(clang::CXXDestructorDecl, isImplicitDestructor) {
      return Node.isImplicit();
    }
  }
}

/*****************************************************************************/

DeclarationMatcher Clase_Cadena_Matcher =
  recordDecl(
    hasName("Cadena")
    ).bind("clase_cadena");

DeclarationMatcher Destructor_Matcher =
  destructorDecl(
    hasDescendant(
      deleteExpr(has(memberExpr(hasDeclaration(fieldDecl())))).bind("destructor")
      ),
    unless(isImplicitDestructor()),
    ofClass(
      recordDecl(
	hasName("Cadena"),
	unless(isTemplateInstantiation())
	)
      )
    );

//Buscar constructor predeterminado:
//- Que tenga tres parámetros y el primer parámetro por defecto (los demás lo serán por tanto).
//- Que utilice lista de inicialización

DeclarationMatcher Default_Constructor_Matcher =
  recordDecl(
    has( 
      constructorDecl(
	isDefaultConstructor(),
	unless(isImplicit())
	).bind("default_constructor")
      ),
    hasName("Cadena"), 
    unless(isTemplateInstantiation())
    );

DeclarationMatcher Function_Inline_Matcher =
  recordDecl(
    forEachDescendant( 
      methodDecl(
	unless(isImplicitMethod())
	).bind("method_inlined")
      ),
    hasName("Cadena"), 
    unless(isTemplateInstantiation())
    );

/*
  DeclarationMatcher Metodo_Observador_Matcher =
  recordDecl(
  forEachDescendant( 
  methodDecl(
  unless(isImplicitMethod())
  ).bind("metodo_observador")
  ),
  hasName("Cadena"), 
  unless(isTemplateInstantiation())
  );
*/
DeclarationMatcher Metodo_Noexcept_Matcher =
  recordDecl(
    forEachDescendant( 
      methodDecl(
	unless(isImplicitMethod())
	).bind("metodo_noexcept")
      ),
    hasName("Cadena"), 
    unless(isTemplateInstantiation())
    );

DeclarationMatcher Variable_New_Matcher =
  functionDecl(
    unless(isImplicitFunction()),
    forEachDescendant(varDecl(has(newExpr())).bind("variable_new"))
    );

DeclarationMatcher Variable_Delete_Matcher =
  functionDecl(
    unless(isImplicitFunction()),
    forEachDescendant(deleteExpr(has(declRefExpr(to(varDecl().bind("variable_delete"))))))
    ); 

DeclarationMatcher Reserva_Memoria_Matcher =
  functionDecl(
    unless(isImplicitFunction()),
    forEachDescendant(
      declRefExpr(
	to(
	  functionDecl(
	    anyOf(
	      hasName("malloc"),
	      hasName("calloc"),
	      hasName("realloc"),
	      hasName("free")
	      )
	    ).bind("method_stdlib")
	  )
	)
      )
    );

DeclarationMatcher Throw_Matcher = 
  functionDecl(
    unless(isImplicitFunction()),
    hasDescendant(
      throwExpr(
	forEachDescendant(
	  constructExpr(
	    hasDeclaration(
	      methodDecl(
		ofClass(
		  recordDecl(
		    anyOf(
		      hasName("std::out_of_range"),
		      hasName("out_of_range")
		      )
		    ).bind("record_throw")
		  )
		)
	      )
	    )
	  )
	).bind("throw_expr")
      )
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
	      hasName("strcpy")
	      )
	    ).bind("method_cstring")
	  )
	)
      )
    );

	
/*****************************************************************************/

class CadenaCheck : public MatchFinder::MatchCallback {
public :
  CadenaCheck(): clase_encontrada(false), default_constructor(false), explicit_specified(false), initialization_list(false), 
		 cadena_destruida(false), stdexcept(false), cstring(true), reserva_stdlib(false)  { 
    //Métodos inline
    inlines.insert(pair<string, bool>("~Cadena", false));
    inlines.insert(pair<string, bool>("operator const char *", false));
    inlines.insert(pair<string, bool>("length", false));
    inlines.insert(pair<string, bool>("operator[]", false));
    inlines.insert(pair<string, bool>("operator+=", false));

    //observadores.insert(pair<string, bool>("operator[]", false));
    //observadores.insert(pair<string, bool>("at", false));
    //observadores.insert(pair<string, bool>("length", false));

    noexcepts.insert(pair<string, bool>("operator[]", false));
    noexcepts.insert(pair<string, bool>("operator[]", false));
  }

  virtual void run(const MatchFinder::MatchResult &Result) {
    Context = Result.Context;
    Rewrite.setSourceMgr(Context->getSourceManager(), Context->getLangOpts());

    if(!clase_encontrada)
      apply_clase(Result);
    else{
      apply_default_constructor(Result);
      apply_methods_inlined(Result);
      //apply_metodos_observadores(Result);
      apply_metodos_noexcept(Result);
      apply_busqueda_stdexcept(Result);
      apply_busqueda_cstring(Result);
      apply_destruye_cadena(Result);
      apply_variables_liberadas(Result);
      apply_reserva_stdlib(Result);
    }
  }
  
  bool is_clase_encontrada(){
    return clase_encontrada;
  }
  
  bool tiene_default_constructor(){
    return default_constructor;
  }

  bool is_explicit_specified(){
    return explicit_specified;
  }

  bool tiene_initialization_list(){
    return initialization_list;
  }

  bool todas_functions_inline(){
    for (map<string, bool>::iterator it=inlines.begin(); it!=inlines.end(); it++){
      if( !(it->second) )
	return false;    
    }
    return true;
  }

  bool valida_metodos_noexcept(){
    for (multimap<string, bool>::iterator it=noexcepts.begin(); it!=noexcepts.end(); it++){
      if( !(it->second) )
	return false;    
    }
    return true;
  }

  bool destruye_cadena(){
    return cadena_destruida;
  }

  bool todas_variables_liberadas(){
    for (map<const VarDecl*, bool>::iterator it=variables_new.begin(); it!=variables_new.end(); it++){
      if( !(it->second) )
	return false;    
    }
    return true;
  }
  
  bool encuentra_stdexcept(){
    return stdexcept;
  }

  bool encuentra_cstring(){
    return cstring;
  }

  bool reserva_memoria_stdlib(){
    return reserva_stdlib;
  }

private:
  void apply_clase(const MatchFinder::MatchResult &Result){
	
    if (Result.Nodes.getNodeAs<clang::CXXRecordDecl>("clase_cadena")){
      clase_encontrada = true;
    }
  }

  void apply_default_constructor(const MatchFinder::MatchResult &Result){
		
    //Solo entrara para la declaración de la clase, pero no para redeclaraciones fuera de la clase
    if (const CXXConstructorDecl *FS = Result.Nodes.getNodeAs<clang::CXXConstructorDecl>("default_constructor")){

      if(FS->getNumParams() == 2 && FS->getParamDecl(0)->hasDefaultArg()){
	default_constructor = true;
      }

      if(FS->isExplicitSpecified()){
	explicit_specified = true;
      }

      //Así tomamos la definición para hacer la comprobación de los inicializadores
      const CXXConstructorDecl *FS2;
      if((CXXConstructorDecl*)FS->getMostRecentDecl() != NULL){
	FS2 = (CXXConstructorDecl*)FS->getMostRecentDecl();
      }
      else
	FS2 = FS;
	
      //llvm::outs() << FS2->getNumCtorInitializers() << "\n";
      if(FS2->getNumCtorInitializers() >= 1){
	initialization_list = true;
      }
    }
  }

  void apply_methods_inlined(const MatchFinder::MatchResult &Result){
		
    if (const CXXMethodDecl *FS = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("method_inlined")){
		
      //Así tomamos la definición para hacer la comprobación de si es inline
      const CXXMethodDecl *FS2;
      if((CXXMethodDecl*)FS->getMostRecentDecl() != NULL){
	FS2 = (CXXMethodDecl*)FS->getMostRecentDecl();
      }
      else
	FS2 = FS;
				
      if(FS2->isInlined()){
	//llvm::outs() << "Nombre del método inline: " << FS->getNameAsString() << "\n";
	map<string, bool>::iterator it;
	if( (it = inlines.find(FS->getNameAsString())) != inlines.end() ){
	  it->second = true;
	}
      }
    }
  }

  /* void apply_metodos_observadores(const MatchFinder::MatchResult &Result){
		
     if (const CXXMethodDecl *FS = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("metodo_observador")){
     //llvm::outs() << "Nombre : "<< FS->getNameAsString() << "\n";
     if(FS->isConst()){
     map<string, bool>::iterator it;
     if( (it = observadores.find(FS->getNameAsString())) != observadores.end() ){
     it->second = true;
     }
     }
     }
     }*/

  void apply_metodos_noexcept(const MatchFinder::MatchResult &Result){
		
    if (const CXXMethodDecl *FS = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("metodo_noexcept")){
      //Haciendo esto con un multimap, estamos permitiendo que la versión constante y no constante puedan tener un comportamiento distinto (aunque no es lo habitual)
      //Otra opción podría haber sido usar un segundo argumetno "int" en vez de bool, en el que finalmente esperemos un número "2" correspondiente a ambos métodos. 
      for (multimap<string, bool>::iterator it=noexcepts.begin(); it!=noexcepts.end(); it++){	
	if(FS->getNameAsString() == it->first){
	  //llvm::outs() << "Entro en noexcept\n";
	  const FunctionProtoType *FP = FS->getType()->castAs<FunctionProtoType>();
	  if(FP && FP->isNothrow(*Context) && !it->second){
	    it->second = true;
	    break;
	  }
	}
      }
    }
  }
 
  void apply_busqueda_stdexcept(const MatchFinder::MatchResult &Result){
	
    if (const CXXThrowExpr *FS = Result.Nodes.getNodeAs<clang::CXXThrowExpr>("throw_expr")){
		
      FullSourceLoc FullLocation1 = Context->getFullLoc(FS->getLocStart());
      const CXXRecordDecl *RD = Result.Nodes.getNodeAs<clang::CXXRecordDecl>("record_throw");
      FullSourceLoc FullLocation2 = Context->getFullLoc(RD->getLocStart());

      if (FullLocation1.isValid() 
	  && !Context->getSourceManager().isInSystemHeader(FullLocation1) 
	){
			
	//Vamos a buscar el location de la cabecera a través de la cual se introduce la excepción out-of-range.
	//Si está en una cabecera del sistema, quiere decir que el #include<stdexcept> está dentro de otra cabecera
	//del sistema y no en el fichero cadena.cpp o cadena.h. Otra opción es comprobar directamente si 
	//el "getFilename" es cadena.h o cadena.cpp.
	FullSourceLoc FullLocation3 = Context->getFullLoc(
	  Context->getSourceManager().getIncludeLoc(FullLocation2.getFileID())
	  );

	//llvm::outs() << Context->getSourceManager().getFilename(FullLocation3) <<"-" << FullLocation3.getSpellingLineNumber() << "\n";
	
	if(FullLocation3.isValid() 
	   && !Context->getSourceManager().isInSystemHeader(FullLocation3) 
	  ){
	  stdexcept = true;
	}
	/*std::pair<SourceLocation, SourceLocation> inc_pair = Context->getSourceManager().getExpansionRange(inc);
	  SourceRange inc_r = SourceRange(inc_pair.first, inc_pair.second);	
	  llvm::outs() << "entrado aquí\n" << Rewrite.getRewrittenText(inc_r) << "\n";		
	  if(Rewrite.getRewrittenText(inc_r) == "stdexcept"){
	  stdexcept = true;
	  }*/

	/*llvm::outs() << Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName() << "\n";
	  string::size_type p = Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName().rfind('/');
	  llvm::outs() <<string(file.begin()+p+1, file.end()) << "\n";*/

	/*if( string(Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName()).find("stdexcept") != std::string::npos){
	  stdexcept = true;
	  }*/
      }
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

//			llvm::outs() << Context->getSourceManager().getFilename(FullLocation2) <<"-" << FullLocation2.getSpellingLineNumber() << "\n";

	if(!FullLocation2.isValid() || Context->getSourceManager().isInSystemHeader(FullLocation2) 
	  ){
	  cstring = false;
	}	
      }
    }
  }

  void apply_destruye_cadena(const MatchFinder::MatchResult &Result){
	
    if (const CXXDeleteExpr *FS = Result.Nodes.getNodeAs<clang::CXXDeleteExpr>("destructor")){
	
      if(FS->isArrayForm()){
	cadena_destruida = true;
	/*if(llvm::isa<MemberExpr>(FS->getArgument())){
	  llvm::outs() << "Aqui tambien\n";
	  const MemberExpr *me = (MemberExpr *)(FS->getArgument());
	  if(me->getMemberDecl()->getName() == "s_"){
	  cadena_destruida = true;
	  llvm::outs() << "Aqui ya conseguido\n";
	  }
	  }*/	
      }
    }
  }

  void apply_variables_liberadas(const MatchFinder::MatchResult &Result){

    if (const VarDecl *FS = Result.Nodes.getNodeAs<clang::VarDecl>("variable_new")){

      FullSourceLoc FullLocation = Context->getFullLoc(FS->getLocStart());
      		
      if (FullLocation.isValid() 
	  && !Context->getSourceManager().isInSystemHeader(FullLocation) 
	){
	bool found = false;
	for (map<const VarDecl*, bool>::iterator it=variables_new.begin(); it!=variables_new.end(); it++){	
	  if( it->first->getCanonicalDecl() == FS->getCanonicalDecl() ){				
	    found = true;
	    break;	
	  }
	}

	if(!found){
	  //llvm::outs() << "entro en new para: " << FS->getNameAsString() << "\n";
	  variables_new.insert(pair<const VarDecl*, bool>(FS, false));
	}
      }
    }

    if (const VarDecl *FS = Result.Nodes.getNodeAs<clang::VarDecl>("variable_delete")){

      FullSourceLoc FullLocation = Context->getFullLoc(FS->getLocStart());
      		
      if (FullLocation.isValid() 
	  && !Context->getSourceManager().isInSystemHeader(FullLocation) 
	){
	for (map<const VarDecl*, bool>::iterator it=variables_new.begin(); it!=variables_new.end(); it++){	
	  if( it->first->getCanonicalDecl() == FS->getCanonicalDecl() ){
	    //llvm::outs() << "entro en delete para: " << FS->getNameAsString() << "\n";
	    it->second = true;
	  }
	}
      }
    }
  }

  void apply_reserva_stdlib(const MatchFinder::MatchResult &Result){
	
    if (const FunctionDecl *FS = Result.Nodes.getNodeAs<clang::FunctionDecl>("method_stdlib")){

      FullSourceLoc FullLocation = Context->getFullLoc(FS->getLocStart());

      if (FullLocation.isValid()){
	/*SourceLocation inc = Context->getSourceManager().getIncludeLoc(FullLocation2.getFileID());
	
	  std::pair<SourceLocation, SourceLocation> inc_pair = Context->getSourceManager().getExpansionRange(inc);
	  SourceRange inc_r = SourceRange(inc_pair.first, inc_pair.second);	
	  llvm::outs() << "entrado aquí\n" << Rewrite.getRewrittenText(inc_r) << "\n";		
	  if(Rewrite.getRewrittenText(inc_r) == "stdexcept"){
	  stdexcept = true;
	  }*/

	/*llvm::outs() << Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName() << "\n";
	  string::size_type p = Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName().rfind('/');

	  llvm::outs() <<string(file.begin()+p+1, file.end()) << "\n";*/
	//llvm::outs() << string(Context->getSourceManager().getFileEntryForID(FullLocation.getFileID())->getName()) << "\n";
	if( string(Context->getSourceManager().getFileEntryForID(FullLocation.getFileID())->getName()).find("stdlib") != std::string::npos){
	  reserva_stdlib = true;
	}
      }
    }
  }
 
  bool clase_encontrada;
  bool default_constructor;
  bool explicit_specified;
  bool initialization_list;
  bool cadena_destruida;
  map<string, bool> inlines;
//  map<string, bool> observadores;
  multimap<string, bool> noexcepts;
  map<const VarDecl*, bool> variables_new; //Necesario ponerlo como VarDecl ya que puede haber varias variables con el mismo nombre en distintas funciones
  bool stdexcept; 
  bool cstring;		//Inicializar a true ya que puede que no se utilice. 
  bool reserva_stdlib;

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

static llvm::cl::OptionCategory MyToolCategory("cadena_check options");

int main(int argc, const char **argv) {

  string option = argv[1];

  if(option.compare("--help") == 0){
    llvm::outs() << "Comando: ./cadena_check cadena.cpp -- -std=c++11\n";
    exit(EXIT_SUCCESS);
  }

  string file_name = "cadena_check.tmp";
  string orden =  "echo | LANG=C cpp -v -x c++ - 2>&1 | sed -n '/<...> search starts here/,/End of search list./p' | sed 's/End of search list.//g' | sed 's/#include <...> search starts here://g' >" + file_name;

  list<string> lstr = cabeceras_leidas(file_name, orden);

  orden =  "echo | clang -E -v -x c++ - 2>&1 | sed -n '/<...> search starts here/,/End of search list./p' | sed 's/End of search list.//g' | sed 's/#include <...> search starts here://g' >" + file_name;
  
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
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  bool sin_fallos = true;

  CadenaCheck FC;
  MatchFinder FinderClase;
  //Incluir aquí los matchers. Si es más de uno, repetir la sentencia modificando adecuadamente el nombre del matcher
  FinderClase.addMatcher(Clase_Cadena_Matcher, &FC);
  
  Tool.run(newFrontendActionFactory(&FinderClase).get());

  if(FC.is_clase_encontrada()){
	
    MatchFinder Finder;
    Finder.addMatcher(Destructor_Matcher, &FC);
    Finder.addMatcher(Default_Constructor_Matcher, &FC);
    Finder.addMatcher(Function_Inline_Matcher, &FC);
    //Finder.addMatcher(Metodo_Observador_Matcher, &FC);
    Finder.addMatcher(Metodo_Noexcept_Matcher, &FC);
    Finder.addMatcher(Throw_Matcher, &FC);
    Finder.addMatcher(Funciones_Estandar_Matcher, &FC);
    Finder.addMatcher(Variable_New_Matcher, &FC);
    Finder.addMatcher(Variable_Delete_Matcher, &FC);
    Finder.addMatcher(Reserva_Memoria_Matcher, &FC);

    Tool.run(newFrontendActionFactory(&Finder).get());
	
    if(!FC.tiene_default_constructor()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto a la construcción de objetos.\n";
    }

    if(sin_fallos && !FC.is_explicit_specified()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto a conversiones implícitas.\n";
    }

    if(sin_fallos && !FC.tiene_initialization_list()){
      //Este if es especial, porque si no encontrase el constructor por defecto porque el primer parámetro no es "default", entonces no entraría en el método
      //y no podría revisar la lista de inicialización. En definitiva, que en este if el "sin_fallos" se debería poner siempre.
      sin_fallos = false;
      llvm::outs() << "Revisa la inicialización de los atributos.\n";
    }

    if(FC.reserva_memoria_stdlib()){
      sin_fallos = false;
      llvm::outs() << "Revisa qué funciones han de ser usadas para la asignación y liberación de memoria de variables.\n";
    }

    if(!FC.destruye_cadena()){
      sin_fallos = false;
      llvm::outs() << "Revisa el destructor de la clase.\n";
    }

    if(!FC.todas_variables_liberadas()){
      sin_fallos = false;
      llvm::outs() << "Revisa la asignación y liberación de memoria de variables.\n";
    }

    /*if(!FC.todas_functions_inline()){
      sin_fallos = false;
      llvm::outs() << "Revisa qué funciones deben ser marcadas inline.\n";
      }*/

    /*if(sin_fallos && !FC.valida_metodos_observadores()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto a los métodos que son observadores.\n";
      }*/

    if(!FC.valida_metodos_noexcept()){
      sin_fallos = false;
      llvm::outs() << "Revisa qué funciones no deben lanzar excepciones.\n";
    }

    if(!FC.encuentra_stdexcept()){
      sin_fallos = false;
      llvm::outs() << "Revisa de dónde son tomadas las excepciones.\n";
    }

    if(!FC.encuentra_cstring()){
      sin_fallos = false;
      llvm::outs() << "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...\n";
    }

    if(sin_fallos)
      llvm::outs() << "Verificación correcta de la clase Cadena.\n";
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Cadena'\n";

  exit(EXIT_SUCCESS);
}
