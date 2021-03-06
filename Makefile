CXXFLAGS ?= -std=c++11 -m32 -g -O0 -static -fopenmp -lpthread  -Wall -I$(QSIM_PREFIX)/include -I.
LDLIBS ?= -lpthread -ldl

TESTS = threads

all: $(TESTS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)
	sed 's/TEST/$@/g' runme_orig.sh > runme.sh
	tar -cf $@.tar $@ runme.sh

clean:
	rm -f $(TESTS) runme.sh *.tar trial*
