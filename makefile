CFLAGS=-W -Wall
CC=gcc $(CFLAGS)

LDFLAGS= -pthread
EXEC=prog
SRC= config.c processus.c resultat.c util.c main.c starter.c round_robin.c sjf.c
OBJ= $(SRC:.c=.o)

LDFLAGS_GUI= -pthread -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
EXEC_GUI=progGui
SRC_GUI= config.c processus.c resultat.c util.c mainGui.c starter.c round_robin.c sjf.c draw.c update.c color.c directory.c font.c graphe.c gui.c init.c input.c mouse.c texture.c timer.c window.c
OBJ_GUI= $(SRC_GUI:.c=.o)

base: $(EXEC) docs

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


interface_graphique: $(EXEC_GUI) docs

$(EXEC_GUI): $(OBJ_GUI)
	$(CC) -o $@ $^ $(LDFLAGS_GUI)
	
%.o: %.c
	$(CC) -o $@ -c $<

docs:
	@doxygen ./Doxyfile

clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf $(EXEC) -rf $(EXEC_GUI)
