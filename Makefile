ifeq ($(OS), Windows_NT)
	BIN_DIR = win
	BIN_EXT = .exe
else
	BIN_DIR = $(shell uname -s)
endif

SRC_PATH = src
BIN_PATH = bin/$(BIN_DIR)
ROM_PATH = roms

HDR = $(SRC_PATH)/*.h
SRC = $(SRC_PATH)/*.c

CC = clang
CC_FLAGS = -O2 -Wall -Wextra -std=c99

ifeq ($(OS), Windows_NT)
	CC_FLAGS += -Wno-deprecated-declarations
endif

.PHONY: all
all: $(ROM_PATH) $(BIN_PATH) $(BIN_PATH)/sg64rando$(BIN_EXT)

$(BIN_PATH):
	mkdir -p "$(BIN_PATH)"

$(ROM_PATH):
	mkdir -p "$(ROM_PATH)"

$(BIN_PATH)/sg64rando$(BIN_EXT): $(HDR) $(SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(BIN_PATH)/sg64rando$(BIN_EXT)

.PHONY: clean
clean:
	rm -fr "$(BIN_PATH)"