#include <math.h>
#include "header.h"
#include "cpu.h"

byte readByte(byte* ram, word address) {
  if (address >= maxMemory) {
    printf("Fatal error: Attempt to access invalid memory address\n");
    exit(1);
    }
  return ram[address];
  }

byte readByteAsi(byte* ram, word address, byte asi) {
  if (asi == 0x0a || asi == 0x0b) {
    if (address >= maxMemory) {
      printf("Fatal error: Attempt to access invalid memory address\n");
      exit(1);
      }
    return ram[address];
    }
  return 0xff;
  }

void writeByte(byte* ram, word address, byte value) {
  if (address >= maxMemory) {
    printf("Fatal error: Attempt to access invalid memory address\n");
    exit(1);
    }
  ram[address] = value;
  }

void writeByteAsi(byte* ram, word address, byte value, byte asi) {
  if (asi == 0x0a || asi == 0x0b) {
    if (address >= maxMemory) {
      printf("Fatal error: Attempt to access invalid memory address\n");
      exit(1);
      }
    ram[address] = value;
    }
  }

halfword readHalfWord(byte* ram, word address) {
  if (address >= maxMemory) {
    printf("Fatal error: Attempt to access invalid memory address\n");
    exit(1);
    }
  return (ram[address] << 8) | ram[address+1];
  }

halfword readHalfWordAsi(byte* ram, word address, byte asi) {
  if (asi == 0x0a || asi == 0x0b) {
    if (address >= maxMemory) {
      printf("Fatal error: Attempt to access invalid memory address\n");
      exit(1);
      }
    return (ram[address] << 8) | ram[address+1];
    }
  return 0xffff;
  }

void writeHalfWord(byte* ram, word address, halfword value) {
  if (address >= maxMemory) {
    printf("Fatal error: Attempt to access invalid memory address\n");
    exit(1);
    }
  ram[address] = (value >> 8) & 0xff;
  ram[address+1] = value & 0xff;
  }

void writeHalfWordAsi(byte* ram, word address, halfword value, byte asi) {
  if (asi == 0x0a || asi == 0x0b) {
    if (address >= maxMemory) {
      printf("Fatal error: Attempt to access invalid memory address\n");
      exit(1);
      }
    ram[address] = (value >> 8) & 0xff;
    ram[address+1] = value & 0xff;
    return;
    }
  }

word readWord(byte* ram, word address) {
  if (address >= maxMemory) {
    printf("Fatal error: Attempt to access invalid memory address\n");
    exit(1);
    }
  return (ram[address] << 24) | (ram[address+1] << 16) | (ram[address+2] << 8) | ram[address+3];
  }

word readWordAsi(byte* ram, word address, byte asi) {
  if (asi == 0x0a || asi == 0x0b) {
    if (address >= maxMemory) {
      printf("Fatal error: Attempt to access invalid memory address\n");
      exit(1);
      }
    return (ram[address] << 24) | (ram[address+1] << 16) | (ram[address+2] << 8) | ram[address+3];
    }
  return 0xffffffff;
  }

void writeWord(byte* ram, word address, halfword value) {
  if (address >= maxMemory) {
    printf("Fatal error: Attempt to access invalid memory address\n");
    exit(1);
    }
  ram[address] = (value >> 24) & 0xff;
  ram[address+1] = (value >> 16) & 0xff;
  ram[address+2] = (value >> 8) & 0xff;
  ram[address+3] = value & 0xff;
  }

void writeWordAsi(byte* ram, word address, halfword value, byte asi) {
  if (asi == 0x0a || asi == 0x0b) {
    if (address >= maxMemory) {
      printf("Fatal error: Attempt to access invalid memory address\n");
      exit(1);
      }
    ram[address] = (value >> 24) & 0xff;
    ram[address+1] = (value >> 16) & 0xff;
    ram[address+2] = (value >> 8) & 0xff;
    ram[address+3] = value & 0xff;
    }
  }

word getR(CPU* cpu, byte r) {
  if (r == 0) return 0;
  if (r < 8) return cpu->g[r];
  r = ((cpu->psr & 0x1f) << 4) + (r - 8);
  if (r > 519) r -= 520;
  return cpu->r[r];
  }

void setR(CPU* cpu, byte r, word v) {
  if (r == 0) return;
  if (r < 8) {
    cpu->g[r] = v;
    return;
    }
  r = ((cpu->psr & 0x1f) << 4) + (r - 8);
  if (r > 519) r -= 520;
  cpu->r[r] = v;
  }

void trap(CPU *cpu, byte number) {
  byte w;
  cpu->psr &= (~PSR_ET);
  cpu->psr &= (~PSR_PS);
  if (cpu->psr & PSR_S) cpu->psr |= PSR_PS;
  cpu->psr |= PSR_S;
  w = ((cpu->psr & 0x1f) - 1) & 0x1f;
  cpu->psr = (cpu->psr & 0xffffffe0) | w;
  setR(cpu, 17, cpu->pc);
  setR(cpu, 18, cpu->npc);
  if (number == TRAP_RESET) {
    cpu->pc = 0;
    cpu->npc = 4;
    }
  else {
    cpu->tbr &= 0xfffff000;
    cpu->tbr |= (number << 4);
    cpu->pc = cpu->tbr;
    cpu->npc = cpu->pc + 4;
    }
  }

word ea(CPU *cpu) {
  word r;
  word v1,v2;
  word inst;
  inst = cpu->inst;
  r = (inst & 0x80000000) ? ((inst >> 14) & 0x1f) : 0;
  v1 = (r < 8) ? cpu->g[r] : getR(cpu, r);
  if (inst & 0x2000) {
    v2 = inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    r = inst & 0x1f;
    v2 = (r < 8) ? cpu->g[r] : getR(cpu, r);
    }
  return v1+v2;
  }

void _P0(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P8(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P9(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PA(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PB(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PC(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }
    
void _PD(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P10(CPU *cpu) {                  /* Bicc disp/4 */
  word disp;
  byte z,c,v,n;
  char jump;
  n = (cpu->psr & CC_N) ? 1 : 0;
  c = (cpu->psr & CC_C) ? 1 : 0;
  z = (cpu->psr & CC_Z) ? 1 : 0;
  v = (cpu->psr & CC_V) ? 1 : 0;
  jump = 'N';
  disp = cpu->inst & 0x3fffff;
  if ((disp & 0x200000) != 0) disp |= 0xffc00000;
  disp <<= 2;
  switch ((cpu->inst >> 25) & 0x0f) {
    case 0x01:                                        /* BE */
         if (z != 0) jump = 'Y';
         break;
    case 0x02:                                        /* BLE */
         if (z | (n ^ v)) jump = 'Y';
         break;
    case 0x03:                                        /* BL */
         if (n ^ v) jump = 'Y';
         break;
    case 0x04:                                        /* BLEU */
         if (c | z) jump = 'Y';
         break;
    case 0x05:                                        /* BCS */
         if (c) jump = 'Y';
         break;
    case 0x06:                                        /* BNEG */
         if (n) jump = 'Y';
         break;
    case 0x07:                                        /* BVS */
         if (v) jump = 'Y';
         break;
    case 0x08: jump = 'Y'; break;                     /* BA */
    case 0x09:                                        /* BNE */
         if (z == 0) jump = 'Y';
         break;
    case 0x0a:                                        /* BG */
         if (!(z | (n ^ v))) jump = 'Y';
         break;
    case 0x0b:                                        /* BGE */
         if (!(n ^ v)) jump = 'Y';
         break;
    case 0x0c:                                        /* BGU */
         if (!(c | z)) jump = 'Y';
         break;
    case 0x0d:                                        /* BCC */
         if (!c) jump = 'Y';
         break;
    case 0x0e:                                        /* BPOS */
         if (!n) jump = 'Y';
         break;
    case 0x0f:                                        /* BVC */
         if (!v) jump = 'Y';
         break;
    }
  if (jump == 'Y') cpu->npc = cpu->pc + disp;
  }

void _P11(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P12(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P13(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P14(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P15(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P16(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P17(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P18(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P19(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P1F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P20(CPU *cpu) {                  /* SETHI const,reg */
  word v;
  v = (cpu->inst & 0x3fffff) << 10;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _P21(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P22(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P23(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P24(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P25(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P26(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P27(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P28(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P29(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P2F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P30(CPU *cpu) {                  /* FBicc disp/4 */
  word disp;
  byte c;
  char jump;
  c = (cpu->fsr >> 10) & 0x3;
  jump = 'N';
  disp = cpu->inst & 0x3fffff;
  if ((disp & 0x200000) != 0) disp |= 0xffc00000;
  disp <<= 2;
  switch ((cpu->inst >> 25) & 0x0f) {
    case 0x01:                                        /* FBNE */
         if (c != 0) jump = 'Y';
         break;
    case 0x02:                                        /* FBLG */
         if ((c == 1) || (c == 2)) jump = 'Y';
         break;
    case 0x03:                                        /* FBUL */
         if ((c == 1) || (c == 3)) jump = 'Y';
         break;
    case 0x04:                                        /* FBL */
         if (c == 1) jump = 'Y';
         break;
    case 0x05:                                        /* FBUG */
         if ((c == 2) || (c == 3)) jump = 'Y';
         break;
    case 0x06:                                        /* FBG */
         if (c == 2) jump = 'Y';
         break;
    case 0x07:                                        /* FBU */
         if (c == 3) jump = 'Y';
         break;
    case 0x08: jump = 'Y'; break;                     /* FBA */
    case 0x09:                                        /* FBE */
         if (c == 0) jump = 'Y';
         break;
    case 0x0a:                                        /* FBUE */
         if ((c == 0) || (c == 3)) jump = 'Y';
         break;
    case 0x0b:                                        /* FBGE */
         if ((c == 0) || (c == 2)) jump = 'Y';
         break;
    case 0x0c:                                        /* FBUGE */
         if (c != 1) jump = 'Y';
         break;
    case 0x0d:                                        /* FBLE */
         if ((c == 0) || (c == 1)) jump = 'Y';
         break;
    case 0x0e:                                        /* FBULE */
         if (c != 2) jump = 'Y';
         break;
    case 0x0f:                                        /* FBO */
         if (c != 3) jump = 'Y';
         break;
    }
  if (jump == 'Y') cpu->npc = cpu->pc + disp;
  }

void _P31(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P32(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P33(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P34(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P35(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P36(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P37(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P38(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P39(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P3F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P40(CPU *cpu) {                  /* CALL disp30 */
  word disp;
  disp = (cpu->inst & 0x3fffffff) << 2;
  setR(cpu, 15, cpu->pc);
  cpu->npc = cpu->pc + disp;
  }

void _P41(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P42(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P43(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P44(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P45(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P46(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P47(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P48(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P49(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P4F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P50(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P51(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P52(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P53(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P54(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P55(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P56(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P57(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P58(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P59(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P5F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P60(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P61(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P62(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P63(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P64(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P65(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P66(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P67(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P68(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P69(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P6F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P70(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P71(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P72(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P73(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P74(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P75(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P76(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P77(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P78(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P79(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7A(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7B(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7C(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7E(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P7F(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P80(CPU *cpu) {                  /* ADD reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 += v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P81(CPU *cpu) {                  /* AND reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 &= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P82(CPU *cpu) {                  /* OR reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 |= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P83(CPU *cpu) {                  /* XOR reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 ^= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P84(CPU *cpu) {                  /* SUB reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 -= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P85(CPU *cpu) {                  /* ANDN reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 &= (~v2);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P86(CPU *cpu) {                  /* ORN reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 |= (~v2);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P87(CPU *cpu) {                  /* XNOR reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 = ~(v1 ^ v2);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P88(CPU *cpu) {                  /* ADDX reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 += v2;
  if ((cpu->psr & CC_C) != 0) v1++;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P89(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P8A(CPU *cpu) {                  /* UMUL reg,arg,reg */
  dword v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 *= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  cpu->y = (v1 >> 32) & 0xffffffff;
  }

void _P8B(CPU *cpu) {                  /* SMUL reg,arg,reg */
  dword v1,v2;
  char s;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  s = ((v1 & 0x8000000) == (v2 & 0x80000000)) ? 'P' : 'N';
  v1 &= 0x7fffffff;
  v2 &= 0x7fffffff;
  v1 *= v2;
  v1 &= 0x7fffffffffffffff;
  if (s == 'N') v1 |= 0x8000000000000000;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  cpu->y = (v1 >> 32) & 0xffffffff;
  }

void _P8C(CPU *cpu) {                  /* SUBX reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 -= v2;
  if ((cpu->psr & CC_C) != 0) v1--;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _P8D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P8E(CPU *cpu) {                  /* UDIV reg,arg,reg */
  dword v1,v2;
  v1 = cpu->y;
  v1 = (v1 << 32) | getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 /= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  }

void _P8F(CPU *cpu) {                  /* SDIV reg,arg,reg */
  dword v1,v2;
  char s;
  v1 = cpu->y;
  v1 = (v1 << 32) | getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  s = ((v1 >>63) == (v2 >> 31)) ? 'P' : 'N';
  v1 &= 0x7fffffffffffffff;
  v2 &= 0x7fffffff;
  v1 /= v2;
  if (s == 'N') v1 |= 0x80000000;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  }

void _P90(CPU *cpu) {                  /* ADDCC reg,arg,reg */
  word v1,v2;
  word o1;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  o1 = v1;
  v1 += v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  if (((o1 & 0x80000000) == (v2 & 0x80000000)) &&
      ((o1 & 0x80000000) != (v1 & 0x80000000))) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
  if (v1 < o1) cpu->psr |= CC_C; else cpu->psr &= (~CC_C);
  }

void _P91(CPU *cpu) {                  /* ANDCC reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 &= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  }

void _P92(CPU *cpu) {                  /* ORCC reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 |= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  }

void _P93(CPU *cpu) {                  /* XORCC reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 ^= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  }

void _P94(CPU *cpu) {                  /* SUBCC reg,arg,reg */
  word v1,v2;
  word o1;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  o1 = v1;
  v1 -= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  if (((o1 & 0x80000000) != (v2 & 0x80000000)) &&
      ((o1 & 0x80000000) != (v1 & 0x80000000))) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
  if (v1 < o1) cpu->psr |= CC_C; else cpu->psr &= (~CC_C);
  }

void _P95(CPU *cpu) {                  /* ANDNCC reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 &= (~v2);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  }

void _P96(CPU *cpu) {                  /* ORNCC reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 |= (~v2);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  }

void _P97(CPU *cpu) {                  /* XNORCC reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 = ~(v1 ^ v2);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  }

void _P98(CPU *cpu) {                  /* ADDXCC reg,arg,reg */
  word v1,v2;
  word o1;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  o1 = v1;
  v1 += v2;
  if ((cpu->psr & CC_C) != 0) v1++;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  if (((o1 & 0x80000000) == (v2 & 0x80000000)) &&
      ((o1 & 0x80000000) != (v1 & 0x80000000))) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
  if (v1 < o1) cpu->psr |= CC_C; else cpu->psr &= (~CC_C);
  }

void _P99(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P9A(CPU *cpu) {                   /* UMULCC reg,arg,reg */
  dword v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 *= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  cpu->y = (v1 >> 32) & 0xffffffff;
  if ((v1 & 0xffffffff) == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  cpu->psr &= (~CC_V);
  cpu->psr &= (~CC_C);
  }

void _P9B(CPU *cpu) {                  /* SMULCC reg,arg,reg */
  dword v1,v2;
  char s;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  s = ((v1 & 0x8000000) == (v2 & 0x80000000)) ? 'P' : 'N';
  v1 &= 0x7fffffff;
  v2 &= 0x7fffffff;
  v1 *= v2;
  v1 &= 0x7fffffffffffffff;
  if (s == 'N') v1 |= 0x8000000000000000;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  cpu->y = (v1 >> 32) & 0xffffffff;
  if ((v1 & 0xffffffff) == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  cpu->psr &= (~CC_V);
  cpu->psr &= (~CC_C);
  }

void _P9C(CPU *cpu) {                  /* SUBXCC reg,arg,reg */
  word v1,v2;
  word o1;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  o1 = v1;
  v1 -= v2;
  if ((cpu->psr & CC_C) != 0) v1--;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  if (v1 == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  if (((o1 & 0x80000000) != (v2 & 0x80000000)) &&
      ((o1 & 0x80000000) != (v1 & 0x80000000))) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
  if (v1 < o1) cpu->psr |= CC_C; else cpu->psr &= (~CC_C);
  }

void _P9D(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _P9E(CPU *cpu) {                  /* UDIVCC reg,arg,reg */
  dword v1,v2;
  v1 = cpu->y;
  v1 = (v1 << 32) | getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 /= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  if ((v1 & 0xffffffff) == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  if (v1 > 0xffffffff) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
  cpu->psr &= (~CC_C);
  }

void _P9F(CPU *cpu) {                  /* SDIVCC reg,arg,reg */
  dword v1,v2;
  char s;
  v1 = cpu->y;
  v1 = (v1 << 32) | getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  s = ((v1 >>63) == (v2 >> 31)) ? 'P' : 'N';
  v1 &= 0x7fffffffffffffff;
  v2 &= 0x7fffffff;
  v1 /= v2;
  if (s == 'N') v1 |= 0x80000000;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1 & 0xffffffff);
  if ((v1 & 0xffffffff) == 0) cpu->psr |= CC_Z; else cpu->psr &= (~CC_Z);
  if ((v1 & 0x80000000) != 0) cpu->psr |= CC_N; else cpu->psr &= (~CC_N);
  if ((v1 & 0x80000000) == 0) {
    if (v1 > 0xffffffff) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
    }
  else {
    if ((v1 >> 32) != 0xffffffff) cpu->psr |= CC_V; else cpu->psr &= (~CC_V);
    }
  cpu->psr &= (~CC_C);
  }

void _PA0(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PA1(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PA2(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PA3(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PA4(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PA5(CPU *cpu) {                  /* SLL reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1f;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f) & 0x1f;
    }
  v1 <<= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _PA6(CPU *cpu) {                  /* SRL reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1f;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f) & 0x1f;
    }
  v1 >>= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _PA7(CPU *cpu) {                  /* SRA reg,arg,reg */
  sword v1;
  word v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1f;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f) & 0x1f;
    }
  v1 >>= v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _PA8(CPU *cpu) {                  /* RD %y,reg */
  if ((cpu->inst & 0x7ffff) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  setR(cpu, (cpu->inst >> 25) & 0x1f, cpu->y);
  }

void _PA9(CPU *cpu) {                  /* RD %psr,reg */
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x7ffff) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  setR(cpu, (cpu->inst >> 25) & 0x1f, cpu->psr);
  }

void _PAA(CPU *cpu) {                  /* RD %wim,reg */
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x7ffff) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  setR(cpu, (cpu->inst >> 25) & 0x1f, cpu->wim);
  }

void _PAB(CPU *cpu) {                  /* RD %tbr,reg */
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x7ffff) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  setR(cpu, (cpu->inst >> 25) & 0x1f, cpu->tbr);
  }

void _PAC(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PAD(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PAE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PAF(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PB0(CPU *cpu) {                  /* WR reg,arg,%y */
  word r;
  word v1,v2;
  word inst;
  if ((cpu->inst & 0x7ffff) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  inst = cpu->inst;
  r = (inst & 0x80000000) ? ((inst >> 14) & 0x1f) : 0;
  v1 = (r < 8) ? cpu->g[r] : getR(cpu, r);
  if (inst & 0x2000) {
    v2 = inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    r = inst & 0x1f;
    v2 = (r < 8) ? cpu->g[r] : getR(cpu, r);
    }
  cpu->y = v1 ^ v2;
  }

void _PB1(CPU *cpu) {                  /* WR reg,arg,%psr */
  word r;
  word v1,v2;
  word inst;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  inst = cpu->inst;
  r = (inst & 0x80000000) ? ((inst >> 14) & 0x1f) : 0;
  v1 = getR(cpu, r);
  if (inst & 0x2000) {
    v2 = inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    r = inst & 0x1f;
    v2 = getR(cpu, r);
    }
  cpu->psr = v1 ^ v2;
  }

void _PB2(CPU *cpu) {                  /* WR reg,arg,%wim */
  word r;
  word v1,v2;
  word inst;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  inst = cpu->inst;
  r = (inst & 0x80000000) ? ((inst >> 14) & 0x1f) : 0;
  v1 = (r < 8) ? cpu->g[r] : getR(cpu, r);
  if (inst & 0x2000) {
    v2 = inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    r = inst & 0x1f;
    v2 = (r < 8) ? cpu->g[r] : getR(cpu, r);
    }
  cpu->wim = v1 ^ v2;
  }

void _PB3(CPU *cpu) {                  /* WR reg,arg,%tbr */
  word r;
  word v1,v2;
  word inst;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  inst = cpu->inst;
  r = (inst & 0x80000000) ? ((inst >> 14) & 0x1f) : 0;
  v1 = (r < 8) ? cpu->g[r] : getR(cpu, r);
  if (inst & 0x2000) {
    v2 = inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    r = inst & 0x1f;
    v2 = (r < 8) ? cpu->g[r] : getR(cpu, r);
    }
  cpu->tbr = v1 ^ v2;
  }

void _PB4(CPU *cpu) {
  word i;
  word rs1,rs2,rd;
  if ((cpu->psr & PSR_EF) == 0) {
    trap(cpu, TRAP_FPDIS);
    return;
    }
  i = (cpu->inst >> 5) & 0x1ff;
  rs1 = (cpu->inst >> 14) & 0x1f;
  rs2 = cpu->inst & 0x1f;
  rd = (cpu->inst >> 25) & 0x1f;
  switch (i) {
    case 0x01:                         /* FMOVS */
         cpu->f[rd].f = cpu->f[rs2].f;
         break;
    case 0x05:                         /* FNEGS */
         cpu->f[rd].f = -cpu->f[rs2].f;
         break;
    case 0x09:                         /* FABSS */
         cpu->f[rd].f = (cpu->f[rs2].f >= 0) ? cpu->f[rs2].f : -cpu->f[rs2].f;
         break;
    case 0x29:                         /* FSQRTS */
         cpu->f[rd].f = sqrt(cpu->f[rs2].f);
         break;
    case 0x41:                         /* FADDS */
         cpu->f[rd].f = cpu->f[rs1].f + cpu->f[rs2].f;
         break;
    case 0x45:                         /* FSUBS */
         cpu->f[rd].f = cpu->f[rs1].f - cpu->f[rs2].f;
         break;
    case 0x49:                         /* FMULS */
         cpu->f[rd].f = cpu->f[rs1].f * cpu->f[rs2].f;
         break;
    case 0x4d:                         /* FDIVS */
         cpu->f[rd].f = cpu->f[rs1].f / cpu->f[rs2].f;
         break;
    case 0x51:                         /* FCMPS */
         cpu->fsr &= 0xfffff3ff;
         if (cpu->f[rs1].f < cpu->f[rs2].f) cpu->fsr |= 0x400;
         if (cpu->f[rs1].f > cpu->f[rs2].f) cpu->fsr |= 0x800;
         break;
    case 0xc1:                         /* FSTOI */
         setR(cpu,rd,cpu->f[rs2].f);
         break;
    case 0xc4:                         /* FITOS */
         cpu->f[rd].f = getR(cpu,rs2);
         break;
    case 0xe1:                         /* FSINS */
         cpu->f[rd].f = sinf(cpu->f[rs2].f);
         break;
    case 0xe5:                         /* FCOSS */
         cpu->f[rd].f = cosf(cpu->f[rs2].f);
         break;
    case 0xe9:                         /* FTANS */
         cpu->f[rd].f = tanf(cpu->f[rs2].f);
         break;
    case 0xed:                         /* FLOGS */
         cpu->f[rd].f = logf(cpu->f[rs2].f);
         break;
    case 0xf1:                         /* FEXPS */
         cpu->f[rd].f = expf(cpu->f[rs2].f);
         break;
    case 0xf5:                         /* FASINS */
         cpu->f[rd].f = asinf(cpu->f[rs2].f);
         break;
    case 0xf9:                         /* FACOSS */
         cpu->f[rd].f = acosf(cpu->f[rs2].f);
         break;
    case 0xfd:                         /* FATANS */
         cpu->f[rd].f = atanf(cpu->f[rs2].f);
         break;
    default:
         trap(cpu, TRAP_UNDEF);
         break;
    }
  }

void _PB5(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PB6(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PB7(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PB8(CPU *cpu) {                  /* JMPL address,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 += v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, cpu->pc);
  cpu->npc = v1;
  }

void _PB9(CPU *cpu) {                  /* RETT address */
  word v1,v2;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 += v2;
  cpu->npc = v1;
  cpu->psr |= PSR_ET;
  cpu->psr &= (~PSR_S);
  if ((cpu->psr & PSR_PS) != 0) cpu->psr |= PSR_S;
  v2 = ((cpu->psr & 0x1f) + 1) & 0x1f;
  cpu->psr = (cpu->psr & 0xfffffffffffe000) | v2;
  }

void _PBA(CPU *cpu) {                  /* Ticc address */
  word v1,v2;
  byte z,c,v,n;
  char jump;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1  = ((v1 + v2) & 0x7f) + 128;
  n = (cpu->psr & CC_N) ? 1 : 0;
  c = (cpu->psr & CC_C) ? 1 : 0;
  z = (cpu->psr & CC_Z) ? 1 : 0;
  v = (cpu->psr & CC_V) ? 1 : 0;
  jump = 'N';
  switch ((cpu->inst >> 25) & 0x0f) {
    case 0x01:                                        /* TE */
         if (z != 0) jump = 'Y';
         break;
    case 0x02:                                        /* TLE */
         if (z | (n ^ v)) jump = 'Y';
         break;
    case 0x03:                                        /* TL */
         if (n ^ v) jump = 'Y';
         break;
    case 0x04:                                        /* TLEU */
         if (c | z) jump = 'Y';
         break;
    case 0x05:                                        /* TCS */
         if (c) jump = 'Y';
         break;
    case 0x06:                                        /* TNEG */
         if (n) jump = 'Y';
         break;
    case 0x07:                                        /* TVS */
         if (v) jump = 'Y';
         break;
    case 0x08: jump = 'Y'; break;                     /* TA */
    case 0x09:                                        /* TNE */
         if (z == 0) jump = 'Y';
         break;
    case 0x0a:                                        /* TG */
         if (!(z | (n ^ v))) jump = 'Y';
         break;
    case 0x0b:                                        /* TGE */
         if (!(n ^ v)) jump = 'Y';
         break;
    case 0x0c:                                        /* TGU */
         if (!(c | z)) jump = 'Y';
         break;
    case 0x0d:                                        /* TCC */
         if (!c) jump = 'Y';
         break;
    case 0x0e:                                        /* TPOS */
         if (!n) jump = 'Y';
         break;
    case 0x0f:                                        /* TVC */
         if (!v) jump = 'Y';
         break;
    }
  if (jump == 'Y') trap(cpu, v1);
  }

void _PBB(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PBC(CPU *cpu) {                 /* SAVE reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 += v2;
  v2 = ((cpu->psr & 0x1f) - 1) & 0x1f;
  cpu->psr = (cpu->psr & 0xfffffffffffffe0) | v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _PBD(CPU *cpu) {                  /* RESTORE reg,arg,reg */
  word v1,v2;
  v1 = getR(cpu, (cpu->inst >> 14) & 0x1f);
  if (cpu->inst & 0x2000) {
    v2 = cpu->inst & 0x1fff;
    if (v2 & 0x1000) v2 |= 0xffffe000;
    }
  else {
    v2 = getR(cpu, cpu->inst & 0x1f);
    }
  v1 += v2;
  v2 = ((cpu->psr & 0x1f) + 1) & 0x1f;
  cpu->psr = (cpu->psr & 0xfffffffffffffe0) | v2;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v1);
  }

void _PBE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PBF(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PC0(CPU *cpu) {                  /* LD [address],reg */
  word v;
  v = readWord(memory, ea(cpu));
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PC1(CPU *cpu) {                  /* LDUB [address],reg */
  word v;
  v = readByte(memory, ea(cpu));
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PC2(CPU *cpu) {                  /* LDUH [address],reg */
  word v;
  v = readHalfWord(memory, ea(cpu));
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PC3(CPU *cpu) {                  /* LDD [address],reg */
  word v;
  word e;
  word d;
  d = (cpu->inst >> 25) & 0x1f;
  e = ea(cpu);
  v = readWord(memory, e);
  setR(cpu, d, v);
  v = readWord(memory, e+4);
  setR(cpu, d+1, v);
  }

void _PC4(CPU *cpu) {                  /* ST reg,[address] */
  word v;
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeWord(memory, ea(cpu), v);
  }

void _PC5(CPU *cpu) {                  /* STB reg,[address] */
  word v;
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeByte(memory, ea(cpu), v);
  }

void _PC6(CPU *cpu) {                  /* STH reg,[address] */
  word v;
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeHalfWord(memory, ea(cpu), v);
  }

void _PC7(CPU *cpu) {                  /* STD reg,[address] */
  word v;
  word e;
  e = ea(cpu);
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeWord(memory, e, v);
  v = getR(cpu, ((cpu->inst >> 25) + 1) & 0x1f);
  writeWord(memory, e+4, v);
  }

void _PC8(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PC9(CPU *cpu) {                  /* LDSB [address],reg */
  word v;
  v = readByte(memory, ea(cpu));
  if (v & 0x80) v |= 0xffffff00;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PCA(CPU *cpu) {                  /* LDSH [address],reg */
  word v;
  v = readHalfWord(memory, ea(cpu));
  if (v & 0x8000) v |= 0xffff0000;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PCB(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PCC(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PCD(CPU *cpu) {                  /* LDSTUB [address],reg */
  word v;
  word e;
  e = ea(cpu);
  v = readByte(memory, e);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  writeByte(memory, e, 0xff);
  }

void _PCE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PCF(CPU *cpu) {                  /* SWAP [address],reg */
  word v,v1;
  word e;
  e = ea(cpu);
  v = readWord(memory, e);
  v1 = getR(cpu, (cpu->inst >> 25) & 0x1f);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  writeWord(memory, e, v1);
  }

void _PD0(CPU *cpu) {                  /* LDA [address]asi,reg */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = readWordAsi(memory, ea(cpu), asi);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PD1(CPU *cpu) {                  /* LDUBA [address]asi,reg */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = readByteAsi(memory, ea(cpu), asi);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PD2(CPU *cpu) {                  /* LDUHA [address]asi,reg */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = readHalfWordAsi(memory, ea(cpu), asi);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PD3(CPU *cpu) {                  /* LDDA [address]asi,reg */
  word v;
  word e;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  e = ea(cpu);
  v = readWordAsi(memory, e, asi);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  v = readWordAsi(memory, e+4, asi);
  setR(cpu, (((cpu->inst >> 25) & 0x1f) + 1) & 0x1f, v);
  }

void _PD4(CPU *cpu) {                  /* STA reg,[address]asi */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeWordAsi(memory, ea(cpu), v, asi);
  }

void _PD5(CPU *cpu) {                  /* STBA reg,[address]asi */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeByteAsi(memory, ea(cpu), v, asi);
  }

void _PD6(CPU *cpu) {                  /* STHA reg,[address]asi */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeHalfWordAsi(memory, ea(cpu), v, asi);
  }

void _PD7(CPU *cpu) {                  /* STDA reg,[address]asi */
  word v;
  word e;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  e = ea(cpu);
  v = getR(cpu, (cpu->inst >> 25) & 0x1f);
  writeWordAsi(memory, e, v, asi);
  v = getR(cpu, (((cpu->inst >> 25) & 0x1f) + 1) & 0x1f);
  writeWordAsi(memory, e+4, v, asi);
  }

void _PD8(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PD9(CPU *cpu) {                  /* LDSBA [address]asi,reg */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = readByteAsi(memory, ea(cpu), asi);
  if (v & 0x80) v |= 0xffffff00;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PDA(CPU *cpu) {                  /* LDSHA [address]asi,reg */
  word v;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  v = readHalfWordAsi(memory, ea(cpu), asi);
  if (v & 0x8000) v |= 0xffff0000;
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  }

void _PDB(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PDC(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PDD(CPU *cpu) {                  /* LDSTUB [address]asi,reg */
  word v;
  word e;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  e = ea(cpu);
  v = readByteAsi(memory, e, asi);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  writeByteAsi(memory, e, 0xff, asi);
  }

void _PDE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PDF(CPU *cpu) {                  /* SWAPA [address]asi,reg */
  word v,v1;
  word e;
  byte asi;
  if ((cpu->psr & PSR_S) == 0) {
    trap(cpu, TRAP_PRIV);
    return;
    }
  if ((cpu->inst & 0x00002000) != 0) {
    trap(cpu, TRAP_UNDEF);
    return;
    }
  asi = (cpu->inst >> 5) & 0xff;
  e = ea(cpu);
  v = readWordAsi(memory, e, asi);
  v1 = getR(cpu, (cpu->inst >> 25) & 0x1f);
  setR(cpu, (cpu->inst >> 25) & 0x1f, v);
  writeWordAsi(memory, e, v1, asi);
  }

void _PE0(CPU *cpu) {                  /* LD [address],freg */
  word v;
  v = readWord(memory, ea(cpu));
  cpu->f[(cpu->inst >> 25) & 0x1f].i = v;
  }

void _PE1(CPU *cpu) {                  /* LD [address],%fsr */
  cpu->fsr = readWord(memory, ea(cpu));
  }

void _PE2(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PE3(CPU *cpu) {                  /* LDD [address],freg */
  word v;
  word e;
  e = ea(cpu);
  v = readWord(memory, e);
  cpu->f[(cpu->inst >> 25) & 0x1f].i = v;
  v = readWord(memory, e+4);
  cpu->f[((cpu->inst >> 25) + 1) & 0x1f].i = v;
  }

void _PE4(CPU *cpu) {                  /* ST freg,[address] */
  word v;
  v = cpu->f[(cpu->inst >> 25) & 0x1f].i;
  writeWord(memory, ea(cpu), v);
  }

void _PE5(CPU *cpu) {                  /* ST %fsr,[address] */
  writeWord(memory, ea(cpu), cpu->fsr);
  }

void _PE6(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PE7(CPU *cpu) {                  /* STD freg,[address] */
  word v;
  word e;
  e = ea(cpu);
  v = cpu->f[(cpu->inst >> 25) & 0x1f].i;
  writeWord(memory, e, v);
  v = cpu->f[((cpu->inst >> 25) + 1) & 0x1f].i;
  writeWord(memory, e+4, v);
  }

void _PE8(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PE9(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PEA(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
 }

void _PEB(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PEC(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PED(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PEE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PEF(CPU *cpu) { 
  trap(cpu, TRAP_UNDEF);
  }

void _PF0(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF1(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF2(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF3(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF4(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF5(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF6(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF7(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF8(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PF9(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PFA(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PFB(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PFC(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PFD(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PFE(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void _PFF(CPU *cpu) {
  trap(cpu, TRAP_UNDEF);
  }

void cpu_prepare(CPU *cpu) {
  cpu->Inst[0x00]=_P0; cpu->Inst[0x01]=_P1; cpu->Inst[0x02]=_P2; cpu->Inst[0x03]=_P3;
  cpu->Inst[0x04]=_P4; cpu->Inst[0x05]=_P5; cpu->Inst[0x06]=_P6; cpu->Inst[0x07]=_P7;
  cpu->Inst[0x08]=_P8; cpu->Inst[0x09]=_P9; cpu->Inst[0x0a]=_PA; cpu->Inst[0x0b]=_PB;
  cpu->Inst[0x0c]=_PC; cpu->Inst[0x0d]=_PD; cpu->Inst[0x0e]=_PE; cpu->Inst[0x0f]=_PF;

  cpu->Inst[0x10]=_P10; cpu->Inst[0x11]=_P11; cpu->Inst[0x12]=_P12; cpu->Inst[0x13]=_P13;
  cpu->Inst[0x14]=_P14; cpu->Inst[0x15]=_P15; cpu->Inst[0x16]=_P16; cpu->Inst[0x17]=_P17;
  cpu->Inst[0x18]=_P18; cpu->Inst[0x19]=_P19; cpu->Inst[0x1a]=_P1A; cpu->Inst[0x1b]=_P1B;
  cpu->Inst[0x1c]=_P1C; cpu->Inst[0x1d]=_P1D; cpu->Inst[0x1e]=_P1E; cpu->Inst[0x1f]=_P1F;

  cpu->Inst[0x20]=_P20; cpu->Inst[0x21]=_P21; cpu->Inst[0x22]=_P22; cpu->Inst[0x23]=_P23;
  cpu->Inst[0x24]=_P24; cpu->Inst[0x25]=_P25; cpu->Inst[0x26]=_P26; cpu->Inst[0x27]=_P27;
  cpu->Inst[0x28]=_P28; cpu->Inst[0x29]=_P29; cpu->Inst[0x2a]=_P2A; cpu->Inst[0x2b]=_P2B;
  cpu->Inst[0x2c]=_P2C; cpu->Inst[0x2d]=_P2D; cpu->Inst[0x2e]=_P2E; cpu->Inst[0x2f]=_P2F;

  cpu->Inst[0x30]=_P30; cpu->Inst[0x31]=_P31; cpu->Inst[0x32]=_P32; cpu->Inst[0x33]=_P33;
  cpu->Inst[0x34]=_P34; cpu->Inst[0x35]=_P35; cpu->Inst[0x36]=_P36; cpu->Inst[0x37]=_P37;
  cpu->Inst[0x38]=_P38; cpu->Inst[0x39]=_P39; cpu->Inst[0x3a]=_P3A; cpu->Inst[0x3b]=_P3B;
  cpu->Inst[0x3c]=_P3C; cpu->Inst[0x3d]=_P3D; cpu->Inst[0x3e]=_P3E; cpu->Inst[0x3f]=_P3F;

  cpu->Inst[0x40]=_P40; cpu->Inst[0x41]=_P41; cpu->Inst[0x42]=_P42; cpu->Inst[0x43]=_P43;
  cpu->Inst[0x44]=_P44; cpu->Inst[0x45]=_P45; cpu->Inst[0x46]=_P46; cpu->Inst[0x47]=_P47;
  cpu->Inst[0x48]=_P48; cpu->Inst[0x49]=_P49; cpu->Inst[0x4a]=_P4A; cpu->Inst[0x4b]=_P4B;
  cpu->Inst[0x4c]=_P4C; cpu->Inst[0x4d]=_P4D; cpu->Inst[0x4e]=_P4E; cpu->Inst[0x4f]=_P4F;

  cpu->Inst[0x50]=_P50; cpu->Inst[0x51]=_P51; cpu->Inst[0x52]=_P52; cpu->Inst[0x53]=_P53;
  cpu->Inst[0x54]=_P54; cpu->Inst[0x55]=_P55; cpu->Inst[0x56]=_P56; cpu->Inst[0x57]=_P57;
  cpu->Inst[0x58]=_P58; cpu->Inst[0x59]=_P59; cpu->Inst[0x5a]=_P5A; cpu->Inst[0x5b]=_P5B;
  cpu->Inst[0x5c]=_P5C; cpu->Inst[0x5d]=_P5D; cpu->Inst[0x5e]=_P5E; cpu->Inst[0x5f]=_P5F;

  cpu->Inst[0x60]=_P60; cpu->Inst[0x61]=_P61; cpu->Inst[0x62]=_P62; cpu->Inst[0x63]=_P63;
  cpu->Inst[0x64]=_P64; cpu->Inst[0x65]=_P65; cpu->Inst[0x66]=_P66; cpu->Inst[0x67]=_P67;
  cpu->Inst[0x68]=_P68; cpu->Inst[0x69]=_P69; cpu->Inst[0x6a]=_P6A; cpu->Inst[0x6b]=_P6B;
  cpu->Inst[0x6c]=_P6C; cpu->Inst[0x6d]=_P6D; cpu->Inst[0x6e]=_P6E; cpu->Inst[0x6f]=_P6F;

  cpu->Inst[0x70]=_P70; cpu->Inst[0x71]=_P71; cpu->Inst[0x72]=_P72; cpu->Inst[0x73]=_P73;
  cpu->Inst[0x74]=_P74; cpu->Inst[0x75]=_P75; cpu->Inst[0x76]=_P76; cpu->Inst[0x77]=_P77;
  cpu->Inst[0x78]=_P78; cpu->Inst[0x79]=_P79; cpu->Inst[0x7a]=_P7A; cpu->Inst[0x7b]=_P7B;
  cpu->Inst[0x7c]=_P7C; cpu->Inst[0x7d]=_P7D; cpu->Inst[0x7e]=_P7E; cpu->Inst[0x7f]=_P7F;

  cpu->Inst[0x80]=_P80; cpu->Inst[0x81]=_P81; cpu->Inst[0x82]=_P82; cpu->Inst[0x83]=_P83;
  cpu->Inst[0x84]=_P84; cpu->Inst[0x85]=_P85; cpu->Inst[0x86]=_P86; cpu->Inst[0x87]=_P87;
  cpu->Inst[0x88]=_P88; cpu->Inst[0x89]=_P89; cpu->Inst[0x8a]=_P8A; cpu->Inst[0x8b]=_P8B;
  cpu->Inst[0x8c]=_P8C; cpu->Inst[0x8d]=_P8D; cpu->Inst[0x8e]=_P8E; cpu->Inst[0x8f]=_P8F;

  cpu->Inst[0x90]=_P90; cpu->Inst[0x91]=_P91; cpu->Inst[0x92]=_P92; cpu->Inst[0x93]=_P93;
  cpu->Inst[0x94]=_P94; cpu->Inst[0x95]=_P95; cpu->Inst[0x96]=_P96; cpu->Inst[0x97]=_P97;
  cpu->Inst[0x98]=_P98; cpu->Inst[0x99]=_P99; cpu->Inst[0x9a]=_P9A; cpu->Inst[0x9b]=_P9B;
  cpu->Inst[0x9c]=_P9C; cpu->Inst[0x9d]=_P9D; cpu->Inst[0x9e]=_P9E; cpu->Inst[0x9f]=_P9F;

  cpu->Inst[0xa0]=_PA0; cpu->Inst[0xa1]=_PA1; cpu->Inst[0xa2]=_PA2; cpu->Inst[0xa3]=_PA3;
  cpu->Inst[0xa4]=_PA4; cpu->Inst[0xa5]=_PA5; cpu->Inst[0xa6]=_PA6; cpu->Inst[0xa7]=_PA7;
  cpu->Inst[0xa8]=_PA8; cpu->Inst[0xa9]=_PA9; cpu->Inst[0xaa]=_PAA; cpu->Inst[0xab]=_PAB;
  cpu->Inst[0xac]=_PAC; cpu->Inst[0xad]=_PAD; cpu->Inst[0xae]=_PAE; cpu->Inst[0xaf]=_PAF;

  cpu->Inst[0xb0]=_PB0; cpu->Inst[0xb1]=_PB1; cpu->Inst[0xb2]=_PB2; cpu->Inst[0xb3]=_PB3;
  cpu->Inst[0xb4]=_PB4; cpu->Inst[0xb5]=_PB5; cpu->Inst[0xb6]=_PB6; cpu->Inst[0xb7]=_PB7;
  cpu->Inst[0xb8]=_PB8; cpu->Inst[0xb9]=_PB9; cpu->Inst[0xba]=_PBA; cpu->Inst[0xbb]=_PBB;
  cpu->Inst[0xbc]=_PBC; cpu->Inst[0xbd]=_PBD; cpu->Inst[0xbe]=_PBE; cpu->Inst[0xbf]=_PBF;

  cpu->Inst[0xc0]=_PC0; cpu->Inst[0xc1]=_PC1; cpu->Inst[0xc2]=_PC2; cpu->Inst[0xc3]=_PC3;
  cpu->Inst[0xc4]=_PC4; cpu->Inst[0xc5]=_PC5; cpu->Inst[0xc6]=_PC6; cpu->Inst[0xc7]=_PC7;
  cpu->Inst[0xc8]=_PC8; cpu->Inst[0xc9]=_PC9; cpu->Inst[0xca]=_PCA; cpu->Inst[0xcb]=_PCB;
  cpu->Inst[0xcc]=_PCC; cpu->Inst[0xcd]=_PCD; cpu->Inst[0xce]=_PCE; cpu->Inst[0xcf]=_PCF;

  cpu->Inst[0xd0]=_PD0; cpu->Inst[0xd1]=_PD1; cpu->Inst[0xd2]=_PD2; cpu->Inst[0xd3]=_PD3;
  cpu->Inst[0xd4]=_PD4; cpu->Inst[0xd5]=_PD5; cpu->Inst[0xd6]=_PD6; cpu->Inst[0xd7]=_PD7;
  cpu->Inst[0xd8]=_PD8; cpu->Inst[0xd9]=_PD9; cpu->Inst[0xda]=_PDA; cpu->Inst[0xdb]=_PDB;
  cpu->Inst[0xdc]=_PDC; cpu->Inst[0xdd]=_PDD; cpu->Inst[0xde]=_PDE; cpu->Inst[0xdf]=_PDF;

  cpu->Inst[0xe0]=_PE0; cpu->Inst[0xe1]=_PE1; cpu->Inst[0xe2]=_PE2; cpu->Inst[0xe3]=_PE3;
  cpu->Inst[0xe4]=_PE4; cpu->Inst[0xe5]=_PE5; cpu->Inst[0xe6]=_PE6; cpu->Inst[0xe7]=_PE7;
  cpu->Inst[0xe8]=_PE8; cpu->Inst[0xe9]=_PE9; cpu->Inst[0xea]=_PEA; cpu->Inst[0xeb]=_PEB;
  cpu->Inst[0xec]=_PEC; cpu->Inst[0xed]=_PED; cpu->Inst[0xee]=_PEE; cpu->Inst[0xef]=_PEF;

  cpu->Inst[0xf0]=_PF0; cpu->Inst[0xf1]=_PF1; cpu->Inst[0xf2]=_PF2; cpu->Inst[0xf3]=_PF3;
  cpu->Inst[0xf4]=_PF4; cpu->Inst[0xf5]=_PF5; cpu->Inst[0xf6]=_PF6; cpu->Inst[0xf7]=_PF7;
  cpu->Inst[0xf8]=_PF8; cpu->Inst[0xf9]=_PF9; cpu->Inst[0xfa]=_PFA; cpu->Inst[0xfb]=_PFB;
  cpu->Inst[0xfc]=_PFC; cpu->Inst[0xfd]=_PFD; cpu->Inst[0xfe]=_PFE; cpu->Inst[0xff]=_PFF;
  }

void cpu_reset(CPU* cpu) {
  cpu->pc = 0;
  cpu->npc = 0;
  cpu->psr = PSR_RESTART;
  cpu->tbr = 0;
  cpu->wim = 0;
  cpu->halt = 0;
  }

void cpu_cycle(CPU* cpu) {
  byte cmd;
  cpu->inst = readWord(memory, cpu->pc);
  cpu->npc = cpu->pc+4;
  cmd = ((cpu->inst >> 19) & 0x3f) | ((cpu->inst >> 24) & 0xc0);
  if ((cpu->inst & 0xc0000000) == 0x00000000) cmd &= 0xf8;
  if ((cpu->inst & 0xc0000000) == 0x40000000) cmd &= 0xc0;
  cpu->Inst[cmd](cpu);
  cpu->pc = cpu->npc;
  }

