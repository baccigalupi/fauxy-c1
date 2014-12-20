BISON=/usr/local/Cellar/bison/3.0.2/bin/bison
FLEX=/usr/local/Cellar/flex/2.5.37/bin/flex

# currently any optimization -O1 to -O3 causes the parser/bit.c code to segfault
CFLAGS=-g -O3 -std=gnu11 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)

SOURCES=$(wildcard lib/**/*.c lib/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard spec/c-unit/**/*_spec.c spec/c-unit/*_spec.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/fauxy.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: bin/fauxy dev

dev: CFLAGS=-g -std=gnu11 -Wall -Wextra -Isrc $(OPTFLAGS)
dev: $(TARGET) c-unit

# converts to an archive static lib, produces build/fauxy.a
# indexes archive for use
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

build:
	@mkdir -p build
	@mkdir -p bin

# flex and bison -----------
bin/fauxy: lib/parser/parse.tab.c lib/parser/lex.yy.c
	$(CC) $(CFLAGS) -o bin/fauxy $(SOURCES) lib/parser/parse.tab.c lib/parser/lex.yy.c -ll

lib/parser/parse.tab.c: lib/parser/parse.y
	$(BISON) --verbose lib/parser/parse.y

lib/parser/lex.yy.c: lib/parser/lex.l
	$(FLEX) -o lib/parser/lex.yy.c lib/parser/lex.l

.PHONY: run
run:
	bin/fauxy
# ---------

# C unit tests
c-unit: CFLAGS += $(TARGET)
c-unit: $(TESTS)
	sh ./spec/c-unit/lib/run_specs.sh

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f c_scpe/spec.log
	rm -f lib/parser/parse.tab.*
	rm -f lib/parser/lex.yy.*
	rm -f bin/*
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`


# # System Install
# PREFIX?=/usr/local
# install: all
# 	install -d $(DESTDIR)/$(PREFIX)/lib/
# 	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/
