#define MAIN

#include "header.h"

int findLabel(char* name) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcmp(labelNames[i], name) == 0) return i;
  return -1;
  }

void addLabel(char* name, word value) {
  if (pass == 2) return;
  if (findLabel(name) >= 0) {
    printf("Error: Duplicate label: %s\n",name);
    errors++;
    return;
    }
  numLabels++;
  if (numLabels == 1) {
    labelNames = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    }
  else {
    labelNames = (char**)realloc(labelNames, sizeof(char*) * numLabels);
    labelValues = (word*)realloc(labelValues, sizeof(word) * numLabels);
    }
  labelNames[numLabels-1] = (char*)malloc(strlen(name) + 1);
  strcpy(labelNames[numLabels-1], name);
  labelValues[numLabels-1] = value;
  }

word getLabel(char* name) {
  int i;
  i = findLabel(name);
  if (i >= 0) return labelValues[i];
  if (pass == 2) {
    printf("Error: Label not found: %s\n",name);
    errors++;
    }
  return 0;
  }

char* getNumber(char* line, word* dest) {
  char name[64];
  int p;
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    p = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') name[p++] = *line++;
    name[p] = 0;
    *dest =  getLabel(name);
    return line;
    }
  if (*line == '$') {
    *dest = 0;
    line++;
    while ((*line >= '0' && *line <= '9') ||
           (*line >= 'a' && *line <= 'f') ||
           (*line >= 'A' && *line <= 'F')) {
      if (*line >= '0' && *line <= '9') *dest = (*dest << 4) + (*line - '0');
      if (*line >= 'a' && *line <= 'f') *dest = (*dest << 4) + (*line - 87);
      if (*line >= 'A' && *line <= 'F') *dest = (*dest << 4) + (*line - 55);
      line++;
      }
    return line;
    }
  if (*line >= '0' && *line <= '9') {
    *dest = 0;
    while (*line >= '0' && *line <='9') {
      *dest = (*dest * 10) + (*line - '0');
      line++;
      }
    return line;
    }
  return NULL;
  }

void output(byte b) {
  char n[4];
  address++;
  if (pass == 2) {
    codeGenerated++;
    sprintf(n, " %02x", b);
    strcat(outLine, n);
    outCount++;
    if (outCount == 16) {
      fprintf(outFile, "%s\n", outLine);
      outCount = 0;
      sprintf(outLine,"%08x:", address);
      }
    }
  }

int assemblyPass(FILE* src) {
  char  line[1024];
  char *pline;
  int   p;
  int   err;
  word  opcode;
  lineNumber = 0;
  startAddress = 0;
  linesAssembled = 0;
  codeGenerated = 0;
  while (!feof(src)) {
    fgets(line, 1023, src);
    linesAssembled++;
    while (strlen(line) > 0 && line[strlen(line)-1] <= ' ') line[strlen(line)-1] = 0;
    strcpy(srcLine, line);
    strcpy(label, "");
    lineNumber++;
    pline = line;
    if ((*pline >= 'a' && *pline <= 'z') ||
        (*pline >= 'A' && *pline <= 'Z')) {
      p = 0;
      while ((*pline >= 'a' && *pline <= 'z') ||
             (*pline >= 'A' && *pline <= 'Z') ||
             (*pline >= '0' && *pline <= '9') ||
             *pline == '_') label[p++] = *pline++;
      label[p] = 0;
      if (*pline == ':') pline++;
      if (pass == 1) addLabel(label, address);
      }
    if (*pline != 0 && *pline != 32 && *pline != '\t') {
      printf("Error: Invalid starting character on line\n");
      errors++;
      }
    else if (*pline != 0) {
      while (*pline == ' ' || *pline == '\t') pline++;
      if (strncasecmp(pline, "org", 3) == 0) {
        pline += 3;
        while (*pline == ' ' || *pline == '\t') pline++;
        getNumber(pline, &address);
        if (pass == 2) {
          if (showList != 0) printf("[%5d]                    %s\n",lineNumber, srcLine);
          if (outCount > 0) {
            fprintf(outFile, "%s\n", outLine);
            }
          sprintf(outLine,"%08x:", address);
          outCount = 0;
          }
        
        }
      else if (strncasecmp(pline, "end", 3) == 0) {
        pline += 3;
        while (*pline == ' ' || *pline == '\t') pline++;
        getNumber(pline, &startAddress);
        if (pass == 2 && showList != 0)
          printf("[%5d]                    %s\n",lineNumber, srcLine);
        }
      else {
        opcode = assemble(pline, &err);
        if (err == 0) {
          if (pass == 2 && showList != 0)
            printf("[%5d] %08x: %08x %s\n",lineNumber, address, opcode, srcLine);
          output((opcode >> 24) & 0xff);
          output((opcode >> 16) & 0xff);
          output((opcode >> 8) & 0xff);
          output(opcode & 0xff);
          }
        else {
          printf("Error: Error in line\n");
          printf(" --->  %s\n",srcLine);
          errors++;
          }
        }
      }
    }
  return 0;
  }

void assembleFile(char* filename) {
  int p;
  printf("Assembling %s...\n",filename);
  strcpy(srcName, filename);
  strcpy(baseName, filename);
  p = strlen(baseName) - 1;
  while (p > 0 && baseName[p] != '.') p--;
  if (p != 0) baseName[p] = 0;
  strcpy(listName, baseName);
  strcat(listName, ".lst");
  strcpy(outName, baseName);
  strcat(outName, ".prg");
  srcFile = fopen(srcName,"r");
  if (srcFile == NULL) {
    printf("Could not open source file: %s\n",srcName);
    return;
    }
  numLabels = 0;
  errors = 0;
  pass = 1;
  assemblyPass(srcFile);
  fclose(srcFile);
  if (errors > 0) {
    printf("Errors encountered, aborting file\n");
    return;
    }
  srcFile = fopen(srcName,"r");
  if (srcFile == NULL) {
    printf("Could not open source file: %s\n",srcName);
    return;
    }
  outFile = fopen(outName,"w");
  if (outFile == NULL) {
    printf("Could not open output file: %s\n", outName);
    fclose(srcFile);
    return;
    }
  pass = 2;
  outCount = 0;
  sprintf(outLine,"%08x:", address);
  assemblyPass(srcFile);
  if (outCount > 0) {
    fprintf(outFile, "%s\n", outLine);
    }
  fclose(srcFile);
  fclose(outFile);
  printf("\n");
  printf("Errors          : %d\n", errors);
  printf("Lines Assembled : %d\n", linesAssembled);
  printf("Code Generated  : %d\n", codeGenerated);
  }

int main(int argc, char** argv) {
  int i;
  printf("Asm/S v1.0\n");
  printf("by Michael H. Riley\n\n");
  showList = 0;
  listFile = 0;
  i = 1;
  while (i < argc) {
    if (strcmp(argv[i], "-l") == 0) showList = 0xff;
    else if (strcmp(argv[i], "-L") == 0) listFile = 0xff;
    else if (argv[i][0] == '-') {
      printf("Unknown switch encountered: %s\n",argv[i]);
      exit(1);
      }
    else assembleFile(argv[i]);
    i++;
    }
  return 0;
  }

