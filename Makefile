BINEXEC=abre

all: ${BINEXEC} run

run:
	./abre $(id)

${BINEXEC}: abre.c
	gcc abre.c -Wall -o abre

order:
	rm -f *.o

clean:
	rm -f *.o ${BINEXEC}