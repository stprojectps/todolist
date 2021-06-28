#
# Makefile for directory sql
#

SRC=$(wildcard src/*.c)
OBJ=$(patsubst %.c,$(OUTDIR)/%.o,$(SRC))

all: $(OBJ)

$(OUTDIR)/%.o: %.c
	@echo "Compiling $@ ..."
	@$(CC) -o ../$@ -c $< $(CFLAGS) -I../${I_SQL} -I../${I_COMMON} -I../${I_TOOLS}
