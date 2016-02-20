CFLAGS=-g -O3 -std=gnu11 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS) -ljansson

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard ../../spec/c-unit/bricks/*_spec.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=../../build/fauxy_bricks.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: dev

dev: CFLAGS=-g -std=gnu11 -Wall -Wextra -Isrc $(OPTFLAGS)
dev: $(TARGET)

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

build:
	@mkdir -p ../../build
	@mkdir -p ../../bin

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f spec/c-unit/spec.log
	rm -rf $(TARGET)
	rm -rf `find ../../ -name "bricks/*.dSYM" -print`

