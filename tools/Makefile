#
# Makefile for directory tools
#

SRC=memop.c									#$(wildcard *.c)
OBJ=$(patsubst %.c,$(OUTDIR)/%.o,$(SRC))

all: $(OBJ)

$(OUTDIR)/%.o: %.c
	@echo "Compiling $< ..."
	@$(CC) -o ../$@ -c $< $(CFLAGS)
