########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e1 p2_e2 p2_e3 p2_e4
########################################################
OBJECTSP2_E1 = p2_e1.o element-int.o stack_element.o
OBJECTSP2_E2 = p2_e2.o graph.o Node.o element-Node.o stack_element.o
OBJECTSP2_E3 = p2_e3.o element-Node.o graph.o Node.o stack_element.o
OBJECTSP2_E4 = p2_e4.o graph.o Node.o functions.o stack_fp.o
########################################################

all: $(EJS) clear

p2_e1: $(OBJECTSP2_E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2_E1)

p2_e2: $(OBJECTSP2_E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2_E2)

p2_e3: $(OBJECTSP2_E3)
	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSP2_E3)

p2_e4: $(OBJECTSP2_E4)
	$(CC) $(CFLAGS) -o p2_e4 $(OBJECTSP2_E4)


p2_e1.o: p2_e1.c stack_element.h
	$(CC) $(CFLAGS) -c p2_e1.c

p2_e2.o: p2_e2.c stack_element.h
	$(CC) $(CFLAGS) -c p2_e2.c

p2_e3.o: p2_e3.c graph.h types.h stack_element.h
	$(CC) $(CFLAGS) -c p2_e3.c

p2_e4.o: p2_e4.c graph.h stack_fp.h
	$(CC) $(CFLAGS) -c p2_e4.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

Node.o: Node.c Node.h types.h
	$(CC) $(CFLAGS) -c Node.c

element-int.o: element-int.c element.h
	$(CC) $(CFLAGS) -c element-int.c

stack_element.o: stack_element.c stack_element.h
	$(CC) $(CFLAGS) -c stack_element.c

element-Node.o: element-Node.c Node.h element.h
	$(CC) $(CFLAGS) -c element-Node.c

functions.o: functions.c Node.h
	$(CC) $(CFLAGS) -c functions.c

stack_fp.o: stack_fp.c stack_fp.h
	$(CC) $(CFLAGS) -c stack_fp.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1"
	./p2_e1
	@echo ">>>>>>Running p2_e2"
	./p2_e2 G1.txt
	@echo ">>>>>>Running p2_e3"
	./p2_e3
	@echo ">>>>>>Running p2_e4"
	./p2_e4

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1
	@echo ">>>>>>Running p2_e2 with valgrind"
	valgrind --leak-check=full ./p2_e2 G1.txt
	@echo ">>>>>>Running p2_e3 with valgrind"
	valgrind --leak-check=full ./p2_e3
	@echo ">>>>>>Running p2_e4 with valgrind"
	valgrind --leak-check=full ./p2_e4