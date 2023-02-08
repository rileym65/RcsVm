#include <stdio.h>
#include <string.h>
#include <sys/types.h>

typedef u_int8_t  byte;
typedef u_int16_t halfword;
typedef u_int32_t word;
typedef u_int64_t dword;
typedef int32_t   sword;

typedef struct {
  char *pattern;
  char *trans;
  int   atype;
  } OPS;

OPS ops[] = {
  { "LDSB [%r+%r],%r",    "11CCCCC001001AAAAA000000000BBBBB", 0 },
  { "LDSB [%r+i],%r",     "11CCCCC001001AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDSB [%r-n],%r",     "11CCCCC001001AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDSH [%r+%r],%r",    "11CCCCC001010AAAAA000000000BBBBB", 0 },
  { "LDSH [%r+i],%r",     "11CCCCC001010AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDSH [%r-n],%r",     "11CCCCC001010AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDUB [%r+%r],%r",    "11CCCCC000001AAAAA000000000BBBBB", 0 },
  { "LDUB [%r+i],%r",     "11CCCCC000001AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDUB [%r-n],%r",     "11CCCCC000001AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDUH [%r+%r],%r",    "11CCCCC000010AAAAA000000000BBBBB", 0 },
  { "LDUH [%r+i],%r",     "11CCCCC000010AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDUH [%r-n],%r",     "11CCCCC000010AAAAA1BBBBBBBBBBBBB", 0 },
  { "LD [%r+%r],%r",      "11CCCCC000000AAAAA000000000BBBBB", 0 },
  { "LD [%r+i],%r",       "11CCCCC000000AAAAA1BBBBBBBBBBBBB", 0 },
  { "LD [%r-n],%r",       "11CCCCC000000AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDD [%r+%r],%r",     "11CCCCC000011AAAAA000000000BBBBB", 0 },
  { "LDD [%r+i],%r",      "11CCCCC000011AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDD [%r-n],%r",      "11CCCCC000011AAAAA1BBBBBBBBBBBBB", 0 },
  { "LD [%r+%r],%f",      "11CCCCC100000AAAAA000000000BBBBB", 0 },
  { "LD [%r+i],%f",       "11CCCCC100000AAAAA1BBBBBBBBBBBBB", 0 },
  { "LD [%r-n],%f",       "11CCCCC100000AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDD [%r+%r],%f",     "11CCCCC100011AAAAA000000000BBBBB", 0 },
  { "LDD [%r+i],%f",      "11CCCCC100011AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDD [%r-n],%f",      "11CCCCC100011AAAAA1BBBBBBBBBBBBB", 0 },
  { "LD [%r+%r],%FSR",    "11CCCCC100001AAAAA000000000BBBBB", 0 },
  { "LD [%r+i],%FSR",     "11CCCCC100001AAAAA1BBBBBBBBBBBBB", 0 },
  { "LD [%r-n],%FSR",     "11CCCCC100001AAAAA1BBBBBBBBBBBBB", 0 },
  { "STB %r,[%r+%r]",     "11AAAAA000101BBBBB000000000CCCCC", 0 },
  { "STB %r,[%r+i]",      "11AAAAA000101BBBBB1CCCCCCCCCCCCC", 0 },
  { "STB %r,[%r-n]",      "11AAAAA000101BBBBB1CCCCCCCCCCCCC", 0 },
  { "STH %r,[%r+%r]",     "11AAAAA000110BBBBB000000000CCCCC", 0 },
  { "STH %r,[%r+i]",      "11AAAAA000110BBBBB1CCCCCCCCCCCCC", 0 },
  { "STH %r,[%r-n]",      "11AAAAA000110BBBBB1CCCCCCCCCCCCC", 0 },
  { "ST %r,[%r+%r]",      "11AAAAA000100BBBBB000000000CCCCC", 0 },
  { "ST %r,[%r+i]",       "11AAAAA000100BBBBB1CCCCCCCCCCCCC", 0 },
  { "ST %r,[%r-n]",       "11AAAAA000100BBBBB1CCCCCCCCCCCCC", 0 },
  { "STD %r,[%r+%r]",     "11AAAAA000111BBBBB000000000CCCCC", 0 },
  { "STD %r,[%r+i]",      "11AAAAA000111BBBBB1CCCCCCCCCCCCC", 0 },
  { "STD %r,[%r-n]",      "11AAAAA000111BBBBB1CCCCCCCCCCCCC", 0 },
  { "ST %FSR,[%r+%r]",    "1100000100101AAAAA000000000BBBBB", 0 },
  { "ST %FSR,[%r+i]",     "1100000100101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ST %FSR,[%r-n]",     "1100000100101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ST %f,[%r+%r]",      "11AAAAA100100BBBBB000000000CCCCC", 0 },
  { "ST %f,[%r+i]",       "11AAAAA100100BBBBB1CCCCCCCCCCCCC", 0 },
  { "ST %f,[%r-n]",       "11AAAAA100100BBBBB1CCCCCCCCCCCCC", 0 },
  { "STD %f,[%r+%r]",     "11AAAAA100111BBBBB000000000CCCCC", 0 },
  { "STD %f,[%r+i]",      "11AAAAA100111BBBBB1CCCCCCCCCCCCC", 0 },
  { "STD %f,[%r-n]",      "11AAAAA100111BBBBB1CCCCCCCCCCCCC", 0 },
  { "LDSTUB [%r+%r],%r",  "11CCCCC001101AAAAA000000000BBBBB", 0 },
  { "LDSTUB [%r+i],%r",   "11CCCCC001101AAAAA1BBBBBBBBBBBBB", 0 },
  { "LDSTUB [%r-n],%r",   "11CCCCC001101AAAAA1BBBBBBBBBBBBB", 0 },
  { "SWAP [%r+%r],%r",    "11CCCCC001111AAAAA000000000BBBBB", 0 },
  { "SWAP [%r+i],%r",     "11CCCCC001111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SWAP [%r-n],%r",     "11CCCCC001111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SETHI i,%r",         "00BBBBB100AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "SETHI +i,%r",        "00BBBBB100AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "SETHI -n,%r",        "00BBBBB100AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "AND %r,%r,%r",       "10CCCCC000001AAAAA000000000BBBBB", 0 },
  { "AND %r,i,%r",        "10CCCCC000001AAAAA1BBBBBBBBBBBBB", 0 },
  { "AND %r,+i,%r",       "10CCCCC000001AAAAA1BBBBBBBBBBBBB", 0 },
  { "AND %r,-n,%r",       "10CCCCC000001AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDCC %r,%r,%r",     "10CCCCC010001AAAAA000000000BBBBB", 0 },
  { "ANDCC %r,i,%r",      "10CCCCC010001AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDCC %r,+i,%r",     "10CCCCC010001AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDCC %r,-n,%r",     "10CCCCC010001AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDN %r,%r,%r",      "10CCCCC000101AAAAA000000000BBBBB", 0 },
  { "ANDN %r,i,%r",       "10CCCCC000101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDN %r,+i,%r",      "10CCCCC000101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDN %r,-n,%r",      "10CCCCC000101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDNCC %r,%r,%r",    "10CCCCC010101AAAAA000000000BBBBB", 0 },
  { "ANDNCC %r,i,%r",     "10CCCCC010101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDNCC %r,+i,%r",    "10CCCCC010101AAAAA1BBBBBBBBBBBBB", 0 },
  { "ANDNCC %r,-n,%r",    "10CCCCC010101AAAAA1BBBBBBBBBBBBB", 0 },
  { "OR %r,%r,%r",        "10CCCCC000010AAAAA000000000BBBBB", 0 },
  { "OR %r,i,%r",         "10CCCCC000010AAAAA1BBBBBBBBBBBBB", 0 },
  { "OR %r,+i,%r",        "10CCCCC000010AAAAA1BBBBBBBBBBBBB", 0 },
  { "OR %r,-n,%r",        "10CCCCC000010AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORCC %r,%r,%r",      "10CCCCC010010AAAAA000000000BBBBB", 0 },
  { "ORCC %r,i,%r",       "10CCCCC010010AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORCC %r,+i,%r",      "10CCCCC010010AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORCC %r,-n,%r",      "10CCCCC010010AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORN %r,%r,%r",       "10CCCCC000110AAAAA000000000BBBBB", 0 },
  { "ORN %r,i,%r",        "10CCCCC000110AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORN %r,+i,%r",       "10CCCCC000110AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORN %r,-n,%r",       "10CCCCC000110AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORNCC %r,%r,%r",     "10CCCCC010110AAAAA000000000BBBBB", 0 },
  { "ORNCC %r,i,%r",      "10CCCCC010110AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORNCC %r,+i,%r",     "10CCCCC010110AAAAA1BBBBBBBBBBBBB", 0 },
  { "ORNCC %r,-n,%r",     "10CCCCC010110AAAAA1BBBBBBBBBBBBB", 0 },
  { "XOR %r,%r,%r",       "10CCCCC000011AAAAA000000000BBBBB", 0 },
  { "XOR %r,i,%r",        "10CCCCC000011AAAAA1BBBBBBBBBBBBB", 0 },
  { "XOR %r,+i,%r",       "10CCCCC000011AAAAA1BBBBBBBBBBBBB", 0 },
  { "XOR %r,-n,%r",       "10CCCCC000011AAAAA1BBBBBBBBBBBBB", 0 },
  { "XORCC %r,%r,%r",     "10CCCCC010011AAAAA000000000BBBBB", 0 },
  { "XORCC %r,i,%r",      "10CCCCC010011AAAAA1BBBBBBBBBBBBB", 0 },
  { "XORCC %r,+i,%r",     "10CCCCC010011AAAAA1BBBBBBBBBBBBB", 0 },
  { "XORCC %r,-n,%r",     "10CCCCC010011AAAAA1BBBBBBBBBBBBB", 0 },
  { "XNOR %r,%r,%r",      "10CCCCC000111AAAAA000000000BBBBB", 0 },
  { "XNOR %r,i,%r",       "10CCCCC000111AAAAA1BBBBBBBBBBBBB", 0 },
  { "XNOR %r,+i,%r",      "10CCCCC000111AAAAA1BBBBBBBBBBBBB", 0 },
  { "XNOR %r,-n,%r",      "10CCCCC000111AAAAA1BBBBBBBBBBBBB", 0 },
  { "XNORCC %r,%r,%r",    "10CCCCC010111AAAAA000000000BBBBB", 0 },
  { "XNORCC %r,i,%r",     "10CCCCC010111AAAAA1BBBBBBBBBBBBB", 0 },
  { "XNORCC %r,+i,%r",    "10CCCCC010111AAAAA1BBBBBBBBBBBBB", 0 },
  { "XNORCC %r,-n,%r",    "10CCCCC010111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SLL %r,%r,%r",       "10CCCCC100101AAAAA000000000BBBBB", 0 },
  { "SLL %r,i,%r",        "10CCCCC100101AAAAA1BBBBBBBBBBBBB", 0 },
  { "SLL %r,+i,%r",       "10CCCCC100101AAAAA1BBBBBBBBBBBBB", 0 },
  { "SLL %r,-n,%r",       "10CCCCC100101AAAAA1BBBBBBBBBBBBB", 0 },
  { "SRL %r,%r,%r",       "10CCCCC100110AAAAA000000000BBBBB", 0 },
  { "SRL %r,i,%r",        "10CCCCC100110AAAAA1BBBBBBBBBBBBB", 0 },
  { "SRL %r,+i,%r",       "10CCCCC100110AAAAA1BBBBBBBBBBBBB", 0 },
  { "SRL %r,-n,%r",       "10CCCCC100110AAAAA1BBBBBBBBBBBBB", 0 },
  { "SRA %r,%r,%r",       "10CCCCC100111AAAAA000000000BBBBB", 0 },
  { "SRA %r,i,%r",        "10CCCCC100111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SRA %r,+i,%r",       "10CCCCC100111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SRA %r,-n,%r",       "10CCCCC100111AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADD %r,%r,%r",       "10CCCCC000000AAAAA000000000BBBBB", 0 },
  { "ADD %r,i,%r",        "10CCCCC000000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADD %r,+i,%r",       "10CCCCC000000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADD %r,-n,%r",       "10CCCCC000000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDCC %r,%r,%r",     "10CCCCC010000AAAAA000000000BBBBB", 0 },
  { "ADDCC %r,i,%r",      "10CCCCC010000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDCC %r,+i,%r",     "10CCCCC010000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDCC %r,-n,%r",     "10CCCCC010000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDX %r,%r,%r",      "10CCCCC001000AAAAA000000000BBBBB", 0 },
  { "ADDX %r,i,%r",       "10CCCCC001000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDX %r,+i,%r",      "10CCCCC001000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDX %r,-n,%r",      "10CCCCC001000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDXCC %r,%r,%r",    "10CCCCC011000AAAAA000000000BBBBB", 0 },
  { "ADDXCC %r,i,%r",     "10CCCCC011000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDXCC %r,+i,%r",    "10CCCCC011000AAAAA1BBBBBBBBBBBBB", 0 },
  { "ADDXCC %r,-n,%r",    "10CCCCC011000AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUB %r,%r,%r",       "10CCCCC000100AAAAA000000000BBBBB", 0 },
  { "SUB %r,i,%r",        "10CCCCC000100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUB %r,+i,%r",       "10CCCCC000100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUB %r,-n,%r",       "10CCCCC000100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBCC %r,%r,%r",     "10CCCCC010100AAAAA000000000BBBBB", 0 },
  { "SUBCC %r,i,%r",      "10CCCCC010100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBCC %r,+i,%r",     "10CCCCC010100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBCC %r,-n,%r",     "10CCCCC010100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBX %r,%r,%r",      "10CCCCC001100AAAAA000000000BBBBB", 0 },
  { "SUBX %r,i,%r",       "10CCCCC001100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBX %r,+i,%r",      "10CCCCC001100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBX %r,-n,%r",      "10CCCCC001100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBXCC %r,%r,%r",    "10CCCCC011100AAAAA000000000BBBBB", 0 },
  { "SUBXCC %r,i,%r",     "10CCCCC011100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBXCC %r,+i,%r",    "10CCCCC011100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SUBXCC %r,-n,%r",    "10CCCCC011100AAAAA1BBBBBBBBBBBBB", 0 },
  { "UMUL %r,%r,%r",      "10CCCCC001010AAAAA000000000BBBBB", 0 },
  { "UMUL %r,i,%r",       "10CCCCC001010AAAAA1BBBBBBBBBBBBB", 0 },
  { "UMUL %r,+i,%r",      "10CCCCC001010AAAAA1BBBBBBBBBBBBB", 0 },
  { "UMUL %r,-n,%r",      "10CCCCC001010AAAAA1BBBBBBBBBBBBB", 0 },
  { "UMULCC %r,%r,%r",    "10CCCCC011010AAAAA000000000BBBBB", 0 },
  { "UMULCC %r,i,%r",     "10CCCCC011010AAAAA1BBBBBBBBBBBBB", 0 },
  { "UMULCC %r,+i,%r",    "10CCCCC011010AAAAA1BBBBBBBBBBBBB", 0 },
  { "UMULCC %r,-n,%r",    "10CCCCC011010AAAAA1BBBBBBBBBBBBB", 0 },
  { "SMUL %r,%r,%r",      "10CCCCC001011AAAAA000000000BBBBB", 0 },
  { "SMUL %r,i,%r",       "10CCCCC001011AAAAA1BBBBBBBBBBBBB", 0 },
  { "SMUL %r,+i,%r",      "10CCCCC001011AAAAA1BBBBBBBBBBBBB", 0 },
  { "SMUL %r,-n,%r",      "10CCCCC001011AAAAA1BBBBBBBBBBBBB", 0 },
  { "SMULCC %r,%r,%r",    "10CCCCC011011AAAAA000000000BBBBB", 0 },
  { "SMULCC %r,i,%r",     "10CCCCC011011AAAAA1BBBBBBBBBBBBB", 0 },
  { "SMULCC %r,+i,%r",    "10CCCCC011011AAAAA1BBBBBBBBBBBBB", 0 },
  { "SMULCC %r,-n,%r",    "10CCCCC011011AAAAA1BBBBBBBBBBBBB", 0 },
  { "UDIV %r,%r,%r",      "10CCCCC001110AAAAA000000000BBBBB", 0 },
  { "UDIV %r,i,%r",       "10CCCCC001110AAAAA1BBBBBBBBBBBBB", 0 },
  { "UDIV %r,+i,%r",      "10CCCCC001110AAAAA1BBBBBBBBBBBBB", 0 },
  { "UDIV %r,-n,%r",      "10CCCCC001110AAAAA1BBBBBBBBBBBBB", 0 },
  { "UDIVCC %r,%r,%r",    "10CCCCC011110AAAAA000000000BBBBB", 0 },
  { "UDIVCC %r,i,%r",     "10CCCCC011110AAAAA1BBBBBBBBBBBBB", 0 },
  { "UDIVCC %r,+i,%r",    "10CCCCC011110AAAAA1BBBBBBBBBBBBB", 0 },
  { "UDIVCC %r,-n,%r",    "10CCCCC011110AAAAA1BBBBBBBBBBBBB", 0 },
  { "SDIV %r,%r,%r",      "10CCCCC001111AAAAA000000000BBBBB", 0 },
  { "SDIV %r,i,%r",       "10CCCCC001111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SDIV %r,+i,%r",      "10CCCCC001111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SDIV %r,-n,%r",      "10CCCCC001111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SDIVCC %r,%r,%r",    "10CCCCC011111AAAAA000000000BBBBB", 0 },
  { "SDIVCC %r,i,%r",     "10CCCCC011111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SDIVCC %r,+i,%r",    "10CCCCC011111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SDIVCC %r,-n,%r",    "10CCCCC011111AAAAA1BBBBBBBBBBBBB", 0 },
  { "SAVE %r,%r,%r",      "10CCCCC111100AAAAA000000000BBBBB", 0 },
  { "SAVE %r,i,%r",       "10CCCCC111100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SAVE %r,+i,%r",      "10CCCCC111100AAAAA1BBBBBBBBBBBBB", 0 },
  { "SAVE %r,-n,%r",      "10CCCCC111100AAAAA1BBBBBBBBBBBBB", 0 },
  { "RESTORE %r,%r,%r",   "10CCCCC111101AAAAA000000000BBBBB", 0 },
  { "RESTORE %r,i,%r",    "10CCCCC111101AAAAA1BBBBBBBBBBBBB", 0 },
  { "RESTORE %r,+i,%r",   "10CCCCC111101AAAAA1BBBBBBBBBBBBB", 0 },
  { "RESTORE %r,-n,%r",   "10CCCCC111101AAAAA1BBBBBBBBBBBBB", 0 },
  { "BA d",               "0001000010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BA +i",              "0001000010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BA -n",              "0001000010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BN d",               "0000000010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BN +i",              "0000000010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BN -n",              "0000000010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BNE d",              "0001001010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BNE +i",             "0001001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BNE -n",             "0001001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BNZ d",              "0001001010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BNZ +i",             "0001001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BNZ -n",             "0001001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BE d",               "0000001010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BE +i",              "0000001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BE -n",              "0000001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BZ d",               "0000001010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BZ +i",              "0000001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BZ -n",              "0000001010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BG d",               "0001010010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BG +i",              "0001010010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BG -n",              "0001010010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BLE d",              "0000010010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BLE +i",             "0000010010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BLE -n",             "0000010010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BGE d",              "0001011010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BGE +i",             "0001011010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BGE -n",             "0001011010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BL d",               "0000011010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BL +i",              "0000011010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BL -n",              "0000011010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BGU d",              "0001100010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BGU +i",             "0001100010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BGU -n",             "0001100010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BLEU d",             "0000100010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BLEU +i",            "0000100010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BLEU -n",            "0000100010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BCC d",              "0001101010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BCC +i",             "0001101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BCC -n",             "0001101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BGEU d",             "0001101010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BGEU +i",            "0001101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BGEU -n",            "0001101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BCS d",              "0000101010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BCS +i",             "0000101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BCS -n",             "0000101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BLU d",              "0000101010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BLU +i",             "0000101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BLU -n",             "0000101010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BPOS d",             "0001110010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BPOS +i",            "0001110010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BPOS -n",            "0001110010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BNEG d",             "0000110010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BNEG +i",            "0000110010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BNEG -n",            "0000110010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BVC d",              "0001111010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BVC +i",             "0001111010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BVC -n",             "0001111010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BVS d",              "0000111010AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "BVS +i",             "0000111010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "BVS -n",             "0000111010AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "CALL d",             "01AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 3 },
  { "CALL +i",            "01AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 3 },
  { "CALL -n",            "01AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 3 },
  { "JMPL %r+%r,%r",      "10CCCCC111000AAAAA000000000BBBBB", 0 },
  { "JMPL %r+i,%r",       "10CCCCC111000AAAAA1BBBBBBBBBBBBB", 0 },
  { "JMPL %r-n,%r",       "10CCCCC111000AAAAA1BBBBBBBBBBBBB", 0 },
  { "TA %r+%r",           "1001000111010AAAAA000000000BBBBB", 0 },
  { "TA %r+i",            "1001000111010AAAAA1000000BBBBBBB", 0 },
  { "TA %r-n",            "1001000111010AAAAA1000000BBBBBBB", 0 },
  { "TN %r+%r",           "1000000111010AAAAA000000000BBBBB", 0 },
  { "TN %r+i",            "1000000111010AAAAA1000000BBBBBBB", 0 },
  { "TN %r-n",            "1000000111010AAAAA1000000BBBBBBB", 0 },
  { "TNE %r+%r",          "1001001111010AAAAA000000000BBBBB", 0 },
  { "TNE %r+i",           "1001001111010AAAAA1000000BBBBBBB", 0 },
  { "TNE %r-n",           "1001001111010AAAAA1000000BBBBBBB", 0 },
  { "TNZ %r+%r",          "1001001111010AAAAA000000000BBBBB", 0 },
  { "TNZ %r+i",           "1001001111010AAAAA1000000BBBBBBB", 0 },
  { "TNZ %r-n",           "1001001111010AAAAA1000000BBBBBBB", 0 },
  { "TE %r+%r",           "1000001111010AAAAA000000000BBBBB", 0 },
  { "TE %r+i",            "1000001111010AAAAA1000000BBBBBBB", 0 },
  { "TE %r-n",            "1000001111010AAAAA1000000BBBBBBB", 0 },
  { "TZ %r+%r",           "1000001111010AAAAA000000000BBBBB", 0 },
  { "TZ %r+i",            "1000001111010AAAAA1000000BBBBBBB", 0 },
  { "TZ %r-n",            "1000001111010AAAAA1000000BBBBBBB", 0 },
  { "TG %r+%r",           "1001010111010AAAAA000000000BBBBB", 0 },
  { "TG %r+i",            "1001010111010AAAAA1000000BBBBBBB", 0 },
  { "TG %r-n",            "1001010111010AAAAA1000000BBBBBBB", 0 },
  { "TLE %r+%r",          "1000010111010AAAAA000000000BBBBB", 0 },
  { "TLE %r+i",           "1000010111010AAAAA1000000BBBBBBB", 0 },
  { "TLE %r-n",           "1000010111010AAAAA1000000BBBBBBB", 0 },
  { "TGE %r+%r",          "1001011111010AAAAA000000000BBBBB", 0 },
  { "TGE %r+i",           "1001011111010AAAAA1000000BBBBBBB", 0 },
  { "TGE %r-n",           "1001011111010AAAAA1000000BBBBBBB", 0 },
  { "TL %r+%r",           "1000011111010AAAAA000000000BBBBB", 0 },
  { "TL %r+i",            "1000011111010AAAAA1000000BBBBBBB", 0 },
  { "TL %r-n",            "1000011111010AAAAA1000000BBBBBBB", 0 },
  { "TGU %r+%r",          "1001100111010AAAAA000000000BBBBB", 0 },
  { "TGU %r+i",           "1001100111010AAAAA1000000BBBBBBB", 0 },
  { "TGU %r-n",           "1001100111010AAAAA1000000BBBBBBB", 0 },
  { "TLEU %r+%r",         "1000100111010AAAAA000000000BBBBB", 0 },
  { "TLEU %r+i",          "1000100111010AAAAA1000000BBBBBBB", 0 },
  { "TLEU %r-n",          "1000100111010AAAAA1000000BBBBBBB", 0 },
  { "TCC %r+%r",          "1001101111010AAAAA000000000BBBBB", 0 },
  { "TCC %r+i",           "1001101111010AAAAA1000000BBBBBBB", 0 },
  { "TCC %r-n",           "1001101111010AAAAA1000000BBBBBBB", 0 },
  { "TGEU %r+%r",         "1001101111010AAAAA000000000BBBBB", 0 },
  { "TGEU %r+i",          "1001101111010AAAAA1000000BBBBBBB", 0 },
  { "TGEU %r-n",          "1001101111010AAAAA1000000BBBBBBB", 0 },
  { "TCS %r+%r",          "1000101111010AAAAA000000000BBBBB", 0 },
  { "TCS %r+i",           "1000101111010AAAAA1000000BBBBBBB", 0 },
  { "TCS %r-n",           "1000101111010AAAAA1000000BBBBBBB", 0 },
  { "TLU %r+%r",          "1000101111010AAAAA000000000BBBBB", 0 },
  { "TLU %r+i",           "1000101111010AAAAA1000000BBBBBBB", 0 },
  { "TLU %r-n",           "1000101111010AAAAA1000000BBBBBBB", 0 },
  { "TPOS %r+%r",         "1001110111010AAAAA000000000BBBBB", 0 },
  { "TPOS %r+i",          "1001110111010AAAAA1000000BBBBBBB", 0 },
  { "TPOS %r-n",          "1001110111010AAAAA1000000BBBBBBB", 0 },
  { "TNEG %r+%r",         "1000110111010AAAAA000000000BBBBB", 0 },
  { "TNEG %r+i",          "1000110111010AAAAA1000000BBBBBBB", 0 },
  { "TNEG %r-n",          "1000110111010AAAAA1000000BBBBBBB", 0 },
  { "TVC %r+%r",          "1001111111010AAAAA000000000BBBBB", 0 },
  { "TVC %r+i",           "1001111111010AAAAA1000000BBBBBBB", 0 },
  { "TVC %r-n",           "1001111111010AAAAA1000000BBBBBBB", 0 },
  { "TVS %r+%r",          "1000111111010AAAAA000000000BBBBB", 0 },
  { "TVS %r+i",           "1000111111010AAAAA1000000BBBBBBB", 0 },
  { "TVS %r-n",           "1000111111010AAAAA1000000BBBBBBB", 0 },
  { "RD %Y,%r",           "10AAAAA1010000000000000000000000", 0 },
  { "WR %r,%r,%Y",        "1000000110000AAAAA000000000BBBBB", 0 },
  { "WR %r,i,%Y",         "1000000110000AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,+i,%Y",        "1000000110000AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,-n,%Y",        "1000000110000AAAAA1BBBBBBBBBBBBB", 0 },
  { "FBA d",              "0001000110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBA +i",             "0001000110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBA -n",             "0001000110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBN d",              "0000000110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBN +i",             "0000000110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBN -n",             "0000000110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBU d",              "0000111110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBU +i",             "0000111110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBU -n",             "0000111110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBG d",              "0000110110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBG +i",             "0000110110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBG -n",             "0000110110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUG d",             "0000101110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBUG +i",            "0000101110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUG -n",            "0000101110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBL d",              "0000100110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBL +i",             "0000100110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBL -n",             "0000100110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUL d",             "0000011110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBUL +i",            "0000011110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUL -n",            "0000011110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBLG d",             "0000010110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBLG +i",            "0000010110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBLG -n",            "0000010110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBNE d",             "0000001110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBNE +i",            "0000001110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBNE -n",            "0000001110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBE d",              "0001001110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBE +i",             "0001001110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBE -n",             "0001001110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUE d",             "0001010110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBUE +i",            "0001010110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUE -n",            "0001010110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBGE d",             "0001011110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBGE +i",            "0001011110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBGE -n",            "0001011110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUGE d",            "0001100110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBUGE +i",           "0001100110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBUGE -n",           "0001100110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBLE d",             "0001101110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBLE +i",            "0001101110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBLE -n",            "0001101110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBULE d",            "0001110110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBULE +i",           "0001110110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBULE -n",           "0001110110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBO d",              "0001111110AAAAAAAAAAAAAAAAAAAAAA", 2 },
  { "FBO +i",             "0001111110AAAAAAAAAAAAAAAAAAAAAA", 0 },
  { "FBO -n",             "0001111110AAAAAAAAAAAAAAAAAAAAAA", 0 },

  { "LDSBA [%r+%r]i,%r",  "11DDDDD011001AAAAA0CCCCCCCCBBBBB", 0 },
  { "LDSHA [%r+%r]i,%r",  "11DDDDD011010AAAAA0CCCCCCCCBBBBB", 0 },
  { "LDUBA [%r+%r]i,%r",  "11DDDDD010001AAAAA0CCCCCCCCBBBBB", 0 },
  { "LDUHA [%r+%r]i,%r",  "11DDDDD010010AAAAA0CCCCCCCCBBBBB", 0 },
  { "LDA [%r+%r]i,%r",    "11DDDDD010000AAAAA0CCCCCCCCBBBBB", 0 },
  { "LDDA [%r+%r]i,%r",   "11DDDDD010011AAAAA0CCCCCCCCBBBBB", 0 },
  { "STBA %r,[%r+%r]i",   "11AAAAA010101BBBBB0DDDDDDDDCCCCC", 0 },
  { "STHA %r,[%r+%r]i",   "11AAAAA010110BBBBB0DDDDDDDDCCCCC", 0 },
  { "STA %r,[%r+%r]i",    "11AAAAA010100BBBBB0DDDDDDDDCCCCC", 0 },
  { "STDA %r,[%r+%r]i",   "11AAAAA010111BBBBB0DDDDDDDDCCCCC", 0 },
  { "LDSTUBA [%r+%r]i,%r","11DDDDD011101AAAAA0CCCCCCCCBBBBB", 0 },
  { "SWAPA [%r+%r]i,%r",  "11DDDDD011111AAAAA0CCCCCCCCBBBBB", 0 },
  { "RETT %r+%r",         "1000000111001AAAAA000000000BBBBB", 0 },
  { "RETT %r+i",          "1000000111001AAAAA1BBBBBBBBBBBBB", 0 },
  { "RETT %r-n",          "1000000111001AAAAA1BBBBBBBBBBBBB", 0 },
  { "RD %PSR,%r",         "10AAAAA1010010000000000000000000", 0 },
  { "RD %WIM,%r",         "10AAAAA1010100000000000000000000", 0 },
  { "RD %TBR,%r",         "10AAAAA1010110000000000000000000", 0 },
  { "WR %r,%r,%PSR",      "1000000110001AAAAA000000000BBBBB", 0 },
  { "WR %r,i,%PSR",       "1000000110001AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,+i,%PSR",      "1000000110001AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,-n,%PSR",      "1000000110001AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,%r,%WIM",      "1000000110010AAAAA000000000BBBBB", 0 },
  { "WR %r,i,%WIM",       "1000000110010AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,+i,%WIM",      "1000000110010AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,-n,%WIM",      "1000000110010AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,%r,%TBR",      "1000000110011AAAAA000000000BBBBB", 0 },
  { "WR %r,i,%TBR",       "1000000110011AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,+i,%TBR",      "1000000110011AAAAA1BBBBBBBBBBBBB", 0 },
  { "WR %r,-n,%TBR",      "1000000110011AAAAA1BBBBBBBBBBBBB", 0 },

  { "CMP %r,%r",          "1000000010100AAAAA000000000BBBBB", 0 },
  { "CMP %r,i",           "1000000010100AAAAA1BBBBBBBBBBBBB", 0 },
  { "CMP %r,+i",          "1000000010100AAAAA1BBBBBBBBBBBBB", 0 },
  { "CMP %r,-n",          "1000000010100AAAAA1BBBBBBBBBBBBB", 0 },
  { "JMP %r+%r",          "1000000111000AAAAA000000000BBBBB", 0 },
  { "JMP %r+i",           "1000000111000AAAAA1BBBBBBBBBBBBB", 0 },
  { "JMP %r-n",           "1000000111000AAAAA1BBBBBBBBBBBBB", 0 },
  { "CALL %r+%r",         "1001111111000AAAAA000000000BBBBB", 0 },
  { "CALL %r+i",          "1001111111000AAAAA1BBBBBBBBBBBBB", 0 },
  { "CALL %r-n",          "1001111111000AAAAA1BBBBBBBBBBBBB", 0 },
  { "TST %r",             "100000001001000000000000000AAAAA", 0 },
  { "RET",                "10000001110001111110000000000100", 0 },
  { "RETL",               "10000001110000111110000000000100", 0 },
  { "RESTORE",            "10000001111010000000000000000000", 0 },
  { "SAVE",               "10000001111000000000000000000000", 0 },
  { "NOT %r,%r",          "10BBBBB000111AAAAA00000000000000", 0 },
  { "NOT %r",             "10AAAAA000111AAAAA00000000000000", 0 },
  { "NEG %r,%r",          "10BBBBB00010000000000000000AAAAA", 0 },
  { "NEG %r",             "10AAAAA00010000000000000000AAAAA", 0 },
  { "INC %r",             "10AAAAA000000AAAAA10000000000001", 0 },
  { "INC i,%r",           "10BBBBB000000BBBBB1AAAAAAAAAAAAA", 0 },
  { "INCCC %r",           "10AAAAA010000AAAAA10000000000001", 0 },
  { "INCCC i,%r",         "10BBBBB010000BBBBB1AAAAAAAAAAAAA", 0 },
  { "DEC %r",             "10AAAAA000100AAAAA10000000000001", 0 },
  { "DEC i,%r",           "10BBBBB000100BBBBB1AAAAAAAAAAAAA", 0 },
  { "DECCC %r",           "10AAAAA010100AAAAA10000000000001", 0 },
  { "DECCC i,%r",         "10BBBBB010100BBBBB1AAAAAAAAAAAAA", 0 },
  { "BTST %r,%r",         "1000000010001AAAAA000000000BBBBB", 0 },
  { "BTST i,%r",          "1000000010001BBBBB1AAAAAAAAAAAAA", 0 },
  { "BSET %r,%r",         "10BBBBB000010AAAAA000000000BBBBB", 0 },
  { "BSET i,%r",          "10BBBBB000010BBBBB1AAAAAAAAAAAAA", 0 },
  { "BCLR %r,%r",         "10BBBBB000101BBBBB000000000AAAAA", 0 },
  { "BCLR i,%r",          "10BBBBB000101BBBBB1AAAAAAAAAAAAA", 0 },
  { "BTOG %r,%r",         "10BBBBB000011BBBBB000000000AAAAA", 0 },
  { "BTOG i,%r",          "10BBBBB000011BBBBB1AAAAAAAAAAAAA", 0 },
  { "CLR %r",             "10AAAAA0000100000000000000000000", 0 },
  { "CLRB [%r+%r]",       "1100000000101AAAAA000000000BBBBB", 0 },
  { "CLRB [%r+i]",        "1100000000101AAAAA1BBBBBBBBBBBBB", 0 },
  { "CLRB [%r-n]",        "1100000000101AAAAA1BBBBBBBBBBBBB", 0 },
  { "CLRH [%r+%r]",       "1100000000110AAAAA000000000BBBBB", 0 },
  { "CLRH [%r+i]",        "1100000000110AAAAA1BBBBBBBBBBBBB", 0 },
  { "CLRH [%r-n]",        "1100000000110AAAAA1BBBBBBBBBBBBB", 0 },
  { "CLR [%r+%r]",        "1100000000100AAAAA000000000BBBBB", 0 },
  { "CLR [%r+i]",         "1100000000100AAAAA1BBBBBBBBBBBBB", 0 },
  { "CLR [%r-n]",         "1100000000100AAAAA1BBBBBBBBBBBBB", 0 },
  { "MOV %r,%r",          "10BBBBB00001000000000000000AAAAA", 0 },
  { "MOV i,%r",           "10BBBBB000010000001AAAAAAAAAAAAA", 0 },
  { "MOV -n,%r",          "10BBBBB000010000001AAAAAAAAAAAAA", 0 },
  { "MOV %Y,%r",          "10AAAAA1010000000000000000000000", 0 },
  { "MOV %PSR,%r",        "10AAAAA1010010000000000000000000", 0 },
  { "MOV %WIM,%r",        "10AAAAA1010100000000000000000000", 0 },
  { "MOV %TBR,%r",        "10AAAAA1010110000000000000000000", 0 },
  { "MOV %r,%Y",          "100000011000000000000000000AAAAA", 0 },
  { "MOV i,%Y",           "1000000110000000001AAAAAAAAAAAAA", 0 },
  { "MOV -n,%Y",          "1000000110000000001AAAAAAAAAAAAA", 0 },
  { "MOV %r,%PSR",        "100000011000100000000000000AAAAA", 0 },
  { "MOV i,%PSR",         "1000000110001000001AAAAAAAAAAAAA", 0 },
  { "MOV -n,%PSR",        "1000000110001000001AAAAAAAAAAAAA", 0 },
  { "MOV %r,%WIM",        "100000011001000000000000000AAAAA", 0 },
  { "MOV i,%WIM",         "1000000110010000001AAAAAAAAAAAAA", 0 },
  { "MOV -n,%WIM",        "1000000110010000001AAAAAAAAAAAAA", 0 },
  { "MOV %r,%TBR",        "100000011001100000000000000AAAAA", 0 },
  { "MOV i,%TBR",         "1000000110011000001AAAAAAAAAAAAA", 0 },
  { "MOV -n,%TBR",        "1000000110011000001AAAAAAAAAAAAA", 0 },

  { "FITOS %r,%f",        "10BBBBB11010000000011000100AAAAA", 0 },
  { "FITOD %r,%f",        "10BBBBB11010000000011001000AAAAA", 0 },
  { "FITOQ %r,%f",        "10BBBBB11010000000011001100AAAAA", 0 },
  { "FSTOI %f,%r",        "10BBBBB11010000000011000001AAAAA", 0 },
  { "FDTOI %f,%r",        "10BBBBB11010000000011000010AAAAA", 0 },
  { "FQTOI %f,%r",        "10BBBBB11010000000011000011AAAAA", 0 },
  { "FMOVS %f,%f",        "10BBBBB11010000000000000001AAAAA", 0 },
  { "FNEGS %f,%f",        "10BBBBB11010000000000000101AAAAA", 0 },
  { "FABSS %f,%f",        "10BBBBB11010000000000001001AAAAA", 0 },
  { "FSQRTS %f,%f",       "10BBBBB11010000000000101001AAAAA", 0 },
  { "FSQRTD %f,%f",       "10BBBBB11010000000000101010AAAAA", 0 },
  { "FSQRTQ %f,%f",       "10BBBBB11010000000000101011AAAAA", 0 },
  { "FADDS %f,%f,%f",     "10CCCCC110100AAAAA001000001BBBBB", 0 },
  { "FADDD %f,%f,%f",     "10CCCCC110100AAAAA001000010BBBBB", 0 },
  { "FADDQ %f,%f,%f",     "10CCCCC110100AAAAA001000011BBBBB", 0 },
  { "FSUBS %f,%f,%f",     "10CCCCC110100AAAAA001000101BBBBB", 0 },
  { "FSUBD %f,%f,%f",     "10CCCCC110100AAAAA001000110BBBBB", 0 },
  { "FSUBQ %f,%f,%f",     "10CCCCC110100AAAAA001000111BBBBB", 0 },
  { "FMULS %f,%f,%f",     "10CCCCC110100AAAAA001001001BBBBB", 0 },
  { "FMULD %f,%f,%f",     "10CCCCC110100AAAAA001001010BBBBB", 0 },
  { "FMULQ %f,%f,%f",     "10CCCCC110100AAAAA001001011BBBBB", 0 },
  { "FDIVS %f,%f,%f",     "10CCCCC110100AAAAA001001101BBBBB", 0 },
  { "FDIVD %f,%f,%f",     "10CCCCC110100AAAAA001001110BBBBB", 0 },
  { "FDIVQ %f,%f,%f",     "10CCCCC110100AAAAA001001111BBBBB", 0 },
  { "FCMPS %f,%f",        "1000000110100AAAAA001010001BBBBB", 0 },
  { "FCMPD %f,%f",        "1000000110100AAAAA001010010BBBBB", 0 },
  { "FCMPQ %f,%f",        "1000000110100AAAAA001010011BBBBB", 0 },

  { "FSINS %f,%f",        "10BBBBB11010000000011100001AAAAA", 0 },
  { "FSIND %f,%f",        "10BBBBB11010000000011100010AAAAA", 0 },
  { "FSINQ %f,%f",        "10BBBBB11010000000011100011AAAAA", 0 },
  { "FCOSS %f,%f",        "10BBBBB11010000000011100101AAAAA", 0 },
  { "FCOSD %f,%f",        "10BBBBB11010000000011100110AAAAA", 0 },
  { "FCOSQ %f,%f",        "10BBBBB11010000000011100111AAAAA", 0 },
  { "FTANS %f,%f",        "10BBBBB11010000000011101001AAAAA", 0 },
  { "FTAND %f,%f",        "10BBBBB11010000000011101010AAAAA", 0 },
  { "FTANQ %f,%f",        "10BBBBB11010000000011101011AAAAA", 0 },
  { "FLOGS %f,%f",        "10BBBBB11010000000011101101AAAAA", 0 },
  { "FLOGD %f,%f",        "10BBBBB11010000000011101110AAAAA", 0 },
  { "FLOGQ %f,%f",        "10BBBBB11010000000011101111AAAAA", 0 },
  { "FEXPS %f,%f",        "10BBBBB11010000000011110001AAAAA", 0 },
  { "FEXPD %f,%f",        "10BBBBB11010000000011110010AAAAA", 0 },
  { "FEXPQ %f,%f",        "10BBBBB11010000000011110011AAAAA", 0 },
  { "FASINS %f,%f",       "10BBBBB11010000000011110101AAAAA", 0 },
  { "FASIND %f,%f",       "10BBBBB11010000000011110110AAAAA", 0 },
  { "FASINQ %f,%f",       "10BBBBB11010000000011110111AAAAA", 0 },
  { "FACOSS %f,%f",       "10BBBBB11010000000011111001AAAAA", 0 },
  { "FACOSD %f,%f",       "10BBBBB11010000000011111010AAAAA", 0 },
  { "FACOSQ %f,%f",       "10BBBBB11010000000011111011AAAAA", 0 },
  { "FATANS %f,%f",       "10BBBBB11010000000011111101AAAAA", 0 },
  { "FATAND %f,%f",       "10BBBBB11010000000011111110AAAAA", 0 },
  { "FATANQ %f,%f",       "10BBBBB11010000000011111111AAAAA", 0 },

  { "HALT",               "11-----1111110000000000000000000", 0 },
  { "---",             "---", 0 },
  };

word args[8];

int cmatch(char c1, char c2) {
  if (c1 >= 'a' && c1 <= 'z') c1 -= 32;
  if (c2 >= 'a' && c2 <= 'z') c2 -= 32;
  if (c1 == c2) return -1;
  return 0;
  }

extern word  address;
extern int   isExternal;
extern int   addressType;
extern char* getNumber(char* line, word* dest);

word translate(char* pattern) {
  word ret;
  word arg0,arg1,arg2,arg3;
  int p;
  int shift;
  p = strlen(pattern)-1;
  ret = 0;
  shift = 0;
  arg0 = args[0];
  arg1 = args[1];
  arg2 = args[2];
  arg3 = args[3];
  while (p >= 0) {
    if (pattern[p] == '0') {
      arg0 = args[0];
      arg1 = args[1];
      arg2 = args[2];
      arg3 = args[3];
      }
    if (pattern[p] == '1') {
      ret |= (1 << shift);
      arg0 = args[0];
      arg1 = args[1];
      arg2 = args[2];
      arg3 = args[3];
      }
    if (pattern[p] == 'A') {
      ret |= ((arg0 & 1) << shift);
      arg0 >>= 1;
      arg1 = args[1];
      arg2 = args[2];
      arg3 = args[3];
      }
    if (pattern[p] == 'B') {
      ret |= ((arg1 & 1) << shift);
      arg1 >>= 1;
      arg0 = args[0];
      arg2 = args[2];
      arg3 = args[3];
      }
    if (pattern[p] == 'C') {
      ret |= ((arg2 & 1) << shift);
      arg2 >>= 1;
      arg0 = args[0];
      arg1 = args[1];
      arg3 = args[3];
      }
    if (pattern[p] == 'D') {
      ret |= ((arg3 & 1) << shift);
      arg3 >>= 1;
      arg0 = args[0];
      arg1 = args[1];
      arg2 = args[2];
      }
    shift++;
    p--;
    }
  return ret;
  }

char* getDecimal(char* line, word* dest) {
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

int match(char* pattern, char* line) {
  int arg;
  arg = 0;
  while (*line == ' ' || *line == '\t') line++;
  while (*pattern == ' ' || *pattern == '\t') pattern++;
  while (*pattern != 0) {
    if (*pattern == 'r') {
      if ((*line == 'r') || (*line == 'R')) {
        line = getDecimal(line+1, &(args[arg]));
        if (line == NULL) return 0;
        if (args[arg] > 31) return 0;
        arg++;
        }
      else if ((*line == 'i') || (*line == 'I')) {
        line = getDecimal(line+1, &(args[arg]));
        if (line == NULL) return 0;
        if (args[arg] > 7) return 0;
        args[arg] += 24;
        arg++;
        }
      else if ((*line == 'o') || (*line == 'O')) {
        line = getDecimal(line+1, &(args[arg]));
        if (line == NULL) return 0;
        if (args[arg] > 7) return 0;
        args[arg] += 8;
        arg++;
        }
      else if ((*line == 'l') || (*line == 'L')) {
        line = getDecimal(line+1, &(args[arg]));
        if (line == NULL) return 0;
        if (args[arg] > 7) return 0;
        args[arg] += 16;
        arg++;
        }
      else if ((*line == 'g') || (*line == 'G')) {
        line = getDecimal(line+1, &(args[arg]));
        if (line == NULL) return 0;
        if (args[arg] > 7) return 0;
        arg++;
        }
      else return 0;
      pattern++;
      }
    else if (*pattern == 'f') {
      if (*line == 'f' || *line == 'F') {
        line = getNumber(line+1, &(args[arg]));
        if (line == NULL) return 0;
        if (args[arg] > 31) return 0;
        arg++;
        pattern++;
        }
      else return 0;
      }
    else if (*pattern == 'i') {
      line = getNumber(line, &(args[arg]));
      if (line == NULL) return 0;
      arg++;
      pattern++;
      }
    else if (*pattern == 'd') {
      line = getNumber(line, &(args[arg]));
      if (line == NULL) return 0;
      args[arg] -= address;
      args[arg] /= 4;
      arg++;
      pattern++;
      }
    else if (*pattern == 'n') {
      line = getNumber(line, &(args[arg]));
      if (line == NULL) return 0;
      args[arg] = -args[arg];
      arg++;
      pattern++;
      }
    else if (*pattern == ' ') {
      if (*line != ' ') return 0;
      while (*pattern == ' ') pattern++;
      while (*line == ' ' || *line == '\t') line++;
      }
    else if (cmatch(*pattern, *line) != 0) {
      pattern++;
      line++;
      }
    else return 0;
    }
  while (*line == ' ' || *line == '\t') line++;
  if (*line == 0) return -1;
  return 0;
  }

word assemble(char* line, int* err) {
  int inst;
  int i;
  inst = -1;
  *err = 0;
  i = 0;
  while (inst < 0  && strcmp(ops[i].pattern,"---") != 0) {
    isExternal = -1;
    if (match(ops[i].pattern, line) != 0) inst = i;
    i++;
    }
  if (inst >= 0) {
    addressType = ops[inst].atype;
    return translate(ops[inst].trans);
    }
  *err = -1;
  return 0;
  }

