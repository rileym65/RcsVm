#define MAIN

#include <time.h>
#include "header.h"

#define OP_LO      0xe1
#define OP_HI      0xe0
#define OP_MOD     0x62
#define OP_DIV     0x61
#define OP_MUL     0x60
#define OP_ADD     0x50
#define OP_SUB     0x51
#define OP_SHL     0x41
#define OP_SHR     0x40
#define OP_GTE     0x35
#define OP_LTE     0x34
#define OP_GT      0x33
#define OP_LT      0x32
#define OP_NE      0x31
#define OP_EQ      0x30
#define OP_XOR     0x23
#define OP_OR      0x22
#define OP_AND     0x21
#define OP_CP      0x11
#define OP_OP      0x10
#define OP_END     0x01

int findDefine(char* name) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcmp(defineNames[i], name) == 0) return i;
  return -1;
  }

void addDefine(char* name, char* value) {
  if (findDefine(name) >= 0) {
    printf("Error: Duplicate define: %s\n",name);
    errors++;
    return;
    }
  numDefines++;
  if (numDefines == 1) {
    defineNames = (char**)malloc(sizeof(char*));
    defineValues = (char**)malloc(sizeof(char*));
    }
  else {
    defineNames = (char**)realloc(defineNames, sizeof(char*) * numDefines);
    defineValues = (char**)realloc(defineValues, sizeof(char*) * numDefines);
    }
  defineNames[numDefines-1] = (char*)malloc(strlen(name) + 1);
  strcpy(defineNames[numDefines-1], name);
  defineValues[numDefines-1] = (char*)malloc(strlen(value) + 1);
  strcpy(defineValues[numDefines-1], value);
  }

char* getDefine(char* name) {
  int i;
  i = findDefine(name);
  if (i >= 0) return defineValues[i];
  return NULL;
  }



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
  word numbers[128];
  byte ops[128];
  byte nsp;
  byte osp;
  char name[64];
  int  flag;
  int p;
  word v;
  byte op;
  osp = 0;
  nsp = 0;
  while (*line == ' ' || *line == '\t') line++;
  while (*line != 0 && *line != ',' && *line != ']') {
    flag = -1;
    while (flag) {
      flag = 0;
      if (*line == '(') {
        ops[osp++] = OP_OP;
        line++;
        flag = -1;
        }
      else if (strncasecmp(line,"%HI(",4) == 0) {
        ops[osp++] = OP_HI;
        ops[osp++] = OP_OP;
        line += 4;
        flag = -1;
        }
      else if (strncasecmp(line,"%LO(",4) == 0) {
        ops[osp++] = OP_LO;
        ops[osp++] = OP_OP;
        line += 4;
        flag = -1;
        }
      while (*line == ' ' || *line == '\t') line++;
      }
    if (*line == '\'') {
      line++;
      numbers[nsp++] = *line++;
      if (*line != '\'') {
        printf("Error: Character constant more than 1 character\n");
        errors++;
        return NULL;
        }
      line++;
      }
    else if (strncasecmp(line, "[build]",7) == 0) {
      numbers[nsp++] = buildNumber;
      line += 7;
      }
    else if (strncasecmp(line, "[hour]",6) == 0) {
      numbers[nsp++] = buildHour;
      line += 6;
      }
    else if (strncasecmp(line, "[minute]",8) == 0) {
      numbers[nsp++] = buildMinute;
      line += 8;
      }
    else if (strncasecmp(line, "[second]",8) == 0) {
      numbers[nsp++] = buildSecond;
      line += 8;
      }
    else if (strncasecmp(line, "[year]",6) == 0) {
      numbers[nsp++] = buildYear;
      line += 6;
      }
    else if (strncasecmp(line, "[month]",7) == 0) {
      numbers[nsp++] = buildMonth;
      line += 7;
      }
    else if (strncasecmp(line, "[day]",5) == 0) {
      numbers[nsp++] = buildDay;
      line += 5;
      }
    else if ((*line >= 'a' && *line <= 'z') ||
        (*line >= 'A' && *line <= 'Z')) {
      p = 0;
      while ((*line >= 'a' && *line <= 'z') ||
             (*line >= 'A' && *line <= 'Z') ||
             (*line >= '0' && *line <= '9') ||
             *line == '_') name[p++] = *line++;
      name[p] = 0;
      numbers[nsp++] =  getLabel(name);
      }
    else if (*line == '$') {
      v = 0;
      line++;
      while ((*line >= '0' && *line <= '9') ||
             (*line >= 'a' && *line <= 'f') ||
             (*line >= 'A' && *line <= 'F')) {
        if (*line >= '0' && *line <= '9') v = (v << 4) + (*line - '0');
        if (*line >= 'a' && *line <= 'f') v = (v << 4) + (*line - 87);
        if (*line >= 'A' && *line <= 'F') v = (v << 4) + (*line - 55);
        line++;
        }
      numbers[nsp++] = v;
      }
    else if (*line >= '0' && *line <= '9') {
      v = 0;
      while (*line >= '0' && *line <='9') {
        v = (v * 10) + (*line - '0');
        line++;
        }
      numbers[nsp++] = v;
      }
    else {
      return NULL;
      }
    while (*line == ' ' || *line == '\t') line++;
    
    flag = -1;
    while (flag) {
      flag = 0;
      if (*line == '+') { op = OP_ADD; line++; }
      else if (*line == '-') { op = OP_SUB; line++; }
      else if (*line == '*') { op = OP_MUL; line++; }
      else if (*line == '/') { op = OP_DIV; line++; }
      else if (*line == '%') { op = OP_MOD; line++; }
      else if (*line == '&') { op = OP_AND; line++; }
      else if (*line == '|') { op = OP_OR; line++; }
      else if (*line == '^') { op = OP_XOR; line++; }
      else if (*line == '=') { op = OP_EQ; line++; }
      else if (*line == '<' && *(line+1) == '>') { op = OP_NE; line+=2; }
      else if (*line == '<' && *(line+1) == '=') { op = OP_LTE; line+=2; }
      else if (*line == '<' && *(line+1) == '<') { op = OP_SHL; line+=2; }
      else if (*line == '<') { op = OP_LT; line++; }
      else if (*line == '>' && *(line+1) == '=') { op = OP_GTE; line+=2; }
      else if (*line == '>' && *(line+1) == '>') { op = OP_SHR; line+=2; }
      else if (*line == '>') { op = OP_GT; line++; }
      else if (*line == ')') { op = OP_CP; line++; }
      else if (*line == ',') op = OP_END;
      else if (*line == ']') op = OP_END;
      else if (*line == 0) op = OP_END;
      else op = 0;
      if (op == 0) {
        printf("Error: Expression error\n");
        return NULL;
        }
      while (osp > 0 && (op & 0xf0) <= (ops[osp-1] & 0xf0)) {
        if (nsp > 0 && ops[osp-1] == OP_HI) {
          numbers[nsp - 1] = numbers[nsp -1] >> 10;
          osp--;
          }
        else if (nsp > 0 && ops[osp-1] == OP_LO) {
          numbers[nsp - 1] = numbers[nsp -1] & 0x3ff;
          osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_ADD) {
          numbers[nsp - 2] += numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_SUB) {
          numbers[nsp - 2] -= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_MUL) {
          numbers[nsp - 2] *= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_MOD) {
          numbers[nsp - 2] %= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_DIV) {
          numbers[nsp - 2] /= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_AND) {
          numbers[nsp - 2] &= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_OR) {
          numbers[nsp - 2] |= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_XOR) {
          numbers[nsp - 2] ^= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_SHL) {
          numbers[nsp - 2] <<= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_SHR) {
          numbers[nsp - 2] >>= numbers[nsp -1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_EQ) {
          numbers[nsp-2] = numbers[nsp-2] == numbers[nsp-1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_NE) {
          numbers[nsp-2] = numbers[nsp-2] != numbers[nsp-1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_LT) {
          numbers[nsp-2] = numbers[nsp-2] < numbers[nsp-1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_LTE) {
          numbers[nsp-2] = numbers[nsp-2] <= numbers[nsp-1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_GT) {
          numbers[nsp-2] = numbers[nsp-2] > numbers[nsp-1];
          nsp--; osp--;
          }
        else if (nsp > 1 && ops[osp-1] == OP_GTE) {
          numbers[nsp-2] = numbers[nsp-2] >= numbers[nsp-1];
          nsp--; osp--;
          }
        else if (op == OP_CP && ops[osp-1] == OP_OP) {
          osp--;
          op = 0xff;
          flag = -1;
          }
        }
      if (op != 0xff) ops[osp++] = op;
      while (*line == ' ' || *line == '\t') line++;
      }
    }
  if (nsp != 1) {
    printf("Error: Expression did not reduce to single term\n");
    return NULL;
    }
  *dest = numbers[0];
  return line;
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

char* trim(char* buffer) {
  while (*buffer == ' '|| *buffer == '\t') buffer++;
  return buffer;
  }

int nextLine(char* buffer, int maxLen) {
  char *line;
  char *pchar;
  int   flag;
  int   rflag;
  char  tmp[1024];
  int   i;
  word  value;
  flag = 0;
  while (flag == 0) {
    flag = -1;
    line=buffer;
    while (numFiles > 1 && feof(files[numFiles-1])) {
      fclose(files[numFiles-1]);
      numFiles--;
      }
    if (feof(files[numFiles-1])) {
      strcpy(buffer, "");
      return 0;
      }
    fgets(line, maxLen, files[numFiles-1]);

    rflag = -1;
    while (rflag) {
      rflag = 0;
      for (i=0; i<numDefines; i++) {
        pchar = strstr(buffer, defineNames[i]);
        if (pchar != NULL) {
          strncpy(tmp, buffer, pchar-buffer);
          tmp[pchar-buffer] = 0;
          strcat(tmp, defineValues[i]);
          strcat(tmp, pchar+strlen(defineNames[i]));
          strcpy(buffer,tmp);
          rflag = -1;
          }
        }
      }


    while (strlen(line) > 0 && line[strlen(line)-1] <= ' ')
      line[strlen(line)-1] = 0;
    fileLines[numFiles-1]++;
    if (strncmp(line,"#include ",9) == 0) {
      flag = 0;
      line += 9;
      line = trim(line);
      files[numFiles] = fopen(line,"r");
      if (files[numFiles] == NULL) {
        printf("Could not open include file: <<%s>>\n",line);
        return -1;
        }
      fileLines[numFiles] = 0;
      numFiles++;
      }
    else if (strncmp(line,"#define ",8) == 0) {
      flag = 0;
      line += 8;
      line = trim(line);
      pchar = strchr(line,' ');
      if (pchar != NULL) {
        *pchar = 0;
        pchar++;
        pchar = trim(pchar);
        addDefine(line, pchar);
        }
      else {
        addDefine(line,"1");
        }
      }
    else if (strncmp(line,"#ifdef ",7) == 0) {
      flag = 0;
      if (numCond > 0 &&
          (cond[numCond-1] == 'N' || cond[numCond-1] == 'I')) {
        cond[numCond++] = 'I';
        }
      else {
        line += 6;
        line = trim(line);
        pchar = strchr(line,' ');
        if (pchar != NULL) *pchar = 0;
        pchar = getDefine(line);
        if (pchar == NULL) {
          cond[numCond++] = 'N';
          }
        else if (strcmp(pchar,"0") == 0) {
          cond[numCond++] = 'N';
          }
        else cond[numCond++] = 'Y';
        }
      }
    else if (strncmp(line,"#ifndef ",8) == 0) {
      flag = 0;
      if (numCond > 0 &&
          (cond[numCond-1] == 'N' || cond[numCond-1] == 'I')) {
        cond[numCond++] = 'I';
        }
      else {
        line += 7;
        line = trim(line);
        pchar = strchr(line,' ');
        if (pchar != NULL) *pchar = 0;
        pchar = getDefine(line);
        if (pchar == NULL) {
          cond[numCond++] = 'Y';
          }
        else if (strcmp(pchar,"0") == 0) {
          cond[numCond++] = 'Y';
          }
        else cond[numCond++] = 'N';
        }
      }
    else if (strncmp(line,"#if ",4) == 0) {
      flag = 0;
      if (numCond > 0 &&
          (cond[numCond-1] == 'N' || cond[numCond-1] == 'I')) {
        cond[numCond++] = 'I';
        }
      else {
        line += 4;
        line = trim(line);
        getNumber(line, &value);
        if (value == 0) {
          cond[numCond++] = 'N';
          }
        else cond[numCond++] = 'Y';
        }
      }
    else if (strncmp(line,"#else",5) == 0) {
      flag = 0;
      if (numCond == 0) {
        printf("Error: #else outside #ifdef\n");
        errors++;
        }
      else {
        if (cond[numCond-1] == 'N') cond[numCond-1] = 'Y';
        else if (cond[numCond-1] == 'Y') cond[numCond-1] = 'N';
        }
      }
    else if (strncmp(line,"#endif",6) == 0) {
      flag = 0;
      if (numCond == 0) {
        printf("Error: Unmatched #endif\n");
        errors++;
        }
      else numCond--;
      }

    else if (numCond > 0 && cond[numCond-1] == 'I') flag = 0;
    else if (numCond > 0 && cond[numCond-1] == 'N') flag = 0;
    }
  
  if (numFiles > 1) sprintf(lineNo,"<%5d>", fileLines[numFiles-1]);
    else sprintf(lineNo,"[%5d]", fileLines[numFiles-1]);


  return 0;
  }

int assemblyPass(FILE* src) {
  char  line[1024];
  char  oline[256];
  char  tmp[16];
  char *pline;
  int   p;
  int   err;
  word  opcode;
  word  value;
  int   count;
  int   qt;
  int   i;
  numFiles = 0;
  files[numFiles++] = src;
  fileLines[numFiles-1] = 0;
  lineNumber = 0;
  startAddress = 0;
  linesAssembled = 0;
  codeGenerated = 0;
  numDefines = 0;
  numCond = 0;
  while (!feof(src)) {
    if (nextLine(line, 1023) == -1) {
      printf("Error: Unexpected file error\n");
      exit(1);
      }
    linesAssembled++;
    strcpy(srcLine, line);
    strcpy(label, "");
    lineNumber++;
    pline = strchr(line, ';');
    if (pline != NULL) {
      *pline = 0;
      while (strlen(line) > 0 && line[strlen(line)-1] <= ' ') line[strlen(line)-1] = 0;
      }
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
    if (*pline != 0 && *pline != 32 && *pline != '\t' && *pline != '.') {
      printf("Error: Invalid starting character on line\n");
printf("-->%s\n",srcLine);
      errors++;
      }
    else if (*pline != 0) {
      while (*pline == ' ' || *pline == '\t') pline++;

      if (strncasecmp(pline, ".align word", 11) == 0) {
        if (outCount > 0) {
          fprintf(outFile, "%s\n", outLine);
          }
        address = (address + 3) & 0xfffffffc;
        sprintf(outLine,"%08x:", address);
        outCount = 0;
        if (pass == 2) {
          if (showList != 0) printf("%7s                    %s\n",lineNo, srcLine);
          }
        }

      else if (strncasecmp(pline, ".align para", 11) == 0) {
        if (outCount > 0) {
          fprintf(outFile, "%s\n", outLine);
          }
        address = (address + 15) & 0xfffffff0;
        sprintf(outLine,"%08x:", address);
        outCount = 0;
        if (pass == 2) {
          if (showList != 0) printf("%7s                    %s\n",lineNo, srcLine);
          }
        }

      else if (strncasecmp(pline, ".align page", 11) == 0) {
        if (outCount > 0) {
          fprintf(outFile, "%s\n", outLine);
          }
        address = (address + 255) & 0xffffff00;
        sprintf(outLine,"%08x:", address);
        outCount = 0;
        if (pass == 2) {
          if (showList != 0) printf("%7s                    %s\n",lineNo, srcLine);
          }
        }

      else if (strncasecmp(pline, "org", 3) == 0) {
        pline += 3;
        while (*pline == ' ' || *pline == '\t') pline++;
        getNumber(pline, &address);
        if (pass == 2) {
          if (showList != 0) printf("%7s                    %s\n",lineNo, srcLine);
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
          printf("%7s                    %s\n",lineNo, srcLine);
        }

      else if (strncasecmp(pline, "db", 2) == 0) {
        pline += 2;
        qt = 0;
        sprintf(oline,"%7s %08x: ",lineNo, address);
        count = 0;
        while (*pline == ' ' || *pline == '\t') pline++;
        while (pline != NULL && *pline != 0) {
          if (*pline == '"') {
            qt = qt ^0xff;
            pline++;
            if (qt == 0) {
              while (*pline == ' ' || *pline == '\t') pline++;
              if (*pline == ',') pline++;
              while (*pline == ' ' || *pline == '\t') pline++;
              }
            }
          else {
            if (qt) value = *pline++;
              else pline = getNumber(pline, &value);
            if (pline != NULL) {
              count++;
              sprintf(tmp,"%02x",value & 0xff);
              strcat(oline, tmp);
              if ((count % 4) == 0) {
                if (count == 4) {
                  strcat(oline, " ");
                  strcat(oline, srcLine);
                  if (pass == 2 && showList != 0)
                    printf("%s\n",oline);
                  }
                else if (pass == 2 && showList != 0)
                  printf("%s\n",oline);
                strcpy(oline,"                  ");
                }
              output(value & 0xff);
              if (*pline != 0 && *pline != ',' && qt == 0) {
                printf("Error: Syntax error\n");
                pline = NULL;
                }
              else if (*pline == ',' && qt == 0) pline++;
              }
            if (pline != NULL && qt == 0)
              while (*pline == ' ' || *pline == '\t') pline++;
            }
          }
        if (pass == 2 && showList != 0 && (count % 4) != 0) {
          if (count < 4) {
            while (strlen(oline) < 27) strcat(oline," ");
            strcat(oline, srcLine);
            }
          printf("%s\n",oline);
          }
        }

      else if (strncasecmp(pline, "dh", 2) == 0) {
        pline += 2;
        sprintf(oline,"%7s %08x: ",lineNo, address);
        count = 0;
        while (*pline == ' ' || *pline == '\t') pline++;
        while (pline != NULL && *pline != 0) {
          pline = getNumber(pline, &value);
          if (pline != NULL) {
            count++;
            sprintf(tmp,"%04x",value & 0xffff);
            strcat(oline, tmp);
            if ((count % 2) == 0) {
              if (count == 2) {
                strcat(oline, " ");
                strcat(oline, srcLine);
                if (pass == 2 && showList != 0)
                  printf("%s\n",oline);
                }
              else if (pass == 2 && showList != 0)
                printf("%s\n",oline);
              strcpy(oline,"                  ");
              }
            output((value >> 8) & 0xff);
            output(value & 0xff);
            if (*pline != 0 && *pline != ',') {
              printf("Error: Syntax error\n");
              pline = NULL;
              }
            else if (*pline == ',') pline++;
            }
          if (pline != NULL)
            while (*pline == ' ' || *pline == '\t') pline++;
          }
        if (pass == 2 && showList != 0 && (count % 2) != 0) {
          if (count < 2) {
            while (strlen(oline) < 27) strcat(oline," ");
            strcat(oline, srcLine);
            }
          printf("%s\n",oline);
          }
        }

      else if (strncasecmp(pline, "dw", 2) == 0) {
        pline += 2;
        sprintf(oline,"%7s %08x: ",lineNo, address);
        count = 0;
        while (*pline == ' ' || *pline == '\t') pline++;
        while (pline != NULL && *pline != 0) {
          pline = getNumber(pline, &value);
          if (pline != NULL) {
            count++;
            sprintf(tmp,"%08x",value);
            strcat(oline, tmp);
            if (count == 1) {
              strcat(oline, " ");
              strcat(oline, srcLine);
              if (pass == 2 && showList != 0)
                printf("%s\n",oline);
              }
            else if (pass == 2 && showList != 0)
              printf("%s\n",oline);
            strcpy(oline,"                  ");
            output((value >> 24) & 0xff);
            output((value >> 16) & 0xff);
            output((value >> 8) & 0xff);
            output(value & 0xff);
            if (*pline != 0 && *pline != ',') {
              printf("Error: Syntax error\n");
              pline = NULL;
              }
            else if (*pline == ',') pline++;
            }
          if (pline != NULL)
            while (*pline == ' ' || *pline == '\t') pline++;
          }
        }

      else {
        opcode = assemble(pline, &err);
        if (err == 0) {
          if (pass == 2 && showList != 0)
            printf("%7s %08x: %08x %s\n",lineNo, address, opcode, srcLine);
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
  if (numDefines > 0) {
    for (i=0; i<numDefines; i++) {
      free(defineNames[i]);
      free(defineValues[i]);
      }
    free(defineNames);
    free(defineValues);
    numDefines = 0;
    }
  return 0;
  }

void assembleFile(char* filename) {
  int p;
  char buildName[1024];
  FILE *buildFile;
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
  strcpy(buildName, baseName);
  strcat(buildName, ".build");
  buildFile = fopen(buildName, "r");
  if (buildFile == NULL) {
    buildNumber = 1;
    }
  else {
    fscanf(buildFile,"%d",&buildNumber);
    fclose(buildFile);
    buildNumber++;
    }
  buildFile = fopen(buildName, "w");
  fprintf(buildFile, "%d\n",buildNumber);
  fclose(buildFile);
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
  if (startAddress != 0)
    fprintf(outFile,"@%x\n", startAddress);
  fclose(srcFile);
  fclose(outFile);
  printf("\n");
  printf("Errors          : %d\n", errors);
  printf("Lines Assembled : %d\n", linesAssembled);
  printf("Code Generated  : %d\n", codeGenerated);
  }

int main(int argc, char** argv) {
  int i;
  struct tm buildTime;
  time_t    tt;
  printf("Asm/S v1.0\n");
  printf("by Michael H. Riley\n\n");
  tt = time(NULL);
  localtime_r(&tt, &buildTime);
  buildYear = buildTime.tm_year + 1900;
  buildMonth = buildTime.tm_mon + 1;
  buildDay = buildTime.tm_mday;
  buildHour = buildTime.tm_hour;
  buildMinute = buildTime.tm_min;
  buildSecond = buildTime.tm_sec;
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

