#ifndef _HEADER_H
#define _HEADER_H

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

typedef u_int8_t  byte;
typedef u_int16_t halfword;
typedef u_int32_t word;
typedef u_int64_t dword;
typedef int32_t   sword;

typedef union {
  word i;
  float f;
  } IF;

LINK word   address;
LINK int    errors;
LINK char   listFile;
LINK int    pass;
LINK char   showList;
LINK int    lineNumber;
LINK char   srcLine[1024];
LINK char   baseName[1024];
LINK char   srcName[1024];
LINK char   listName[1024];
LINK char   outName[1024];
LINK FILE*  srcFile;
LINK FILE*  outFile;
LINK FILE*  lstFile;
LINK char   label[128];
LINK char **labelNames;
LINK char **labelModules;
LINK word  *labelValues;
LINK word  *labelDefLines;
LINK int    numLabels;
LINK word   startAddress;
LINK int    linesAssembled;
LINK int    codeGenerated;
LINK char   outLine[128];
LINK int    outCount;
LINK FILE*  files[128];
LINK int    fileLines[128];
LINK int    numFiles;
LINK char   lineNo[16];
LINK char **defineNames;
LINK char **defineValues;
LINK int    numDefines;
LINK char   cond[256];
LINK int    numCond;
LINK int    buildNumber;
LINK int    buildMonth;
LINK int    buildDay;
LINK int    buildYear;
LINK int    buildHour;
LINK int    buildMinute;
LINK int    buildSecond;
LINK int    showSymbols;
LINK char   err[256];
LINK word  *publics;
LINK int    numPublics;
LINK word  *extrns;
LINK int    numExtrns;
LINK int    isExternal;
LINK int    addressType;
LINK char   module[256];
LINK word   orgAddress;
LINK char   buffer[256];


extern word assemble(char* line, int* err);

#endif

