#makefile 
CC   =   g++
CCVERSIONGTEQ48 := $(shell expr `g++ -dumpversion | cut -f1,2 -d.` \>= 4.8)

UCFLAGS = -O0 -g3 -Wall -gstabs+ 
# UCFLAGS = -O3 -Wall 

RUCFLAGS := $(shell root-config --cflags) -I./interface/ -I${python_path}/include/python2.7/ 
LIBS :=  $(shell root-config --libs) -L${python_path}/lib -lpython2.7 -lboost_python 

vpath %.cpp ./src
vpath %.cpp ./bin

SRCPP = main.cpp\
	Parameters.cpp\
	Event.cpp\
	SignalParticle.cpp\
	InputService.cpp\
	OutputService.cpp\
	Geometry.cpp\
	Packer.cpp\
	Manager.cpp\
	SignalSelectionDeltaEtaPhi.cpp\

         
OBJCPP = $(patsubst %.cpp,lib/%.o,$(SRCPP))


ifeq "$(CCVERSIONGTEQ48)" "0"
  $(error Requires g++ version >= 4.8)
endif

all : bin/concentrator_ntuplizer.exe 

lib/%.o : %.cpp
	@echo "> compiling $*"
	@mkdir -p lib/
	@$(CC) -c $< $(UCFLAGS) $(RUCFLAGS) -o $@

bin/concentrator_ntuplizer.exe : $(OBJCPP)
	@echo "> linking"
	$(CC) $^ $(LIBS) -o $@


clean:
	@echo "> Cleaning object files"
	@rm  -f lib/*.o
        
cleanall: clean
	@echo "> Cleaning executable"
	@rm -f bin/concentrator_ntuplizer.exe
