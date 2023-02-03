#include "header.h"

word address;
char lines[16][80];
word breakpoints[1000];
int  numBreakpoints;
int  tracing;
byte traps[256];
unsigned int clocks;
char conditions[100][256];
int  numConditions;
char useConditions;


void Cls() {
  printf("\e[H\e[2J");
  }

void GotoXY(int x, int y) {
  printf("\e[%d;%dH",y,x);
  }

int IsHex(char* line) {
  if (*line >= '0' && *line <= '9') return -1;
  if (*line >= 'a' && *line <= 'f') return -1;
  if (*line >= 'A' && *line <= 'F') return -1;
  return 0;
  }

word GetHex(char* line) {
  word ret;
  ret = 0;
  while (IsHex(line)) {
    ret <<= 4;
    if (*line >= '0' && *line <= '9') ret |= (*line - '0');
    if (*line >= 'a' && *line <= 'f') ret |= (*line - 87);
    if (*line >= 'A' && *line <= 'F') ret |= (*line - 55);
    line++;
    }
  return ret;
  }

void DrawScreen() {
  int l;
  Cls();
  l = 1;
  GotoXY(1,l++); printf("I7: 00000000  I3: 00000000   G7: 00000000  G3: 00000000   PSR: 00000000");
  GotoXY(1,l++); printf("I6: 00000000  I2: 00000000   G6: 00000000  G2: 00000000   WIM: 00000000");
  GotoXY(1,l++); printf("I5: 00000000  I1: 00000000   G5: 00000000  G1: 00000000   TBR: 00000000");
  GotoXY(1,l++); printf("I4: 00000000  I0: 00000000   G4: 00000000  G0: 00000000   N Z C V   S   ET EF");
  GotoXY(1,l++); printf("              +----------------------------------------------------------------+");
  GotoXY(1,l++); printf("L7: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L6: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L5: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L4: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L3: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L2: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L1: 00000000  |                                                                |");
  GotoXY(1,l++); printf("L0: 00000000  |                                                                |");
  GotoXY(1,l++); printf("              |                                                                |");
  GotoXY(1,l++); printf("O7: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O6: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O5: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O4: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O3: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O2: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O1: 00000000  |                                                                |");
  GotoXY(1,l++); printf("O0: 00000000  +----------------------------------------------------------------+");
  GotoXY(1,l++);
  printf("  -->\n");
  printf("    >");
  }

void UpdateScreen() {
  GotoXY(5,1); printf("%08x",getR(&cpu, 31));
  GotoXY(5,2); printf("%08x",getR(&cpu, 30));
  GotoXY(5,3); printf("%08x",getR(&cpu, 29));
  GotoXY(5,4); printf("%08x",getR(&cpu, 28));
  GotoXY(19,1); printf("%08x",getR(&cpu, 27));
  GotoXY(19,2); printf("%08x",getR(&cpu, 26));
  GotoXY(19,3); printf("%08x",getR(&cpu, 25));
  GotoXY(19,4); printf("%08x",getR(&cpu, 24));
  GotoXY(5,6); printf("%08x",getR(&cpu, 23));
  GotoXY(5,7); printf("%08x",getR(&cpu, 22));
  GotoXY(5,8); printf("%08x",getR(&cpu, 21));
  GotoXY(5,9); printf("%08x",getR(&cpu, 20));
  GotoXY(5,10); printf("%08x",getR(&cpu, 19));
  GotoXY(5,11); printf("%08x",getR(&cpu, 18));
  GotoXY(5,12); printf("%08x",getR(&cpu, 17));
  GotoXY(5,13); printf("%08x",getR(&cpu, 16));
  GotoXY(5,15); printf("%08x",getR(&cpu, 15));
  GotoXY(5,16); printf("%08x",getR(&cpu, 14));
  GotoXY(5,17); printf("%08x",getR(&cpu, 13));
  GotoXY(5,18); printf("%08x",getR(&cpu, 12));
  GotoXY(5,19); printf("%08x",getR(&cpu, 11));
  GotoXY(5,20); printf("%08x",getR(&cpu, 10));
  GotoXY(5,21); printf("%08x",getR(&cpu, 9));
  GotoXY(5,22); printf("%08x",getR(&cpu, 8));
  GotoXY(34,1); printf("%08x",getR(&cpu, 7));
  GotoXY(34,2); printf("%08x",getR(&cpu, 6));
  GotoXY(34,3); printf("%08x",getR(&cpu, 5));
  GotoXY(34,4); printf("%08x",getR(&cpu, 4));
  GotoXY(48,1); printf("%08x",getR(&cpu, 3));
  GotoXY(48,2); printf("%08x",getR(&cpu, 2));
  GotoXY(48,3); printf("%08x",getR(&cpu, 1));
  GotoXY(48,4); printf("%08x",getR(&cpu, 0));
  GotoXY(64,1); printf("%08x",cpu.psr);
  GotoXY(64,2); printf("%08x",cpu.wim);
  GotoXY(64,3); printf("%08x",cpu.tbr);
  GotoXY(59,4); if (cpu.psr & CC_N) printf("N"); else printf("-");
  GotoXY(61,4); if (cpu.psr & CC_Z) printf("Z"); else printf("-");
  GotoXY(63,4); if (cpu.psr & CC_C) printf("C"); else printf("-");
  GotoXY(65,4); if (cpu.psr & CC_V) printf("V"); else printf("-");
  GotoXY(69,4); if (cpu.psr & PSR_S) printf("S"); else printf("-");
  GotoXY(73,4); if (cpu.psr & PSR_ET) printf("ET"); else printf("--");
  GotoXY(76,4); if (cpu.psr & PSR_EF) printf("EF"); else printf("--");
  }

void Output(char* msg) {
  int i;
  for (i=0; i<15; i++) {
    strcpy(lines[i], lines[i+1]);
    lines[i][64] = 0;
    GotoXY(16,i+6); printf("%s", lines[i]);
    }
  strcpy(lines[15], msg);
  while (strlen(lines[15]) < 64) strcat(lines[15]," ");
  lines[15][64] = 0;
  GotoXY(16,21); printf("%s",lines[15]); fflush(stdout);
  }

void debugger_qm(char* line) {
  char l[70];
  char t[6];
  int  stack;
  int  x,y;
  stack = 0;
  if (*line == 'f' || *line == 'F') {
    for (x=0; x<16; x++) {
      sprintf(l,"%02d: %08x %12f      %02d: %08x %12f",x,cpu.f[x].i,cpu.f[x].f,
                                                    x+16,cpu.f[x+16].i,cpu.f[x+16].f);
      Output(l);
      }
    return;
    }
  if (*line == 'c' || *line == 'C') {
    sprintf(l,"Clocks: %u",clocks);
    Output(l);
    line++;
    if (*line == '-') clocks = 0;
    return;
    }
  if (IsHex(line)) address = GetHex(line);
  else if (*line == 'p' || *line == 'P') address = cpu.pc;
  for (y=0; y<16; y++) {
    if (stack) sprintf(l,"%04x:",0x100 + (address & 0xff));
      else sprintf(l,"%04x:",address);
    for (x=0; x<16; x++) {
      if (stack) sprintf(t," %02x",memory[0x100 + ((address++) & 0xff)]);
        else sprintf(t," %02x",memory[address++]);
      strcat(l, t);
      }
    Output(l);
    }
  }

void debugger_dl(char* line) {
  char l[80];
  int  y;
  if (IsHex(line)) address = GetHex(line);
  else if (*line == 'p' || *line == 'P') address = cpu.pc;
  for (y=0; y<16; y++) {
    address = Disassem(address, l);
    Output(l);
    }
  }

void debugger_ex(char*line) {
  word v;
  word addr;
  if (*line == 'P' || *line == 'p') addr = cpu.pc;
  else if (IsHex(line)) {
    addr = GetHex(line);
    while (IsHex(line)) line++;
    while (*line == ' ') line++;
    }
  else return;
  while (IsHex(line)) {
    v = GetHex(line);
    memory[addr++] = v;
    while (IsHex(line)) line++;
    while (*line == ' ') line++;
    }
  }

void debugger_b(char* line) {
  int  i,j;
  word addr;
  char l[70];
  char t[6];
  if (*line == '?') {
    Output("Breakpoints:");
    i = 0;
    strcpy(l,"  ");
    while (i < numBreakpoints) {
      sprintf(t," %04x", breakpoints[i++]);
      strcat(l, t);
      if (strlen(l) > 62) {
        Output(l);
        strcpy(l,"  ");
        }
      }
    if (strlen(l) > 2) Output(l);
    return;
    }
  if (*line == '+') {
    line++;
    addr = GetHex(line);
    for (i=0; i<numBreakpoints; i++)
      if (breakpoints[i] == addr) return;
    breakpoints[numBreakpoints++] = addr;
    return;
    }
  if (*line == '-') {
    line++;
    addr = GetHex(line);
    for (i=0; i<numBreakpoints; i++)
      if (breakpoints[i] == addr) {
        for (j=i; j<numBreakpoints-1; j++)
          breakpoints[j] = breakpoints[j+1];
        numBreakpoints--;
        return;
        }
    return;
    }
  if (*line == 'c' || *line == 'C') {
    numBreakpoints = 0;
    return;
    }
  }

void debugger_c(char*line) {
  int i;
  int j;
  char outp[300];
  if (*line == '?') {
    Output("Conditional breakpoints:");
    for (i=0; i<numConditions; i++) {
      sprintf(outp,"%d:%s",i+1,conditions[i]);
      Output(outp);
      }
    return;
    }
  if (*line == '+' && *(line+1) == '+') {
    useConditions = 'Y';
    Output("Conditions enabled");
    return;
    }
  if (*line == '-' && *(line+1) == '-') {
    useConditions = 'N';
    Output("Conditions disabled");
    return;
    }
  if (*line == '+') {
    line++;
    strcpy(conditions[numConditions++], line);
    return;
    }
  if (*line == '-') {
    line++;
    j = atoi(line) - 1;
    if (j >= 0 && j < numConditions) {
      for (i=j; i<numConditions-1; i++)
        strcpy(conditions[i], conditions[i+1]);
      numConditions--;
      }
    }
  if (*line == 'c' || *line == 'C') {
    numConditions = 0;
    Output("Conditions cleared");
    return;
    }
  }


void debugger_p(char*line) {
  if (*line == 'c' || *line == 'C') {
    line++;
    if (*line == '=') {
      line++;
      if (IsHex(line)) {
        cpu.pc = GetHex(line);
        UpdateScreen();
        }
      }
    return;
    }
  }

void debugger_t(char* line) {
  int  i;
  word addr;
  char l[70];
  char t[6];
  if (*line == 'r' || *line == 'R') {
    line++;
    if (*line == '+') tracing = 0xff;
    if (*line == '-') tracing = 0x00;
    return;
    }
  if (*line == '?') {
    Output("Traps:");
    i = 0;
    strcpy(l,"  ");
    for (i=0; i<256; i++) {
      if (traps[i] != 0) {
        sprintf(t," %02x", i);
        strcat(l, t);
        if (strlen(l) > 62) {
          Output(l);
          strcpy(l,"  ");
          }
        }
      }
    if (strlen(l) > 2) Output(l);
    return;
    }
  if (*line == '+') {
    line++;
    addr = GetHex(line);
    traps[addr & 0xff] = 0xff;
    return;
    }
  if (*line == '-') {
    line++;
    addr = GetHex(line);
    traps[addr & 0xff] = 0x00;
    return;
    }
  if (*line == 'c' || *line == 'C') {
    for (i=0; i<256; i++) traps[i] = 0x00;
    return;
    }
  }

void debugger_run(char* line) {
  int i;
  int run;
  char dis[1024];
  run = -1;
  if (IsHex(line)) cpu.pc = GetHex(line);
  while (run) {
    if (tracing) {
      Disassem(cpu.pc, dis);
      Output(dis);
      }
    cpu_cycle(&cpu);
    if (cpu.halt != 0) run = 0;
    for (i=0; i<numBreakpoints; i++)
      if (cpu.pc == breakpoints[i]) {
        run = 0;
        UpdateScreen();
        }
    if (useConditions == 'Y') {
      for (i=0; i<numConditions; i++)
        if (evaluate(conditions[i]) != 0) {
          run = 0;
          UpdateScreen();
          }
      }
    if (traps[memory[cpu.pc]] != 0) {
      run = 0;
      UpdateScreen();
      }
    }
  UpdateScreen();
  }

void Debugger() {
  int i;
  int flag;
  char line[1024];
  char dis[1024];
  for (i=0; i<15; i++)
    strcpy(lines[i],"                                                                  ");
  for (i=0; i<256; i++) traps[i] = 0;
  address = 0;
  numBreakpoints = 0;
  numConditions = 0;
  useConditions = 'Y';
  tracing = 0;
  clocks = 0;
  DrawScreen();
  UpdateScreen();
  flag = -1;
  while (flag) {
    GotoXY(6, 23); printf("                                                               ");
    GotoXY(6, 24); printf("                                                               ");
    Disassem(cpu.pc, line);
    GotoXY(6, 23); printf("%s",line);
    GotoXY(1, 24); printf("%04x>",cpu.pc);
    fgets(line, 1023, stdin);
    while (strlen(line) > 0 && line[strlen(line)-1] <= ' ')
      line[strlen(line)-1] = 0;
    if (strcmp(line,"/") == 0) flag = 0;
    if (line[0] == '?') debugger_qm(line+1);
    if (line[0] == '$') debugger_dl(line+1);
    if (line[0] == '!') debugger_ex(line+1);
    if (line[0] == 'b' || line[0] == 'B') debugger_b(line+1);
    if (line[0] == 'c' || line[0] == 'C') debugger_c(line+1);
    if (line[0] == 't' || line[0] == 'T') debugger_t(line+1);
    if (line[0] == 'p' || line[0] == 'P') debugger_p(line+1);
    if (line[0] == '@') debugger_run(line+1);
    if (line[0] == 'r' || line[0] == 'R') {
      cpu_reset(&cpu);
      UpdateScreen();
      }
    if (strlen(line) == 0) {
      if (tracing) {
        Disassem(cpu.pc, dis);
        Output(dis);
        }
      cpu_cycle(&cpu);
      clocks += 1;
      UpdateScreen();
      }
    }
  }



