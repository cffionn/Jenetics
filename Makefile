#path var + dir commands
LOCAL=$(PWD)
ROOT=`root-config --cflags --glibs`
CXX=g++
CXXFLAGS=-Wall -O2 -Wextra -Wno-unused-local-typedefs  -Werror -Wno-deprecated-declarations -std=c++11
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

#Public install of latest fastjet code (3.3.0) on lxplus; if not on lxplus or using different version, change this path as appropriate
FASTJET=`/afs/cern.ch/work/c/cmcginn/public/Fastjet/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins`
MKDIR_BIN=mkdir -p $(LOCAL)/bin

#programs to make

all: mkdirBin forestToJeNtuple.exe forestToSubJeNtuple.exe jetGeneration.exe
mkdirBin:
	$(MKDIR_BIN)
forestToJeNtuple.exe: src/forestToJeNtuple.C
	$(CXX) $(CXXFLAGS) $(ROOT) -I $(LOCAL) -o bin/forestToJeNtuple.exe src/forestToJeNtuple.C
forestToSubJeNtuple.exe: src/forestToSubJeNtuple.C
	$(CXX) $(CXXFLAGS) $(ROOT) -I $(LOCAL) -o bin/forestToSubJeNtuple.exe src/forestToSubJeNtuple.C
jetGeneration.exe: src/jetGeneration.C
	$(CXX) $(CXXFLAGS) $(ROOT) -I $(LOCAL) -o bin/jetGeneration.exe src/jetGeneration.C

clean:
	rm -f *~
	rm -f \#*.*#
	rm -f $(LOCAL)/include/#*.*#
	rm -f $(LOCAL)/include/*~
	rm -f $(LOCAL)/src/#*.*#
	rm -f $(LOCAL)/src/*~
	rm -f $(LOCAL)/bin/*.exe
	rmdir bin
.PHONY: all

