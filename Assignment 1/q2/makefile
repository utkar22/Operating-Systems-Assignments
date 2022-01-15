run:
	make all
	@echo ""
	@echo "RUNNING PROGRAM:"
	@echo ""
	./q2

all:
	make q2 A.o B.o C.o A.s C.s

q2 : A.o B.o C.o
	gcc A.o B.o C.o -no-pie -o q2

A.o : A.c
	gcc -c A.c -o A.o

B.o : B.asm
	nasm -f elf64 B.asm -o B.o

C.o : C.c
	gcc -c C.c -o C.o

A.s : A.c
	gcc -S A.c

C.s : C.c
	gcc -S C.c
