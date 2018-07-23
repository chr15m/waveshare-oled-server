DIR_FONTS = ./fonts
DIR_OBJ = ./obj
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_FONTS}/*.c ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = oled_1in3
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

LIB = -lwiringPi

${TARGET}: ${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

${DIR_BIN}:
	mkdir -p bin

${DIR_BIN}/%.o: $(DIR_OBJ)/%.c $(DIR_BIN)
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

${DIR_BIN}/%.o: $(DIR_FONTS)/%.c $(DIR_BIN)
	$(CC) $(CFLAGS) -c  $< -o $@ 
	
clean:
	$(RM) -rf $(DIR_BIN) $(TARGET) $(DIR_OBJ)/.*.sw?
