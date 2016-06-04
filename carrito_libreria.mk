##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=carrito_libreria
ConfigurationName      :=Debug
WorkspacePath          := "/home/zerokullneo/github/codelite/carrito_libreria"
ProjectPath            := "/home/zerokullneo/github/codelite/carrito_libreria"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jose M Barba Gonzalez
Date                   :=04/06/16
CodeLitePath           :="/home/zerokullneo/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="carrito_libreria.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lcrypt
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O1 -O -ansi -pedantic -W -std=c++14 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -ansi -pedantic -W -std=c99 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
INCLUDES  := -I${CADENADIR} -I${FECHADIR} -I${TESTHDR}
LOCALLIBS := ${CADENADIR}/cadena.o ${FECHADIR}/fecha.o ${LUHNDIR}/luhn.o
EXTLIBS   := -lcrypt
LIBS      := ${LOCALLIBS} ${EXTLIBS}
VPATH     := .:${CADENADIR}:${FECHADIR}
COMM_SRCS := usuario.cpp tarjeta.cpp articulo.cpp pedido.cpp \
pedido-articulo.cpp ${LUHNDIR}/luhn.cpp:=
COMM_HDRS := articulo.h pedido-articulo.h pedido.h tarjeta.h usuario.h \
usuario-pedido.h:=
MAIN_SRCS := test-caso4-consola.cpp
MAIN_OBJS := $(COMM_SRCS:.cpp=.o) $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  := test-caso4-consola
TEST_SRCS := test-caso0-cadena-auto.cpp test-caso0-fecha-auto.cpp \
test-caso1-auto.cpp test-caso3-auto.cpp test-caso4-auto.cpp test-auto.cpp:=
TEST_HDRS := test-auto.h ${TESTHDR}/fct.h
TEST_OBJS := $(COMM_SRCS:.cpp=.o) $(TEST_SRCS:.cpp=.o)
TEST_EXE  := test-p1_4-auto
SRCS := ${COMM_SRCS} ${TEST_SRCS} ${MAIN_SRCS}
HDRS := ${COMM_HDRS} ${TEST_HDRS}
NOMBRETAR := ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR := ${NOMBREALUMNO}/${NOMBREPRACTICA}
Objects0=$(IntermediateDirectory)/P4_articulo.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_tarjeta.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_usuario.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_pedido.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_pedido-articulo.cpp$(ObjectSuffix) $(IntermediateDirectory)/luhn.cpp$(ObjectSuffix) $(IntermediateDirectory)/P1_cadena.cpp$(ObjectSuffix) $(IntermediateDirectory)/P1_cadena_check.cpp$(ObjectSuffix) $(IntermediateDirectory)/P1_fecha.cpp$(ObjectSuffix) $(IntermediateDirectory)/P1_fecha_check.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/P1_test-P1-auto.cpp$(ObjectSuffix) $(IntermediateDirectory)/P1_test-P1-consola.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/P4_articulo.cpp$(ObjectSuffix): P4/articulo.cpp $(IntermediateDirectory)/P4_articulo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/articulo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_articulo.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_articulo.cpp$(DependSuffix): P4/articulo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_articulo.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_articulo.cpp$(DependSuffix) -MM "P4/articulo.cpp"

$(IntermediateDirectory)/P4_articulo.cpp$(PreprocessSuffix): P4/articulo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_articulo.cpp$(PreprocessSuffix) "P4/articulo.cpp"

$(IntermediateDirectory)/P4_tarjeta.cpp$(ObjectSuffix): P4/tarjeta.cpp $(IntermediateDirectory)/P4_tarjeta.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/tarjeta.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_tarjeta.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_tarjeta.cpp$(DependSuffix): P4/tarjeta.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_tarjeta.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_tarjeta.cpp$(DependSuffix) -MM "P4/tarjeta.cpp"

$(IntermediateDirectory)/P4_tarjeta.cpp$(PreprocessSuffix): P4/tarjeta.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_tarjeta.cpp$(PreprocessSuffix) "P4/tarjeta.cpp"

$(IntermediateDirectory)/P4_usuario.cpp$(ObjectSuffix): P4/usuario.cpp $(IntermediateDirectory)/P4_usuario.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/usuario.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_usuario.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_usuario.cpp$(DependSuffix): P4/usuario.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_usuario.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_usuario.cpp$(DependSuffix) -MM "P4/usuario.cpp"

$(IntermediateDirectory)/P4_usuario.cpp$(PreprocessSuffix): P4/usuario.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_usuario.cpp$(PreprocessSuffix) "P4/usuario.cpp"

$(IntermediateDirectory)/P4_pedido.cpp$(ObjectSuffix): P4/pedido.cpp $(IntermediateDirectory)/P4_pedido.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/pedido.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_pedido.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_pedido.cpp$(DependSuffix): P4/pedido.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_pedido.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_pedido.cpp$(DependSuffix) -MM "P4/pedido.cpp"

$(IntermediateDirectory)/P4_pedido.cpp$(PreprocessSuffix): P4/pedido.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_pedido.cpp$(PreprocessSuffix) "P4/pedido.cpp"

$(IntermediateDirectory)/P4_pedido-articulo.cpp$(ObjectSuffix): P4/pedido-articulo.cpp $(IntermediateDirectory)/P4_pedido-articulo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/pedido-articulo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_pedido-articulo.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_pedido-articulo.cpp$(DependSuffix): P4/pedido-articulo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_pedido-articulo.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_pedido-articulo.cpp$(DependSuffix) -MM "P4/pedido-articulo.cpp"

$(IntermediateDirectory)/P4_pedido-articulo.cpp$(PreprocessSuffix): P4/pedido-articulo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_pedido-articulo.cpp$(PreprocessSuffix) "P4/pedido-articulo.cpp"

$(IntermediateDirectory)/luhn.cpp$(ObjectSuffix): luhn.cpp $(IntermediateDirectory)/luhn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/luhn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/luhn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/luhn.cpp$(DependSuffix): luhn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/luhn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/luhn.cpp$(DependSuffix) -MM "luhn.cpp"

$(IntermediateDirectory)/luhn.cpp$(PreprocessSuffix): luhn.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/luhn.cpp$(PreprocessSuffix) "luhn.cpp"

$(IntermediateDirectory)/P1_cadena.cpp$(ObjectSuffix): P1/cadena.cpp $(IntermediateDirectory)/P1_cadena.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/cadena.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P1_cadena.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P1_cadena.cpp$(DependSuffix): P1/cadena.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P1_cadena.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P1_cadena.cpp$(DependSuffix) -MM "P1/cadena.cpp"

$(IntermediateDirectory)/P1_cadena.cpp$(PreprocessSuffix): P1/cadena.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P1_cadena.cpp$(PreprocessSuffix) "P1/cadena.cpp"

$(IntermediateDirectory)/P1_cadena_check.cpp$(ObjectSuffix): P1/cadena_check.cpp $(IntermediateDirectory)/P1_cadena_check.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/cadena_check.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P1_cadena_check.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P1_cadena_check.cpp$(DependSuffix): P1/cadena_check.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P1_cadena_check.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P1_cadena_check.cpp$(DependSuffix) -MM "P1/cadena_check.cpp"

$(IntermediateDirectory)/P1_cadena_check.cpp$(PreprocessSuffix): P1/cadena_check.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P1_cadena_check.cpp$(PreprocessSuffix) "P1/cadena_check.cpp"

$(IntermediateDirectory)/P1_fecha.cpp$(ObjectSuffix): P1/fecha.cpp $(IntermediateDirectory)/P1_fecha.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/fecha.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P1_fecha.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P1_fecha.cpp$(DependSuffix): P1/fecha.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P1_fecha.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P1_fecha.cpp$(DependSuffix) -MM "P1/fecha.cpp"

$(IntermediateDirectory)/P1_fecha.cpp$(PreprocessSuffix): P1/fecha.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P1_fecha.cpp$(PreprocessSuffix) "P1/fecha.cpp"

$(IntermediateDirectory)/P1_fecha_check.cpp$(ObjectSuffix): P1/fecha_check.cpp $(IntermediateDirectory)/P1_fecha_check.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/fecha_check.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P1_fecha_check.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P1_fecha_check.cpp$(DependSuffix): P1/fecha_check.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P1_fecha_check.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P1_fecha_check.cpp$(DependSuffix) -MM "P1/fecha_check.cpp"

$(IntermediateDirectory)/P1_fecha_check.cpp$(PreprocessSuffix): P1/fecha_check.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P1_fecha_check.cpp$(PreprocessSuffix) "P1/fecha_check.cpp"

$(IntermediateDirectory)/P1_test-P1-auto.cpp$(ObjectSuffix): P1/test-P1-auto.cpp $(IntermediateDirectory)/P1_test-P1-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/test-P1-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P1_test-P1-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P1_test-P1-auto.cpp$(DependSuffix): P1/test-P1-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P1_test-P1-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P1_test-P1-auto.cpp$(DependSuffix) -MM "P1/test-P1-auto.cpp"

$(IntermediateDirectory)/P1_test-P1-auto.cpp$(PreprocessSuffix): P1/test-P1-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P1_test-P1-auto.cpp$(PreprocessSuffix) "P1/test-P1-auto.cpp"

$(IntermediateDirectory)/P1_test-P1-consola.cpp$(ObjectSuffix): P1/test-P1-consola.cpp $(IntermediateDirectory)/P1_test-P1-consola.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/test-P1-consola.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P1_test-P1-consola.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P1_test-P1-consola.cpp$(DependSuffix): P1/test-P1-consola.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P1_test-P1-consola.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P1_test-P1-consola.cpp$(DependSuffix) -MM "P1/test-P1-consola.cpp"

$(IntermediateDirectory)/P1_test-P1-consola.cpp$(PreprocessSuffix): P1/test-P1-consola.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P1_test-P1-consola.cpp$(PreprocessSuffix) "P1/test-P1-consola.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


