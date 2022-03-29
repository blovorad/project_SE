CC=gcc
CFLAGS=-W -Wall
LDFLAGS= -pthread
EXEC=prog
SRC= config.c processus.c resultat.c util.c main.c starter.c round_robin.c sjf.c
OBJ= $(SRC:.c=.o)

all: $(EXEC) docs

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

	
main.o: config.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

docs:
	@doxygen ./Doxyfile

.PHONY: clean mrproper

clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf $(EXEC)
