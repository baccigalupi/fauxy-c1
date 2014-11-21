# Extracted from ZedShaw C learn like a badass stuff

COMPILE_FLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

SOURCES=$(wildcard lib/**/*.c lib/*.c)
COMPILED_SOURCE=$(patsubst %.c,%.o,$(SOURCES))

SPEC_SOURCES=$(wildcard c_spec/**/_spec.c c_spec/*_spec.c)
COMPILED_SPECS=$(patsubst %.c,%,$(SPEC_SOURCES))

TARGET=build/fauxy.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) cspec

dev: COMPILE_FLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: clean all

$(TARGET): COMPILE_FLAGS += -fPIC
$(TARGET): build $(COMPILED_SOURCE)
	ar rcs $@ $(COMPILED_SOURCE)
	ranlib $@

$(SO_TARGET): $(TARGET) $(COMPILED_SOURCE)
	$(CC) -shared -o $@ $(COMPILED_SOURCE)

build:
	@mkdir -p build
	@mkdir -p bin

lex:
	flex lib/parser/lex.l
	gcc lex.yy.c -ll -o lib/parser/f_lex

clean:
	rm -rf lib/parser/f_lex lib/parser/lex.yy.c
	rm -rf build $(COMPILED_SOURCE) $(COMPILED_SPECS)
	rm -f c_spec/spec.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

.PHONY: cspec
cspec: $(SPEC_SOURCES)
	sh ./c_spec/lib/run_specs.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)
