#ifndef _CPU_H
#define _CPU_H

#define TRAP_RESET       0x00
#define TRAP_UNDEF       0x02
#define TRAP_PRIV        0x03
#define TRAP_WOVER       0x05
#define TRAP_WUNDER      0x06
#define TRAP_DIV0        0x2a
#define TRAP_FPDIS       0x04

#define CC_N        0x800000
#define CC_Z        0x400000
#define CC_V        0x200000
#define CC_C        0x100000
#define PSR_EF      0x001000
#define PSR_S       0x000080
#define PSR_PS      0x000040
#define PSR_ET      0x000020
#define PSR_RESTART 0xf100109f

typedef union {
  word i;
  float f;
  } IF;

typedef union {
  dword i;
  double f;
  } LD;

typedef struct _CPU {
  word psr;
  word wim;
  word tbr;
  word fsr;
  word y;
  word pc;
  word npc;
  word g[8];
  word r[520];
  IF   f[32];
  word inst;
  int  halt;
  void (*Inst[256])(struct _CPU *cpu);
  } CPU;

extern word getR(CPU* cpu, byte r);
extern void cpu_cycle(CPU* cpu);
extern void cpu_reset(CPU* cpu);
extern void cpu_prepare(CPU *cpu);
extern byte readAsiByte(word address, byte asi);
extern halfword readAsiHalfWord(word address, byte asi);
extern word readAsiWord(word address, byte asi);
extern void writeAsiByte(word address, byte value, byte asi);
extern void writeAsiHalfWord(word address, halfword value, byte asi);
extern void writeAsiWord(word address, word value, byte asi);

#endif

