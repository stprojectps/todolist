#
# Makefile for directory tools
#

SRC=$(wildcard src/*.c)									#$(wildcard *.c)
OBJ=$(patsubst %.c,$(OUTDIR)/%.o,$(SRC))

all: $(OBJ)

$(OUTDIR)/%.o: %.c
	@echo "Compiling $< ..."
	@$(CC) -o ../$@ -c $< $(CFLAGS) -I../${I_TOOLS}
