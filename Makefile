# Files

FILE = main.c client-lib.c create_something.c play.c pond.c server-lib.c core.c

# Paths

SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe
INC_PATH = inc

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