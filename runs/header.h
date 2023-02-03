#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef u_int8_t  byte;
typedef u_int16_t halfword;
typedef u_int32_t word;
typedef u_int64_t dword;
typedef int32_t   sword;

#include "cpu.h"

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

LINK CPU        cpu;
LINK byte       memory[65536];
LINK char       runDebugger;

extern byte readMem(byte* ram, word address);
extern void writeMem(byte* ram, word address, byte value);


extern void Debugger();
extern word Disassem(word addr, char* dest);
extern int evaluate(char* expr);
extern int loadFile(char* filename);
extern void GotoXY(int x, int y);

#endif
