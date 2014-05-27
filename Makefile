# Files

FILE = main.c client-lib.c create_something.c pond.c server-lib.c core.c

# Paths

SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = bin
INC_PATH = include

# Macros

CC = gcc

# Flags

C_INC_FLAGS = -I$(INC_PATH)
C_CC_FLAGS = -Wall -g 
CFLAGS = $(C_CC_FLAGS) $(C_INC_FLAGS)

# Exe

PRODUCT = connect4.x

# SRC and OBJ list

SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))

# Main construction rules

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE_PATH)/$(PRODUCT): $(OBJ)
	@mkdir -p $(EXE_PATH)
	$(CC) -o $@ $^ $(INC) $(LIBS)

# Other rules

clean:
	rm -rf *~
	rm -rf .DS_Store # Erase the .DS_Store created on Mac OS
	@echo "Nettoyage des fichiers temporaires et des .DS_Store effectué." 
	@echo "Entrer 'make mrproper' pour nettoyer les fichiers obj."

mrproper: clean
	rm -rf $(OBJ)
	rm -f $(EXE_PATH)/$(PRODUCT)
	rm -f  *.out.txt
	@echo "Nettoyage des fichiers temporaires et des .DS_Store effectué." 

tar:
	tar -cvf connect-4.tar Makefile src include connect4.png Doxyfile README_fr.md
	gzip -9 connect-4.tar

run:
	@./$(EXE_PATH)/$(PRODUCT)

help:
	@echo "'make' : Compilation du Programme"
	@echo "'make clean' : Nettoyage des fichiers *~ et .DS_Store"
	@echo "'make mrproper' : 'make clean' et nettoyage du dossier obj"
	@echo "'make tar' : Création d'un tarball compressé via gzip"
	@echo "'make run' : Lancement du programme"
	@echo "'make help' : Voir cette aide"