run:
	make all
	@echo ""
	@echo "RUNNING PART 1:"
	@echo ""
	./q1a
	@echo ""
	@echo "RUNNING PART 2:"
	@echo ""
	./q1b

all:
	make q1a.s q1a.o q1a q1b.s q1b.o q1b

q1a.s : q1a.c
	gcc -S q1a.c	

q1a.o : q1a.c
	gcc -c q1a.c -o q1a.o

q1a : q1a.o
	gcc q1a.o -no-pie -o q1a

q1b.s : q1b.c
	gcc -S q1b.c -lpthread	

q1b.o : q1b.c
	gcc -c q1b.c -o q1b.o -lpthread

q1b : q1b.o
	gcc q1b.o -no-pie -o q1b -lpthread