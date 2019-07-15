#Taken from CS370 helpsession#2 and slightly modified
# List of files
C_SRCS = checker.c coordinator.c
C_OBJS = checker.o coordinator.o
#C_HEADERS
OBJS = ${C_OBJS}
EXE1 = coordinator
EXE2 = checker
#Compiler and loader commands and flags
GCC = gcc
GCC_FLAGS = -std=c11 -g -Wall -c -I.
LD_FLAGS = -std=c11 -g -Wall -I.
#Complie .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<
#Target is the executale
all: coordinator checker
coordinator: coordinator.o
	$(GCC) $(LD_FLAGS) coordinator.o -o $(EXE1)
checker: checker.o
	$(GCC) $(LD_FLAGS) checker.o -o $(EXE2)
#Recompile C Objects if headers change
$(C_OBJS) : ${C_HEADERS}

clean:
	rm -f *.o *~ $(EXE1) $(EXE2)
package: 
	zip Harris-Elijah-HW3.zip coordinator.c checker.c README.txt Makefile
