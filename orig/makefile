
.PHONY: all clean

all:
	./forth2c.py countdown.4th gcd.4th main.4th
	gcc -g -Wall -o forth_program forth_program.c
	gdb -x "python execfile('gdb_forth.py')" forth_program

clean:
	rm -vf forth_program forth_program.c
