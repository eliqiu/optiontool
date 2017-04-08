##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=invest
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/eqiu/Documents/Eli
ProjectPath            :=C:/Users/eqiu/Documents/Eli/invest
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=eqiu
Date                   :=06/04/2017
CodeLitePath           :="C:/Program Files/CodeLite"
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
ObjectsFileList        :="invest.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
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
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/etfOption.cpp$(ObjectSuffix) $(IntermediateDirectory)/optStratege.cpp$(ObjectSuffix) $(IntermediateDirectory)/account.cpp$(ObjectSuffix) $(IntermediateDirectory)/datAPI.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/eqiu/Documents/Eli/invest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/etfOption.cpp$(ObjectSuffix): etfOption.cpp $(IntermediateDirectory)/etfOption.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/eqiu/Documents/Eli/invest/etfOption.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/etfOption.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/etfOption.cpp$(DependSuffix): etfOption.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/etfOption.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/etfOption.cpp$(DependSuffix) -MM etfOption.cpp

$(IntermediateDirectory)/etfOption.cpp$(PreprocessSuffix): etfOption.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/etfOption.cpp$(PreprocessSuffix) etfOption.cpp

$(IntermediateDirectory)/optStratege.cpp$(ObjectSuffix): optStratege.cpp $(IntermediateDirectory)/optStratege.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/eqiu/Documents/Eli/invest/optStratege.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/optStratege.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/optStratege.cpp$(DependSuffix): optStratege.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/optStratege.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/optStratege.cpp$(DependSuffix) -MM optStratege.cpp

$(IntermediateDirectory)/optStratege.cpp$(PreprocessSuffix): optStratege.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/optStratege.cpp$(PreprocessSuffix) optStratege.cpp

$(IntermediateDirectory)/account.cpp$(ObjectSuffix): account.cpp $(IntermediateDirectory)/account.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/eqiu/Documents/Eli/invest/account.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/account.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/account.cpp$(DependSuffix): account.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/account.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/account.cpp$(DependSuffix) -MM account.cpp

$(IntermediateDirectory)/account.cpp$(PreprocessSuffix): account.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/account.cpp$(PreprocessSuffix) account.cpp

$(IntermediateDirectory)/datAPI.cpp$(ObjectSuffix): datAPI.cpp $(IntermediateDirectory)/datAPI.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/eqiu/Documents/Eli/invest/datAPI.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/datAPI.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/datAPI.cpp$(DependSuffix): datAPI.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/datAPI.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/datAPI.cpp$(DependSuffix) -MM datAPI.cpp

$(IntermediateDirectory)/datAPI.cpp$(PreprocessSuffix): datAPI.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/datAPI.cpp$(PreprocessSuffix) datAPI.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


