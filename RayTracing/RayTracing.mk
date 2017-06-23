##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=RayTracing
ConfigurationName      :=Debug
WorkspacePath          :=/Users/LJY/Documents/CodeLiteWorkspace
ProjectPath            :=/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=LJY
Date                   :=22/06/2017
CodeLitePath           :="/Users/LJY/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
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
ObjectsFileList        :="RayTracing.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -framework OpenGL
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/local/include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)glew $(LibrarySwitch)glfw 
ArLibs                 :=  "glew" "glfw" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib/ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Ray.cpp$(ObjectSuffix) $(IntermediateDirectory)/IntersectResult.cpp$(ObjectSuffix) $(IntermediateDirectory)/Camera.cpp$(ObjectSuffix) $(IntermediateDirectory)/Scene.cpp$(ObjectSuffix) 



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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/Ray.cpp$(ObjectSuffix): Ray.cpp $(IntermediateDirectory)/Ray.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/Ray.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Ray.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ray.cpp$(DependSuffix): Ray.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Ray.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Ray.cpp$(DependSuffix) -MM Ray.cpp

$(IntermediateDirectory)/Ray.cpp$(PreprocessSuffix): Ray.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Ray.cpp$(PreprocessSuffix)Ray.cpp

$(IntermediateDirectory)/IntersectResult.cpp$(ObjectSuffix): IntersectResult.cpp $(IntermediateDirectory)/IntersectResult.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/IntersectResult.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IntersectResult.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IntersectResult.cpp$(DependSuffix): IntersectResult.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IntersectResult.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IntersectResult.cpp$(DependSuffix) -MM IntersectResult.cpp

$(IntermediateDirectory)/IntersectResult.cpp$(PreprocessSuffix): IntersectResult.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IntersectResult.cpp$(PreprocessSuffix)IntersectResult.cpp

$(IntermediateDirectory)/Camera.cpp$(ObjectSuffix): Camera.cpp $(IntermediateDirectory)/Camera.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/Camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Camera.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Camera.cpp$(DependSuffix): Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Camera.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Camera.cpp$(DependSuffix) -MM Camera.cpp

$(IntermediateDirectory)/Camera.cpp$(PreprocessSuffix): Camera.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Camera.cpp$(PreprocessSuffix)Camera.cpp

$(IntermediateDirectory)/Scene.cpp$(ObjectSuffix): Scene.cpp $(IntermediateDirectory)/Scene.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/LJY/Documents/CodeLiteWorkspace/CGcourse/RayTracing/Scene.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scene.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scene.cpp$(DependSuffix): Scene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Scene.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Scene.cpp$(DependSuffix) -MM Scene.cpp

$(IntermediateDirectory)/Scene.cpp$(PreprocessSuffix): Scene.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scene.cpp$(PreprocessSuffix)Scene.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


