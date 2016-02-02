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
Date                   :=02/02/16
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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Cadena_cadena.cpp$(ObjectSuffix) $(IntermediateDirectory)/Fecha_fecha.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_articulo.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_tarjeta.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_usuario.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_pedido.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_pedido-articulo.cpp$(ObjectSuffix) $(IntermediateDirectory)/P2_luhn.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_test-auto.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_test-caso1-auto.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_test-caso3-auto.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_test-caso4-auto.cpp$(ObjectSuffix) $(IntermediateDirectory)/P4_test-caso4-consola.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Cadena_cadena.cpp$(ObjectSuffix): P1/Cadena/cadena.cpp $(IntermediateDirectory)/Cadena_cadena.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/Cadena/cadena.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Cadena_cadena.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Cadena_cadena.cpp$(DependSuffix): P1/Cadena/cadena.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Cadena_cadena.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Cadena_cadena.cpp$(DependSuffix) -MM "P1/Cadena/cadena.cpp"

$(IntermediateDirectory)/Cadena_cadena.cpp$(PreprocessSuffix): P1/Cadena/cadena.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Cadena_cadena.cpp$(PreprocessSuffix) "P1/Cadena/cadena.cpp"

$(IntermediateDirectory)/Fecha_fecha.cpp$(ObjectSuffix): P1/Fecha/fecha.cpp $(IntermediateDirectory)/Fecha_fecha.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/Fecha/fecha.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Fecha_fecha.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Fecha_fecha.cpp$(DependSuffix): P1/Fecha/fecha.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Fecha_fecha.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Fecha_fecha.cpp$(DependSuffix) -MM "P1/Fecha/fecha.cpp"

$(IntermediateDirectory)/Fecha_fecha.cpp$(PreprocessSuffix): P1/Fecha/fecha.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Fecha_fecha.cpp$(PreprocessSuffix) "P1/Fecha/fecha.cpp"

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

$(IntermediateDirectory)/P2_luhn.cpp$(ObjectSuffix): P2/luhn.cpp $(IntermediateDirectory)/P2_luhn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P2/luhn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P2_luhn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P2_luhn.cpp$(DependSuffix): P2/luhn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P2_luhn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P2_luhn.cpp$(DependSuffix) -MM "P2/luhn.cpp"

$(IntermediateDirectory)/P2_luhn.cpp$(PreprocessSuffix): P2/luhn.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P2_luhn.cpp$(PreprocessSuffix) "P2/luhn.cpp"

$(IntermediateDirectory)/P4_test-auto.cpp$(ObjectSuffix): P4/test-auto.cpp $(IntermediateDirectory)/P4_test-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-auto.cpp$(DependSuffix): P4/test-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-auto.cpp$(DependSuffix) -MM "P4/test-auto.cpp"

$(IntermediateDirectory)/P4_test-auto.cpp$(PreprocessSuffix): P4/test-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-auto.cpp$(PreprocessSuffix) "P4/test-auto.cpp"

$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(ObjectSuffix): P4/test-caso0-cadena-auto.cpp $(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-caso0-cadena-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(DependSuffix): P4/test-caso0-cadena-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(DependSuffix) -MM "P4/test-caso0-cadena-auto.cpp"

$(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(PreprocessSuffix): P4/test-caso0-cadena-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-caso0-cadena-auto.cpp$(PreprocessSuffix) "P4/test-caso0-cadena-auto.cpp"

$(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(ObjectSuffix): P4/test-caso0-fecha-auto.cpp $(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-caso0-fecha-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(DependSuffix): P4/test-caso0-fecha-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(DependSuffix) -MM "P4/test-caso0-fecha-auto.cpp"

$(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(PreprocessSuffix): P4/test-caso0-fecha-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-caso0-fecha-auto.cpp$(PreprocessSuffix) "P4/test-caso0-fecha-auto.cpp"

$(IntermediateDirectory)/P4_test-caso1-auto.cpp$(ObjectSuffix): P4/test-caso1-auto.cpp $(IntermediateDirectory)/P4_test-caso1-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-caso1-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-caso1-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-caso1-auto.cpp$(DependSuffix): P4/test-caso1-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-caso1-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-caso1-auto.cpp$(DependSuffix) -MM "P4/test-caso1-auto.cpp"

$(IntermediateDirectory)/P4_test-caso1-auto.cpp$(PreprocessSuffix): P4/test-caso1-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-caso1-auto.cpp$(PreprocessSuffix) "P4/test-caso1-auto.cpp"

$(IntermediateDirectory)/P4_test-caso3-auto.cpp$(ObjectSuffix): P4/test-caso3-auto.cpp $(IntermediateDirectory)/P4_test-caso3-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-caso3-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-caso3-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-caso3-auto.cpp$(DependSuffix): P4/test-caso3-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-caso3-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-caso3-auto.cpp$(DependSuffix) -MM "P4/test-caso3-auto.cpp"

$(IntermediateDirectory)/P4_test-caso3-auto.cpp$(PreprocessSuffix): P4/test-caso3-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-caso3-auto.cpp$(PreprocessSuffix) "P4/test-caso3-auto.cpp"

$(IntermediateDirectory)/P4_test-caso4-auto.cpp$(ObjectSuffix): P4/test-caso4-auto.cpp $(IntermediateDirectory)/P4_test-caso4-auto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-caso4-auto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-caso4-auto.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-caso4-auto.cpp$(DependSuffix): P4/test-caso4-auto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-caso4-auto.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-caso4-auto.cpp$(DependSuffix) -MM "P4/test-caso4-auto.cpp"

$(IntermediateDirectory)/P4_test-caso4-auto.cpp$(PreprocessSuffix): P4/test-caso4-auto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-caso4-auto.cpp$(PreprocessSuffix) "P4/test-caso4-auto.cpp"

$(IntermediateDirectory)/P4_test-caso4-consola.cpp$(ObjectSuffix): P4/test-caso4-consola.cpp $(IntermediateDirectory)/P4_test-caso4-consola.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P4/test-caso4-consola.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/P4_test-caso4-consola.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/P4_test-caso4-consola.cpp$(DependSuffix): P4/test-caso4-consola.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/P4_test-caso4-consola.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/P4_test-caso4-consola.cpp$(DependSuffix) -MM "P4/test-caso4-consola.cpp"

$(IntermediateDirectory)/P4_test-caso4-consola.cpp$(PreprocessSuffix): P4/test-caso4-consola.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/P4_test-caso4-consola.cpp$(PreprocessSuffix) "P4/test-caso4-consola.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


