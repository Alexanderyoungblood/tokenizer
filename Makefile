# All warnings, treat warnings as errors, generate dependencies in .d files
CXXFLAGS=-Wall -Werror -MD

ifdef DEBUG
LDFLAGS=-g
CXXFLAGS+=-g -O0
else
CXXFLAGS+=-O2
endif

all: tokenizer

HFILES=$(wildcard *.h)
OBJS=CTokenizer.o JavaTokenizer.o TokenizerBase.o

UnitTests: UnitTests.o $(OBJS) CToken.h JavaToken.h
	$(CXX) $(LDFLAGS) UnitTests.o $(OBJS) -lcppunit -o $@

test: UnitTests
	./UnitTests

tokenizer: $(OBJS) tokenizer.o
	$(CXX) $(LDFLAGS) tokenizer.o $(OBJS) -o $@

UnitTests.o CTokenizer.o: CToken.h
UnitTests.o JavaTokenizer.o: JavaToken.h

CToken.h: CTokenizer.cpp
	./mktoken.pl C

JavaToken.h: JavaTokenizer.cpp
	./mktoken.pl Java

clean:
	rm -f *.o *.d *.exe tokenizer UnitTests

# Pull-in dependencies generated with -MD
-include $(OBJS:.o=.d)
