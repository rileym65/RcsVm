PROJECT=runs
CC=gcc
DEFS=-Wall
INCS=
INCDIR=-I ../common/ -I .
LIBS=-lm
LIBDIR=
OBJS=\
	../common/cpu.o \
	../common/disassem.o \
	debugger.o \
	evaluate.o \
	loadfile.o \
	main.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(OBJS) $(LIBDIR) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<


../common/cpu.o: ../common/cpu.c ../common/cpu.h
	$(CC) $(DEFS) $(INCDIR) -c ../common/cpu.c -o ../common/cpu.o

../common/disassem.o: ../common/disassem.c ../common/cpu.h
	$(CC) $(DEFS) $(INCDIR) -c ../common/disassem.c -o ../common/disassem.o

clean:
	-rm *.o
	-rm ../common/*.o
	-rm $(PROJECT)

install:
	cp $(PROJECT) /usr/local/bin
	chmod a+rx /usr/local/bin/$(PROJECT)

debugger.o:  ../common/cpu.h header.h debugger.c
evaluate.o:  ../common/cpu.h header.h evaluate.c
loadfile.o:  ../common/cpu.h header.h loadfile.c
main.o:      ../common/cpu.h header.h main.c

