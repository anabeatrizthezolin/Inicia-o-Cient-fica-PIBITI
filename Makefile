CC = g++
CFLAGS += -Wall 
CFLAGS += -g -O0
CFLAGS += -D_FILE_OFFSET_BITS=64 -m64 -O3 -fomit-frame-pointer -Wno-char-subscripts 

LFLAGS = -lm -lrt -ldl

INPUT = dataset/input.100.txt
ALG = 10

LIBOBJ = \
	external/malloc_count/malloc_count.o
	
CFLAGS += $(DEFINES)

all: main 

clean:
	\rm -f *.o ../*.o ../external/*.o external/malloc_count/malloc_count.o lib/*o repeat-dna

main: Repeat-DNA.cpp ${LIBOBJ} 
	$(CC) -o repeat-dna Repeat-DNA.cpp ${LIBOBJ} $(CFLAGS) $(LFLAGS) 

run:
	./repeat-dna $(INPUT) -A $(ALG)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./repeat-dna $(INPUT) -A $(ALG)
