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
Date                   :=05/05/14
CodeLitePath           :="/home/zerokullneo/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/Cadena_cadena$(ObjectSuffix) $(IntermediateDirectory)/Fecha_fecha$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Cadena_cadena$(ObjectSuffix): P1/Cadena/cadena.cpp $(IntermediateDirectory)/Cadena_cadena$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/Cadena/cadena.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Cadena_cadena$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Cadena_cadena$(DependSuffix): P1/Cadena/cadena.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Cadena_cadena$(ObjectSuffix) -MF$(IntermediateDirectory)/Cadena_cadena$(DependSuffix) -MM "P1/Cadena/cadena.cpp"

$(IntermediateDirectory)/Cadena_cadena$(PreprocessSuffix): P1/Cadena/cadena.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Cadena_cadena$(PreprocessSuffix) "P1/Cadena/cadena.cpp"

$(IntermediateDirectory)/Fecha_fecha$(ObjectSuffix): P1/Fecha/fecha.cpp $(IntermediateDirectory)/Fecha_fecha$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zerokullneo/github/codelite/carrito_libreria/P1/Fecha/fecha.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Fecha_fecha$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Fecha_fecha$(DependSuffix): P1/Fecha/fecha.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Fecha_fecha$(ObjectSuffix) -MF$(IntermediateDirectory)/Fecha_fecha$(DependSuffix) -MM "P1/Fecha/fecha.cpp"

$(IntermediateDirectory)/Fecha_fecha$(PreprocessSuffix): P1/Fecha/fecha.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Fecha_fecha$(PreprocessSuffix) "P1/Fecha/fecha.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Cadena_cadena$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Cadena_cadena$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Cadena_cadena$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Fecha_fecha$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Fecha_fecha$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Fecha_fecha$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/carrito_libreria"


