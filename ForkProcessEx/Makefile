CC=gcc
FILE1=checker.c 
FILE2=coordinator.c

OUT_EXE1 = checker.out
OUT_EXE2 = coordinator.out

build: $(FILES)
	$(CC) -o $(OUT_EXE1) $(FILE1)
	$(CC) -o $(OUT_EXE2) $(FILE2)
clean:
	rm -f *.o $(OUT_EXE1)
	rm -f *.o $(OUT_EXE2)
