EXEC:=main.out
OBJS:=fakemn
LIBS:=fake-mininet/lib
CXXFLAGS:= -std=c++11


all: $(EXEC)

# executable (using static library)
# need libfakemn.a (compile from the Makefile of project root)
$(EXEC): %.out: %.cc
	g++ -o $@ $< -I$(LIBS) -g3 -L. -l$(OBJS) $(CXXFLAGS) -no-pie
	
indent: main.cc
	indent -i4 -bli 0 -sob -npsl main.cc -o main.cc

plot: middle.dot
	dot -Tsvg middle.dot > middle.svg

# reset & clean
clean: 
	rm -rf $(EXEC)
