
CC      := gcc

BIN_DIR := bin
SRC_DIR := src

TARGET  := $(BIN_DIR)/fireplace
SRCS    := main.c $(SRC_DIR)/fire.c
OBJS    := $(SRCS:.c=.o)
STATIC_LIB := $(SRC_DIR)/freesia_tuilib.a

all: $(TARGET) clean

$(TARGET): $(OBJS) $(STATIC_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(OBJS) $(STATIC_LIB) -lm

%.o: %.c
	$(CC) -O2 -c $< -o $@


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJS)
