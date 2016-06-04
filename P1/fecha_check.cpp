// $Id: fecha_check.cpp 293 2016-03-04 20:02:42Z gerardo $
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

    AST_MATCHER(clang::FunctionDecl, isDefaulted) {
      return Node.isDefaulted();
    }
  }
}

/*****************************************************************************/

DeclarationMatcher Clase_Fecha_Matcher =
  recordDecl(
    hasName("Fecha")
    ).bind("clase_fecha");

DeclarationMatcher Copy_Constructor_Matcher =
  recordDecl(
//		hasCopyConstructorWithConstParam(),
    has( 
      constructorDecl(
	isCopyConstructor(),
	unless(isDefaulted()),
	unless(isImplicit())
	).bind("copy_constructor")
      ),
    hasName("Fecha"),
    unless(isTemplateInstantiation())
    );

//Buscar constructor predeterminado:
//- Que tenga 3 parámetros y el 1.º por defecto (los demás lo serán por tanto).
//- Que utilice lista de inicialización

DeclarationMatcher Default_Constructor_Matcher =
  recordDecl(
    has( 
      constructorDecl(
	isDefaultConstructor(),
	unless(isImplicit())
	).bind("default_constructor")
      ),
    hasName("Fecha"), 
    unless(isTemplateInstantiation())
    );

DeclarationMatcher Function_Inline_Matcher =
  recordDecl(
    forEachDescendant( 
      methodDecl(
	unless(isImplicitMethod())
	).bind("method_inlined")
      ),
    hasName("Fecha"), 
    unless(isTemplateInstantiation())
    );

DeclarationMatcher Overloaded_Compare_Matcher =
  functionDecl(
    anyOf(
      hasName("operator!="),
      hasName("operator>"),
      hasName("operator<="),
      hasName("operator>=")
      ),
    hasDescendant(
      operatorCallExpr(
	anyOf(
	  hasOverloadedOperatorName("=="),
	  hasOverloadedOperatorName("<")
	  )
	)
      )
    ).bind("overloaded_compare");

DeclarationMatcher Overloaded_Arithmetic_Matcher =
  methodDecl(
    anyOf(
      hasOverloadedOperatorName("-="),
      hasOverloadedOperatorName("+"),
      hasOverloadedOperatorName("-"),
      hasOverloadedOperatorName("++"),
      hasOverloadedOperatorName("--")
      ),
    unless(isImplicitMethod()),
    hasDescendant(
      operatorCallExpr(hasOverloadedOperatorName("+="))
      ),
    ofClass(
      recordDecl(
	hasName("Fecha"),
	unless(isTemplateInstantiation())
	)
      )
    ).bind("overloaded_arithmetic");

DeclarationMatcher Static_Const_Matcher =
  recordDecl(
    //Necesario aquí eachOf, ya que a lo que se le hace "bind" es a varDecl y si hiciésemos:
    //varDecl(
    //	anyOf(
    //		hasName("AnnoMinimo"),
    //		hasName("AnnoMaximo")
    //	)
    //).bind("static_const")
    //Solo recuperaría una variable, aquella que encontrase primero de entre AnnoMinimo y AnnoMaximo
    eachOf(	   	
      has(
	varDecl(
	  hasName("AnnoMinimo")
	  ).bind("static_const")
	),
      has(
	varDecl(
	  hasName("AnnoMaximo")
	  ).bind("static_const")
	)
      ),
    hasName("Fecha"), 
    unless(isTemplateInstantiation())
    );

DeclarationMatcher Funciones_Cstdio_Matcher =
  functionDecl(
    unless(isImplicitFunction()),
    forEachDescendant(
      declRefExpr(
	to(
	  functionDecl(
	    anyOf(
	      hasName("sscanf"),
	      hasName("sprintf")
	      )
	    ).bind("method_cstdio")
	  )
	)
      )
    );

/*****************************************************************************/

class FechaCheck : public MatchFinder::MatchCallback {
public :
  FechaCheck(): clase_encontrada(false), copy_constructor(false), 
		default_constructor(false), explicit_specified(false), 
		initialization_list(false), valida_AnnoMinimo(false), 
		valida_AnnoMaximo(false), cstdio(false)  { 
    //Métodos inline
    inlines.insert(pair<string, bool>("dia", false));
    inlines.insert(pair<string, bool>("mes", false));
    inlines.insert(pair<string, bool>("anno", false));
    inlines.insert(pair<string, bool>("Invalida", false));
    inlines.insert(pair<string, bool>("por_que", false));

    //Operadores de comparación
    operators_compare.insert(pair<string, bool>("operator!=", false));
    operators_compare.insert(pair<string, bool>("operator>", false));
    operators_compare.insert(pair<string, bool>("operator<=", false));
    operators_compare.insert(pair<string, bool>("operator>=", false));
	
    //Operadores aritméticos
    operators_arithmetic.insert(pair<string, bool>("operator-=", false));
    operators_arithmetic.insert(pair<string, bool>("operator+", false));
    operators_arithmetic.insert(pair<string, bool>("operator-", false));
    operators_arithmetic.insert(pair<string, bool>("operator--", false));
    operators_arithmetic.insert(pair<string, bool>("operator++", false));
  }

  virtual void run(const MatchFinder::MatchResult &Result) {
    Context = Result.Context;
    Rewrite.setSourceMgr(Context->getSourceManager(), Context->getLangOpts());

    if(!clase_encontrada)
      apply_clase(Result);
    else{
      apply_copy_constructor(Result);
      apply_default_constructor(Result);
      apply_methods_inlined(Result);
      apply_overloaded_arithmetic(Result);
      apply_overloaded_compare(Result);
      apply_constant_public(Result);
      apply_busqueda_cstdio(Result);
    }
  }
  
  bool is_clase_encontrada(){
    return clase_encontrada;
  }

  bool tiene_copy_constructor(){
    return copy_constructor;
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
    for (auto par : inlines)
      if (!par.second) return false;
    return true;
  }

  bool reutiliza_operators_arithmetic(){
    for (map<string, bool>::value_type par : operators_arithmetic)
      if (! par.second) return false;
    return true;
  }

  bool reutiliza_operators_compare(){
    for (map<string, bool>::value_type par : operators_compare)
      if( ! par.second) return false;    
    return true;
  }

  bool valida_constantes(){
    return valida_AnnoMinimo && valida_AnnoMaximo;
  }

  bool funciones_cstdio(){
    return cstdio;
  }

private:
  void apply_clase(const MatchFinder::MatchResult &Result){
	
    if (Result.Nodes.getNodeAs<clang::CXXRecordDecl>("clase_fecha")){
      clase_encontrada = true;
    }
  }
 
  void apply_copy_constructor(const MatchFinder::MatchResult &Result){
 
    if (Result.Nodes.getNodeAs<clang::CXXConstructorDecl>("copy_constructor")){
      copy_constructor = true;
    }
  }

  void apply_default_constructor(const MatchFinder::MatchResult &Result){
		
    //Solo entrara para la declaración de la clase, pero no para redeclaraciones fuera de la clase
    if (const CXXConstructorDecl *FS = Result.Nodes.getNodeAs<clang::CXXConstructorDecl>("default_constructor")){

      if(FS->getNumParams() == 3 && FS->getParamDecl(0)->hasDefaultArg()){
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
	
      if(FS2->getNumCtorInitializers() == 3){
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
				
      //llvm::outs() << "Nombre del método inline: " << FS->getNameAsString() << "\n";
      if(FS2->isInlined()){
	map<string, bool>::iterator it;
	if( (it = inlines.find(FS->getNameAsString())) != inlines.end() ){
	  it->second = true;
	}
      }
    }
  }

  void apply_overloaded_compare(const MatchFinder::MatchResult &Result){
    //Solo entrara para la definición, ya que en el matcher exigimos que use en el cuerpo "!=" o "<"
    if (const FunctionDecl *FS = Result.Nodes.getNodeAs<clang::FunctionDecl>("overloaded_compare")){
		
      FullSourceLoc FullLocation = Context->getFullLoc(FS->getLocStart());
      		
      if (FullLocation.isValid() 
	  && !Context->getSourceManager().isInSystemHeader(FullLocation) 
	){

	//llvm::outs() << "Nombre del método compare: " << FS->getNameAsString() << "\n";
	map<string, bool>::iterator it;
	if( (it = operators_compare.find(FS->getNameAsString())) != operators_compare.end() ){
	  it->second = true;
	}
      }
    }	
  }

  void apply_overloaded_arithmetic(const MatchFinder::MatchResult &Result){
		
    //Solo entrara para la definición, ya que en el matcher exigimos que use en el cuerpo "+="
    if (const CXXMethodDecl *FS = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("overloaded_arithmetic")){
		
      //llvm::outs() << "Nombre de la función: " << FS->getNameAsString() << "\n";
      map<string, bool>::iterator it;
      if( (it = operators_arithmetic.find(FS->getNameAsString())) != operators_arithmetic.end() ){
	it->second = true;
      }
    }
  }

  void apply_constant_public(const MatchFinder::MatchResult &Result){

    if (const VarDecl *FS1 = Result.Nodes.getNodeAs<clang::VarDecl>("static_const")){

      if(FS1->getType().getCanonicalType().isConstQualified() && FS1->isStaticDataMember()){

	if(FS1->getNameAsString() == "AnnoMinimo")
	  valida_AnnoMinimo = true;
	else
	  valida_AnnoMaximo = true;
      }
    }
  }

  void apply_busqueda_cstdio(const MatchFinder::MatchResult &Result){
	
    if (const FunctionDecl *FS = Result.Nodes.getNodeAs<clang::FunctionDecl>("method_cstdio")){

      FullSourceLoc FullLocation1 = Context->getFullLoc(FS->getLocStart());
      if (FullLocation1.isValid() ){
	FullSourceLoc FullLocation2 = Context->getFullLoc(
	  Context->getSourceManager().getIncludeLoc(FullLocation1.getFileID())
	  );
	if(FullLocation2.isValid()){
	  if( string(Context->getSourceManager().getFileEntryForID(FullLocation2.getFileID())->getName()).find("cstdio") != std::string::npos){
	    FullLocation2 = Context->getFullLoc(
	      Context->getSourceManager().getIncludeLoc(FullLocation2.getFileID())
	      );
	  }
	}

	// llvm::outs() << Context->getSourceManager().getFilename(FullLocation2) <<"-" << FullLocation2.getSpellingLineNumber() << "\n";

	if(!FullLocation2.isValid() || Context->getSourceManager().isInSystemHeader(FullLocation2)
	  ){
	  cstdio = false;
	}
      }
    }
  }


  bool clase_encontrada;
  bool copy_constructor;
  bool default_constructor;
  bool explicit_specified;
  bool initialization_list;
  map<string, bool> inlines;
  map<string, bool> operators_compare;
  map<string, bool> operators_arithmetic;
  bool valida_AnnoMinimo, valida_AnnoMaximo;
  bool cstdio;

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

static llvm::cl::OptionCategory MyToolCategory("fecha_check options");

int main(int argc, const char **argv) {

  string option = argv[1];

  if(option.compare("--help") == 0){
    llvm::outs() << "Comando: ./fecha_check fecha.cpp -- -std=c++11\n";
    exit(EXIT_SUCCESS);
  }

  string file_name = "fecha_check.tmp";
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

  FechaCheck FC;
  MatchFinder FinderClase;
  //Incluir aquí los matchers. Si es más de uno, repetir la sentencia modificando adecuadamente el nombre del matcher
  FinderClase.addMatcher(Clase_Fecha_Matcher, &FC);
  
  Tool.run(newFrontendActionFactory(&FinderClase).get());

  if(FC.is_clase_encontrada()){
	
    MatchFinder Finder;
    Finder.addMatcher(Copy_Constructor_Matcher, &FC);
    Finder.addMatcher(Default_Constructor_Matcher, &FC);
    Finder.addMatcher(Function_Inline_Matcher, &FC);
    Finder.addMatcher(Overloaded_Compare_Matcher, &FC);
    Finder.addMatcher(Overloaded_Arithmetic_Matcher, &FC);	
    Finder.addMatcher(Static_Const_Matcher, &FC);
    Finder.addMatcher(Funciones_Cstdio_Matcher, &FC);

    Tool.run(newFrontendActionFactory(&Finder).get());

    if(!FC.valida_constantes()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto a las constantes AnnoMinimo y AnnoMaximo.\n";
    }
	
    if(!FC.tiene_default_constructor()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto a la construcción de objetos.\n";
    }

    if(sin_fallos && !FC.is_explicit_specified()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto a conversiones implícitas.\n";
    }

    if(sin_fallos && !FC.tiene_initialization_list()){
      sin_fallos = false;
      llvm::outs() << "Revisa la inicialización de los atributos.\n";
    }

    if(FC.tiene_copy_constructor()){
      sin_fallos = false;
      llvm::outs() << "Revisa el enunciado respecto al constructor de copia.\n";
    }

    /*if(!FC.todas_functions_inline()){
      sin_fallos = false;
      llvm::outs() << "Revisa qué funciones deben ser marcadas inline.\n";
      }*/

    if(!FC.reutiliza_operators_compare()){
      sin_fallos = false;
      llvm::outs() << "Revisa los consejos sobre los operadores de comparación.\n";
    }

    if(!FC.reutiliza_operators_arithmetic()){
      sin_fallos = false;
      llvm::outs() << "Revisa los consejos sobre los operadores aritméticos.\n";
    }	

    if(FC.funciones_cstdio()){
      sin_fallos = false;
      llvm::outs() << "Revisa de dónde son tomadas las funciones ssprintf y sscanf.\n";
    }

    if(sin_fallos)
      llvm::outs() << "Verificación correcta de la clase Fecha.\n";
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Fecha'\n";

  exit(EXIT_SUCCESS);
}
