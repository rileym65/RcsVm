PROJECT = asms
CC = gcc
DEFS = -Wall
INCDIR = -I ../common/ -I .
INCS =
LIBS =
LIBDIR =
OBJS = \
	../common/assemble.o \
	main.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

../common/assemble.o: ../common/assemble.c
	$(CC) $(DEFS) $(INCDIR) -c ../common/assemble.c -o ../common/assemble.o

clean:
	-rm *.o
	-rm ../common/*.o
	-rm $(PROJECT)

install:
	cp $(PROJECT) /usr/local/bin
	chmod a+x /usr/local/bin/$(PROJECT)

main.o:          header.h ../common/cpu.h main.c
