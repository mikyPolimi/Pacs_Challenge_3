#PACS_ROOT = /home/mik01/pacs-examples/Examples
#-include $(PACS_ROOT)/Makefile.inc
CXX       = mpic++
CXXFLAGS = -std=c++20
CPPFLAGS = -fopenmp -O3 -Wall -pedantic -I$(PACS_ROOT)/include

#LDFLAGS = -L$(PACS_ROOT)/lib
LIBS    ?=
DOXYFILE=Doxyfile
EXEC = main
.PHONY = all $(EXEC) clean distclean $(DEPEND)

all: $(EXEC)

$(EXEC): %: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

clean:
	$(RM) *.o *.vtk

distclean: clean
	$(RM) $(EXEC)
	$(RM) *.csv *.out *.bak *~ *.vtk

doc:
	doxygen $(DOXYFILE)