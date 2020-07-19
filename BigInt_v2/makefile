src = BigInt.cpp
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d) 

OUTPUTFILE = libBigInt.so
INSTALLDIR = /usr/local/lib

CXXFLAGS= -shared -fPIC -O2 -g -std=c++14  # Flags option used for compiling C++ files

# Compiler Options
CC       = g++ # compiler used for compiling C files 
CXX      = g++ # compiler used for compiling C++ files

# set those two up even if you don't use because
# makefile will use them implicitly in $(obj)

$(OUTPUTFILE): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

# Generate dependencies of .cpp files 
-include $(dep)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean
clean:
	rm -f $(obj) $(OUTPUTFILE)
.PHONY: cleandep
cleandep:
	rm -f $(dep)
	
