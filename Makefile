BISON=/usr/local/Cellar/bison/3.0.2/bin/bison
FLEX=/usr/local/Cellar/flex/2.5.37/bin/flex
CFLAGS=-g -O3 -std=gnu11 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard lib/**/*.c lib/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard spec/c-unit/**/*_spec.c spec/c-unit/*_spec.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/fauxy.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: bin/fauxy dev

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: $(TARGET) c-unit

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS) # converts to an archive static lib, produces build/fauxy.a
	ranlib $@ # indexes archive for use

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# flex and bison -----------
bin/fauxy: lib/parser/parse.tab.c lib/parser/lex.yy.c
	$(CC) -o bin/fauxy $(SOURCES) lib/parser/parse.tab.c lib/parser/lex.yy.c -ll

lib/parser/parse.tab.c: lib/parser/parse.y
	$(BISON) --verbose lib/parser/parse.y

lib/parser/lex.yy.c: lib/parser/lex.l
	$(FLEX) -o lib/parser/lex.yy.c lib/parser/lex.l

.PHONY: run
run:
	bin/fauxy
# ---------

# specs -----------


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
	rm -f bin/fauxy
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`


# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
