#
# Makefile for directory core
#

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,$(OUTDIR)/%.o,$(SRC))

all: $(OBJ)

$(OUTDIR)/%.o: %.c
	@echo "Compiling $< ..."
	@$(CC) -o ../$@ -c $< $(CFLAGS)