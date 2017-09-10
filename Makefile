CXX=g++
CXXFLAGS=-Wall -O2 -Wextra -Wno-unused-local-typedefs  -Werror -Wno-deprecated-declarations -std=c++11
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

MKDIR_BIN=mkdir -p $(LOCAL)/bin

BOOST=/home/pi/Packages/Boost/boost_1_65_1/
LOCAL=$(PWD)

all: mkdirBin calcPI.exe

mkdirBin:
	$(MKDIR_BIN)

calcPI.exe: src/calcPI.C
	$(CXX) $(CXXFLAGS) -I $(LOCAL) -I $(BOOST) -pthread -o bin/calcPI.exe src/calcPI.C

clean:
	rm -f *~
	rm -f src/*~
	rm -rf bin
