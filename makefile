#option
CFLAGS = -Wall -Wextra -g -MMD
LIB = -lm -lSANDAL2 -lSDL2 -lSDL2_ttf -lSDL2_image

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable

bin/executable: $(OBJ)
	@mkdir -p $(@D)
	cc -o $@ $^ $(LIB)
	@echo "executer avec ./bin/executable"

build/%.o: src/%.c
	@mkdir -p $(@D)
	cc -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf build

-include $(DEP)
