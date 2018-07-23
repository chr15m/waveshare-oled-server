SRC = $(wildcard fonts/*.c src/*.c)
OBJ = $(patsubst %.c,bin/%.o,$(notdir ${SRC}))

TARGET = waveshare-oled-server

CC = gcc

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

LIB = -lwiringPi

${TARGET}: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

bin:
	mkdir -p bin

bin/%.o: src/%.c bin
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

bin/%.o: fonts/%.c bin
	$(CC) $(CFLAGS) -c  $< -o $@ 

.PHONY: clean

clean:
	rm -rf -rf bin $(TARGET)
