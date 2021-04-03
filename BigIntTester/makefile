
### find and replace temp with your name of library



src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d) 

INSTALL_DIR = /usr/local/bin
OUTPUTFILE = final.o
LDFLAGS = -L/usr/src/googletest/googletest -lgtest -pthread 
CXXFLAGS= -O0 -g -std=c++14 -Wall 

  # Flags option used for compiling C++ files

# Compiler Options
CC       = g++ # compiler used for compiling C files 
CXX      = g++ # compiler used for compiling C++ files

$(OUTPUTFILE): $(obj)
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LDFLAGS)
	

# Generate dependencies of .cpp files 
-include $(dep)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@ 
	
#######################
### VALGRIND SECTION
#######################
VALG_FILE = valg_log
VALG_FLAGS =  --tool=memcheck --leak-check=yes --log-file=$(VALG_FILE)

.PHONY: valg_all
valg_all:	valg valg_show_print

.PHONY: valg
valg:
	valgrind $(VALG_FLAGS) ./$(OUTPUTFILE)

.PHONY: valg_show_print
valg_show_print:
	cat $(VALG_FILE)

#######################
## Debugging
#######################
.PHONY: gdb
gdb: 
	gdb ./$(OUTPUTFILE)


#######################
## CLEANING THINGS UP
#######################
	
.PHONY: cleanall 
cleanall: clean cleandep

.PHONY: clean
clean:
	rm -f $(obj) $(OUTPUTFILE)
.PHONY: cleandep
cleandep:
	rm -f $(dep)
	
.PHONY: run
run:
	./$(OUTPUTFILE)

.PHONY: install
install:
	sudo cp $(OUTPUTFILE) $(INSTALL_DIR) 
	