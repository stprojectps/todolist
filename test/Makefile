#


$(OUTDIR)/../$(EXEC): unit_test
	@echo "Compiling unit_test..."
	@$(CC) -I../${I_UNIT_TEST} -o ../$(OUTDIR)/src/unit_test.o -c ./unit_test/src/unit_test.c $(CFLAGS)
	$(CC) -I../${I_SQL} -I../${I_COMMON} -I../${I_UNIT_TEST} -I../${I_TOOLS} -o ../$(OUTDIR)/src/main.o -c ./${UNIT_TEST}/main.c $(CFLAGS)
	@echo "Compiling $@ ..."
	@$(CC) -o ../$@ ../$(OUTDIR)/src/*.o $(CFLAGS) $(LDFLAGS)