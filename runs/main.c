#define MAIN
#include "header.h"
#include "cpu.h"

byte readAsiByte(word address, byte asi) {
  return 0xff;
  }

halfword readAsiHalfWord(word address, byte asi) {
  return 0xffff;
  }

word readAsiWord(word address, byte asi) {
  return 0xffffffff;
  }

void writeAsiByte(word address, byte value, byte asi) {
  }

void writeAsiHalfWord(word address, halfword value, byte asi) {
  }

void writeAsiWord(word address, word value, byte asi) {
  }

void clearMem() {
  int i;
  for (i=0; i<maxMemory; i++) memory[i] = 0;
  }

int main(int argc, char** argv) {
  int i;
  printf("Run/S v1.0.0\n");
  printf("by Michael H. Riley\n");

  maxMemory = 1000000;
  memory = (byte*)malloc(maxMemory);
  if (memory == NULL) {
    printf("Fatal error: Could not allocate memory\n");
    exit(1);
    }
  clearMem();
  runDebugger = 0;
  for (i=1; i<argc; i++) {
    if (strcmp(argv[i], "-d") == 0) runDebugger = 0xff;
    else if (loadFile(argv[i])) {
      printf("Error: Could not load %s\n",argv[i]);
      return 1;
      }
    }
  cpu_reset(&cpu);
  cpu_prepare(&cpu);
  if (runDebugger) Debugger();
  else {
    while (cpu.halt == 0) {
      cpu_cycle(&cpu);
      }
    }
  return 0;
  }

