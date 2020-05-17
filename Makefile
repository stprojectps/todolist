#
# Main Makefile TODOLIST PROJECT
#

#Variables
CC=gcc
CFLAGS=
LDFLAGS=-lsqlite3
build=

main_outdir=build
OUTDIR=
tools_dir=tools
sql_dir=sql
core_dir=core
test_dir=test
EXEC=app

# set variables for debug or release
ifeq ($(build), dev)
	CFLAGS=-W -Wall -pedantic -g
	OUTDIR=$(main_outdir)/debug
endif
ifeq ($(build), prod)
	CFLAGS=-W -Wall -pedantic
	OUTDIR=$(main_outdir)/release
endif

# exports variables
export CFLAGS LDFLAGS OUTDIR CC EXEC

# targets
all:

ifeq ($(build), dev)
all: debug
endif
ifeq ($(build), prod)
all: release
endif
ifeq ($(build),)
	@echo "call make with variable build set (dev or prod)"
	@echo "example make command for dev env: make build=dev"
endif

# build target
compile:
	@mkdir -p $(OUTDIR)
	@(cd $(sql_dir) && $(MAKE))
	@(cd $(tools_dir) && $(MAKE))

# debug target
debug: clean compile
	@(cd $(test_dir) && $(MAKE)) 

# release target
release: compile clean

clean:
	@echo "cleaning debug output ..."
	@rm -rf $(OUTDIR)/*.o
	@rm -rf $(OUTDIR)/$(EXEC)

mrproper: clean
