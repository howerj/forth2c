CFLAGS=-g -std=c99 -Wall -Wextra -pedantic -O2
SOURCES=gcd.fth main.fth
TARGET=forth_program

.PHONY: all clean run

all: run

run: ${TARGET}
	./${TARGET}

${TARGET}.c: forth2c ${SOURCES}
	./forth2c -m -o $@ ${SOURCES}
	-indent -linux $@
	-rm $@~

${TARGET}: ${TARGET}.c forth_runtime.h
	${CC} ${CFLAGS} -o $@ ${TARGET}.c
	#-strip $@

clean:
	rm -fv ${TARGET}.c ${TARGET}

