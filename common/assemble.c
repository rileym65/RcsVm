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
  } OPS;

OPS ops[] = {
  { "LDSB [%r+%r],%r",    "11CCCCC001001AAAAA000000000BBBBB" },
  { "LDSB [%r+i],%r",     "11CCCCC001001AAAAA1BBBBBBBBBBBBB" },
  { "LDSB [%r-n],%r",     "11CCCCC001001AAAAA1BBBBBBBBBBBBB" },
  { "LDSH [%r+%r],%r",    "11CCCCC001010AAAAA000000000BBBBB" },
  { "LDSH [%r+i],%r",     "11CCCCC001010AAAAA1BBBBBBBBBBBBB" },
  { "LDSH [%r-n],%r",     "11CCCCC001010AAAAA1BBBBBBBBBBBBB" },
  { "LDUB [%r+%r],%r",    "11CCCCC000001AAAAA000000000BBBBB" },
  { "LDUB [%r+i],%r",     "11CCCCC000001AAAAA1BBBBBBBBBBBBB" },
  { "LDUB [%r-n],%r",     "11CCCCC000001AAAAA1BBBBBBBBBBBBB" },
  { "LDUH [%r+%r],%r",    "11CCCCC000010AAAAA000000000BBBBB" },
  { "LDUH [%r+i],%r",     "11CCCCC000010AAAAA1BBBBBBBBBBBBB" },
  { "LDUH [%r-n],%r",     "11CCCCC000010AAAAA1BBBBBBBBBBBBB" },
  { "LD [%r+%r],%r",      "11CCCCC000000AAAAA000000000BBBBB" },
  { "LD [%r+i],%r",       "11CCCCC000000AAAAA1BBBBBBBBBBBBB" },
  { "LD [%r-n],%r",       "11CCCCC000000AAAAA1BBBBBBBBBBBBB" },
  { "LDD [%r+%r],%r",     "11CCCCC000011AAAAA000000000BBBBB" },
  { "LDD [%r+i],%r",      "11CCCCC000011AAAAA1BBBBBBBBBBBBB" },
  { "LDD [%r-n],%r",      "11CCCCC000011AAAAA1BBBBBBBBBBBBB" },
  { "LD [%r+%r],%f",      "11CCCCC100000AAAAA000000000BBBBB" },
  { "LD [%r+i],%f",       "11CCCCC100000AAAAA1BBBBBBBBBBBBB" },
  { "LD [%r-n],%f",       "11CCCCC100000AAAAA1BBBBBBBBBBBBB" },
  { "LDD [%r+%r],%f",     "11CCCCC100011AAAAA000000000BBBBB" },
  { "LDD [%r+i],%f",      "11CCCCC100011AAAAA1BBBBBBBBBBBBB" },
  { "LDD [%r-n],%f",      "11CCCCC100011AAAAA1BBBBBBBBBBBBB" },
  { "LD [%r+%r],%FSR",    "11CCCCC100001AAAAA000000000BBBBB" },
  { "LD [%r+i],%FSR",     "11CCCCC100001AAAAA1BBBBBBBBBBBBB" },
  { "LD [%r-n],%FSR",     "11CCCCC100001AAAAA1BBBBBBBBBBBBB" },
  { "STB %r,[%r+%r]",     "11AAAAA000101BBBBB000000000CCCCC" },
  { "STB %r,[%r+i]",      "11AAAAA000101BBBBB1CCCCCCCCCCCCC" },
  { "STB %r,[%r-n]",      "11AAAAA000101BBBBB1CCCCCCCCCCCCC" },
  { "STH %r,[%r+%r]",     "11AAAAA000110BBBBB000000000CCCCC" },
  { "STH %r,[%r+i]",      "11AAAAA000110BBBBB1CCCCCCCCCCCCC" },
  { "STH %r,[%r-n]",      "11AAAAA000110BBBBB1CCCCCCCCCCCCC" },
  { "ST %r,[%r+%r]",      "11AAAAA000100BBBBB000000000CCCCC" },
  { "ST %r,[%r+i]",       "11AAAAA000100BBBBB1CCCCCCCCCCCCC" },
  { "ST %r,[%r-n]",       "11AAAAA000100BBBBB1CCCCCCCCCCCCC" },
  { "STD %r,[%r+%r]",     "11AAAAA000111BBBBB000000000CCCCC" },
  { "STD %r,[%r+i]",      "11AAAAA000111BBBBB1CCCCCCCCCCCCC" },
  { "STD %r,[%r-n]",      "11AAAAA000111BBBBB1CCCCCCCCCCCCC" },
  { "ST %FSR,[%r+%r]",    "1100000100101AAAAA000000000BBBBB" },
  { "ST %FSR,[%r+i]",     "1100000100101AAAAA1BBBBBBBBBBBBB" },
  { "ST %FSR,[%r-n]",     "1100000100101AAAAA1BBBBBBBBBBBBB" },
  { "ST %f,[%r+%r]",      "11AAAAA100100BBBBB000000000CCCCC" },
  { "ST %f,[%r+i]",       "11AAAAA100100BBBBB1CCCCCCCCCCCCC" },
  { "ST %f,[%r-n]",       "11AAAAA100100BBBBB1CCCCCCCCCCCCC" },
  { "STD %f,[%r+%r]",     "11AAAAA100111BBBBB000000000CCCCC" },
  { "STD %f,[%r+i]",      "11AAAAA100111BBBBB1CCCCCCCCCCCCC" },
  { "STD %f,[%r-n]",      "11AAAAA100111BBBBB1CCCCCCCCCCCCC" },
  { "LDSTUB [%r+%r],%r",  "11CCCCC001101AAAAA000000000BBBBB" },
  { "LDSTUB [%r+i],%r",   "11CCCCC001101AAAAA1BBBBBBBBBBBBB" },
  { "LDSTUB [%r-n],%r",   "11CCCCC001101AAAAA1BBBBBBBBBBBBB" },
  { "SWAP [%r+%r],%r",    "11CCCCC001111AAAAA000000000BBBBB" },
  { "SWAP [%r+i],%r",     "11CCCCC001111AAAAA1BBBBBBBBBBBBB" },
  { "SWAP [%r-n],%r",     "11CCCCC001111AAAAA1BBBBBBBBBBBBB" },
  { "SETHI i,%r",         "00BBBBB100AAAAAAAAAAAAAAAAAAAAAA" },
  { "SETHI +i,%r",        "00BBBBB100AAAAAAAAAAAAAAAAAAAAAA" },
  { "SETHI -n,%r",        "00BBBBB100AAAAAAAAAAAAAAAAAAAAAA" },
  { "AND %r,%r,%r",       "10CCCCC000001AAAAA000000000BBBBB" },
  { "AND %r,i,%r",        "10CCCCC000001AAAAA1BBBBBBBBBBBBB" },
  { "AND %r,+i,%r",       "10CCCCC000001AAAAA1BBBBBBBBBBBBB" },
  { "AND %r,-n,%r",       "10CCCCC000001AAAAA1BBBBBBBBBBBBB" },
  { "ANDCC %r,%r,%r",     "10CCCCC010001AAAAA000000000BBBBB" },
  { "ANDCC %r,i,%r",      "10CCCCC010001AAAAA1BBBBBBBBBBBBB" },
  { "ANDCC %r,+i,%r",     "10CCCCC010001AAAAA1BBBBBBBBBBBBB" },
  { "ANDCC %r,-n,%r",     "10CCCCC010001AAAAA1BBBBBBBBBBBBB" },
  { "ANDN %r,%r,%r",      "10CCCCC000101AAAAA000000000BBBBB" },
  { "ANDN %r,i,%r",       "10CCCCC000101AAAAA1BBBBBBBBBBBBB" },
  { "ANDN %r,+i,%r",      "10CCCCC000101AAAAA1BBBBBBBBBBBBB" },
  { "ANDN %r,-n,%r",      "10CCCCC000101AAAAA1BBBBBBBBBBBBB" },
  { "ANDNCC %r,%r,%r",    "10CCCCC010101AAAAA000000000BBBBB" },
  { "ANDNCC %r,i,%r",     "10CCCCC010101AAAAA1BBBBBBBBBBBBB" },
  { "ANDNCC %r,+i,%r",    "10CCCCC010101AAAAA1BBBBBBBBBBBBB" },
  { "ANDNCC %r,-n,%r",    "10CCCCC010101AAAAA1BBBBBBBBBBBBB" },
  { "OR %r,%r,%r",        "10CCCCC000010AAAAA000000000BBBBB" },
  { "OR %r,i,%r",         "10CCCCC000010AAAAA1BBBBBBBBBBBBB" },
  { "OR %r,+i,%r",        "10CCCCC000010AAAAA1BBBBBBBBBBBBB" },
  { "OR %r,-n,%r",        "10CCCCC000010AAAAA1BBBBBBBBBBBBB" },
  { "ORCC %r,%r,%r",      "10CCCCC010010AAAAA000000000BBBBB" },
  { "ORCC %r,i,%r",       "10CCCCC010010AAAAA1BBBBBBBBBBBBB" },
  { "ORCC %r,+i,%r",      "10CCCCC010010AAAAA1BBBBBBBBBBBBB" },
  { "ORCC %r,-n,%r",      "10CCCCC010010AAAAA1BBBBBBBBBBBBB" },
  { "ORN %r,%r,%r",       "10CCCCC000110AAAAA000000000BBBBB" },
  { "ORN %r,i,%r",        "10CCCCC000110AAAAA1BBBBBBBBBBBBB" },
  { "ORN %r,+i,%r",       "10CCCCC000110AAAAA1BBBBBBBBBBBBB" },
  { "ORN %r,-n,%r",       "10CCCCC000110AAAAA1BBBBBBBBBBBBB" },
  { "ORNCC %r,%r,%r",     "10CCCCC010110AAAAA000000000BBBBB" },
  { "ORNCC %r,i,%r",      "10CCCCC010110AAAAA1BBBBBBBBBBBBB" },
  { "ORNCC %r,+i,%r",     "10CCCCC010110AAAAA1BBBBBBBBBBBBB" },
  { "ORNCC %r,-n,%r",     "10CCCCC010110AAAAA1BBBBBBBBBBBBB" },
  { "XOR %r,%r,%r",       "10CCCCC000011AAAAA000000000BBBBB" },
  { "XOR %r,i,%r",        "10CCCCC000011AAAAA1BBBBBBBBBBBBB" },
  { "XOR %r,+i,%r",       "10CCCCC000011AAAAA1BBBBBBBBBBBBB" },
  { "XOR %r,-n,%r",       "10CCCCC000011AAAAA1BBBBBBBBBBBBB" },
  { "XORCC %r,%r,%r",     "10CCCCC010011AAAAA000000000BBBBB" },
  { "XORCC %r,i,%r",      "10CCCCC010011AAAAA1BBBBBBBBBBBBB" },
  { "XORCC %r,+i,%r",     "10CCCCC010011AAAAA1BBBBBBBBBBBBB" },
  { "XORCC %r,-n,%r",     "10CCCCC010011AAAAA1BBBBBBBBBBBBB" },
  { "XNOR %r,%r,%r",      "10CCCCC000111AAAAA000000000BBBBB" },
  { "XNOR %r,i,%r",       "10CCCCC000111AAAAA1BBBBBBBBBBBBB" },
  { "XNOR %r,+i,%r",      "10CCCCC000111AAAAA1BBBBBBBBBBBBB" },
  { "XNOR %r,-n,%r",      "10CCCCC000111AAAAA1BBBBBBBBBBBBB" },
  { "XNORCC %r,%r,%r",    "10CCCCC010111AAAAA000000000BBBBB" },
  { "XNORCC %r,i,%r",     "10CCCCC010111AAAAA1BBBBBBBBBBBBB" },
  { "XNORCC %r,+i,%r",    "10CCCCC010111AAAAA1BBBBBBBBBBBBB" },
  { "XNORCC %r,-n,%r",    "10CCCCC010111AAAAA1BBBBBBBBBBBBB" },
  { "SLL %r,%r,%r",       "10CCCCC100101AAAAA000000000BBBBB" },
  { "SLL %r,i,%r",        "10CCCCC100101AAAAA1BBBBBBBBBBBBB" },
  { "SLL %r,+i,%r",       "10CCCCC100101AAAAA1BBBBBBBBBBBBB" },
  { "SLL %r,-n,%r",       "10CCCCC100101AAAAA1BBBBBBBBBBBBB" },
  { "SRL %r,%r,%r",       "10CCCCC100110AAAAA000000000BBBBB" },
  { "SRL %r,i,%r",        "10CCCCC100110AAAAA1BBBBBBBBBBBBB" },
  { "SRL %r,+i,%r",       "10CCCCC100110AAAAA1BBBBBBBBBBBBB" },
  { "SRL %r,-n,%r",       "10CCCCC100110AAAAA1BBBBBBBBBBBBB" },
  { "SRA %r,%r,%r",       "10CCCCC100111AAAAA000000000BBBBB" },
  { "SRA %r,i,%r",        "10CCCCC100111AAAAA1BBBBBBBBBBBBB" },
  { "SRA %r,+i,%r",       "10CCCCC100111AAAAA1BBBBBBBBBBBBB" },
  { "SRA %r,-n,%r",       "10CCCCC100111AAAAA1BBBBBBBBBBBBB" },
  { "ADD %r,%r,%r",       "10CCCCC000000AAAAA000000000BBBBB" },
  { "ADD %r,i,%r",        "10CCCCC000000AAAAA1BBBBBBBBBBBBB" },
  { "ADD %r,+i,%r",       "10CCCCC000000AAAAA1BBBBBBBBBBBBB" },
  { "ADD %r,-n,%r",       "10CCCCC000000AAAAA1BBBBBBBBBBBBB" },
  { "ADDCC %r,%r,%r",     "10CCCCC010000AAAAA000000000BBBBB" },
  { "ADDCC %r,i,%r",      "10CCCCC010000AAAAA1BBBBBBBBBBBBB" },
  { "ADDCC %r,+i,%r",     "10CCCCC010000AAAAA1BBBBBBBBBBBBB" },
  { "ADDCC %r,-n,%r",     "10CCCCC010000AAAAA1BBBBBBBBBBBBB" },
  { "ADDX %r,%r,%r",      "10CCCCC001000AAAAA000000000BBBBB" },
  { "ADDX %r,i,%r",       "10CCCCC001000AAAAA1BBBBBBBBBBBBB" },
  { "ADDX %r,+i,%r",      "10CCCCC001000AAAAA1BBBBBBBBBBBBB" },
  { "ADDX %r,-n,%r",      "10CCCCC001000AAAAA1BBBBBBBBBBBBB" },
  { "ADDXCC %r,%r,%r",    "10CCCCC011000AAAAA000000000BBBBB" },
  { "ADDXCC %r,i,%r",     "10CCCCC011000AAAAA1BBBBBBBBBBBBB" },
  { "ADDXCC %r,+i,%r",    "10CCCCC011000AAAAA1BBBBBBBBBBBBB" },
  { "ADDXCC %r,-n,%r",    "10CCCCC011000AAAAA1BBBBBBBBBBBBB" },
  { "SUB %r,%r,%r",       "10CCCCC000100AAAAA000000000BBBBB" },
  { "SUB %r,i,%r",        "10CCCCC000100AAAAA1BBBBBBBBBBBBB" },
  { "SUB %r,+i,%r",       "10CCCCC000100AAAAA1BBBBBBBBBBBBB" },
  { "SUB %r,-n,%r",       "10CCCCC000100AAAAA1BBBBBBBBBBBBB" },
  { "SUBCC %r,%r,%r",     "10CCCCC010100AAAAA000000000BBBBB" },
  { "SUBCC %r,i,%r",      "10CCCCC010100AAAAA1BBBBBBBBBBBBB" },
  { "SUBCC %r,+i,%r",     "10CCCCC010100AAAAA1BBBBBBBBBBBBB" },
  { "SUBCC %r,-n,%r",     "10CCCCC010100AAAAA1BBBBBBBBBBBBB" },
  { "SUBX %r,%r,%r",      "10CCCCC001100AAAAA000000000BBBBB" },
  { "SUBX %r,i,%r",       "10CCCCC001100AAAAA1BBBBBBBBBBBBB" },
  { "SUBX %r,+i,%r",      "10CCCCC001100AAAAA1BBBBBBBBBBBBB" },
  { "SUBX %r,-n,%r",      "10CCCCC001100AAAAA1BBBBBBBBBBBBB" },
  { "SUBXCC %r,%r,%r",    "10CCCCC011100AAAAA000000000BBBBB" },
  { "SUBXCC %r,i,%r",     "10CCCCC011100AAAAA1BBBBBBBBBBBBB" },
  { "SUBXCC %r,+i,%r",    "10CCCCC011100AAAAA1BBBBBBBBBBBBB" },
  { "SUBXCC %r,-n,%r",    "10CCCCC011100AAAAA1BBBBBBBBBBBBB" },
  { "UMUL %r,%r,%r",      "10CCCCC001010AAAAA000000000BBBBB" },
  { "UMUL %r,i,%r",       "10CCCCC001010AAAAA1BBBBBBBBBBBBB" },
  { "UMUL %r,+i,%r",      "10CCCCC001010AAAAA1BBBBBBBBBBBBB" },
  { "UMUL %r,-n,%r",      "10CCCCC001010AAAAA1BBBBBBBBBBBBB" },
  { "UMULCC %r,%r,%r",    "10CCCCC011010AAAAA000000000BBBBB" },
  { "UMULCC %r,i,%r",     "10CCCCC011010AAAAA1BBBBBBBBBBBBB" },
  { "UMULCC %r,+i,%r",    "10CCCCC011010AAAAA1BBBBBBBBBBBBB" },
  { "UMULCC %r,-n,%r",    "10CCCCC011010AAAAA1BBBBBBBBBBBBB" },
  { "SMUL %r,%r,%r",      "10CCCCC001011AAAAA000000000BBBBB" },
  { "SMUL %r,i,%r",       "10CCCCC001011AAAAA1BBBBBBBBBBBBB" },
  { "SMUL %r,+i,%r",      "10CCCCC001011AAAAA1BBBBBBBBBBBBB" },
  { "SMUL %r,-n,%r",      "10CCCCC001011AAAAA1BBBBBBBBBBBBB" },
  { "SMULCC %r,%r,%r",    "10CCCCC011011AAAAA000000000BBBBB" },
  { "SMULCC %r,i,%r",     "10CCCCC011011AAAAA1BBBBBBBBBBBBB" },
  { "SMULCC %r,+i,%r",    "10CCCCC011011AAAAA1BBBBBBBBBBBBB" },
  { "SMULCC %r,-n,%r",    "10CCCCC011011AAAAA1BBBBBBBBBBBBB" },
  { "UDIV %r,%r,%r",      "10CCCCC001110AAAAA000000000BBBBB" },
  { "UDIV %r,i,%r",       "10CCCCC001110AAAAA1BBBBBBBBBBBBB" },
  { "UDIV %r,+i,%r",      "10CCCCC001110AAAAA1BBBBBBBBBBBBB" },
  { "UDIV %r,-n,%r",      "10CCCCC001110AAAAA1BBBBBBBBBBBBB" },
  { "UDIVCC %r,%r,%r",    "10CCCCC011110AAAAA000000000BBBBB" },
  { "UDIVCC %r,i,%r",     "10CCCCC011110AAAAA1BBBBBBBBBBBBB" },
  { "UDIVCC %r,+i,%r",    "10CCCCC011110AAAAA1BBBBBBBBBBBBB" },
  { "UDIVCC %r,-n,%r",    "10CCCCC011110AAAAA1BBBBBBBBBBBBB" },
  { "SDIV %r,%r,%r",      "10CCCCC001111AAAAA000000000BBBBB" },
  { "SDIV %r,i,%r",       "10CCCCC001111AAAAA1BBBBBBBBBBBBB" },
  { "SDIV %r,+i,%r",      "10CCCCC001111AAAAA1BBBBBBBBBBBBB" },
  { "SDIV %r,-n,%r",      "10CCCCC001111AAAAA1BBBBBBBBBBBBB" },
  { "SDIVCC %r,%r,%r",    "10CCCCC011111AAAAA000000000BBBBB" },
  { "SDIVCC %r,i,%r",     "10CCCCC011111AAAAA1BBBBBBBBBBBBB" },
  { "SDIVCC %r,+i,%r",    "10CCCCC011111AAAAA1BBBBBBBBBBBBB" },
  { "SDIVCC %r,-n,%r",    "10CCCCC011111AAAAA1BBBBBBBBBBBBB" },
  { "SAVE %r,%r,%r",      "10CCCCC111100AAAAA000000000BBBBB" },
  { "SAVE %r,i,%r",       "10CCCCC111100AAAAA1BBBBBBBBBBBBB" },
  { "SAVE %r,+i,%r",      "10CCCCC111100AAAAA1BBBBBBBBBBBBB" },
  { "SAVE %r,-n,%r",      "10CCCCC111100AAAAA1BBBBBBBBBBBBB" },
  { "RESTORE %r,%r,%r",   "10CCCCC111101AAAAA000000000BBBBB" },
  { "RESTORE %r,i,%r",    "10CCCCC111101AAAAA1BBBBBBBBBBBBB" },
  { "RESTORE %r,+i,%r",   "10CCCCC111101AAAAA1BBBBBBBBBBBBB" },
  { "RESTORE %r,-n,%r",   "10CCCCC111101AAAAA1BBBBBBBBBBBBB" },
  { "BA d",               "0001000010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BA +i",              "0001000010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BA -n",              "0001000010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BN d",               "0000000010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BN +i",              "0000000010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BN -n",              "0000000010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNE d",              "0001001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNE +i",             "0001001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNE -n",             "0001001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNZ d",              "0001001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNZ +i",             "0001001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNZ -n",             "0001001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BE d",               "0000001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BE +i",              "0000001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BE -n",              "0000001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BZ d",               "0000001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BZ +i",              "0000001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BZ -n",              "0000001010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BG d",               "0001010010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BG +i",              "0001010010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BG -n",              "0001010010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLE d",              "0000010010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLE +i",             "0000010010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLE -n",             "0000010010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGE d",              "0001011010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGE +i",             "0001011010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGE -n",             "0001011010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BL d",               "0000011010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BL +i",              "0000011010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BL -n",              "0000011010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGU d",              "0001100010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGU +i",             "0001100010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGU -n",             "0001100010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLEU d",             "0000100010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLEU +i",            "0000100010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLEU -n",            "0000100010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BCC d",              "0001101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BCC +i",             "0001101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BCC -n",             "0001101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGEU d",             "0001101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGEU +i",            "0001101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BGEU -n",            "0001101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BCS d",              "0000101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BCS +i",             "0000101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BCS -n",             "0000101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLU d",              "0000101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLU +i",             "0000101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BLU -n",             "0000101010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BPOS d",             "0001110010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BPOS +i",            "0001110010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BPOS -n",            "0001110010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNEG d",             "0000110010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNEG +i",            "0000110010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BNEG -n",            "0000110010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BVC d",              "0001111010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BVC +i",             "0001111010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BVC -n",             "0001111010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BVS d",              "0000111010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BVS +i",             "0000111010AAAAAAAAAAAAAAAAAAAAAA" },
  { "BVS -n",             "0000111010AAAAAAAAAAAAAAAAAAAAAA" },
  { "CALL d",             "01AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" },
  { "CALL +i",            "01AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" },
  { "CALL -n",            "01AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" },
  { "JMPL %r+%r,%r",      "10CCCCC111000AAAAA000000000BBBBB" },
  { "JMPL %r+i,%r",       "10CCCCC111000AAAAA1BBBBBBBBBBBBB" },
  { "JMPL %r-n,%r",       "10CCCCC111000AAAAA1BBBBBBBBBBBBB" },
  { "TA %r+%r",           "1001000111010AAAAA000000000BBBBB" },
  { "TA %r+i",            "1001000111010AAAAA1000000BBBBBBB" },
  { "TA %r-n",            "1001000111010AAAAA1000000BBBBBBB" },
  { "TN %r+%r",           "1000000111010AAAAA000000000BBBBB" },
  { "TN %r+i",            "1000000111010AAAAA1000000BBBBBBB" },
  { "TN %r-n",            "1000000111010AAAAA1000000BBBBBBB" },
  { "TNE %r+%r",          "1001001111010AAAAA000000000BBBBB" },
  { "TNE %r+i",           "1001001111010AAAAA1000000BBBBBBB" },
  { "TNE %r-n",           "1001001111010AAAAA1000000BBBBBBB" },
  { "TNZ %r+%r",          "1001001111010AAAAA000000000BBBBB" },
  { "TNZ %r+i",           "1001001111010AAAAA1000000BBBBBBB" },
  { "TNZ %r-n",           "1001001111010AAAAA1000000BBBBBBB" },
  { "TE %r+%r",           "1000001111010AAAAA000000000BBBBB" },
  { "TE %r+i",            "1000001111010AAAAA1000000BBBBBBB" },
  { "TE %r-n",            "1000001111010AAAAA1000000BBBBBBB" },
  { "TZ %r+%r",           "1000001111010AAAAA000000000BBBBB" },
  { "TZ %r+i",            "1000001111010AAAAA1000000BBBBBBB" },
  { "TZ %r-n",            "1000001111010AAAAA1000000BBBBBBB" },
  { "TG %r+%r",           "1001010111010AAAAA000000000BBBBB" },
  { "TG %r+i",            "1001010111010AAAAA1000000BBBBBBB" },
  { "TG %r-n",            "1001010111010AAAAA1000000BBBBBBB" },
  { "TLE %r+%r",          "1000010111010AAAAA000000000BBBBB" },
  { "TLE %r+i",           "1000010111010AAAAA1000000BBBBBBB" },
  { "TLE %r-n",           "1000010111010AAAAA1000000BBBBBBB" },
  { "TGE %r+%r",          "1001011111010AAAAA000000000BBBBB" },
  { "TGE %r+i",           "1001011111010AAAAA1000000BBBBBBB" },
  { "TGE %r-n",           "1001011111010AAAAA1000000BBBBBBB" },
  { "TL %r+%r",           "1000011111010AAAAA000000000BBBBB" },
  { "TL %r+i",            "1000011111010AAAAA1000000BBBBBBB" },
  { "TL %r-n",            "1000011111010AAAAA1000000BBBBBBB" },
  { "TGU %r+%r",          "1001100111010AAAAA000000000BBBBB" },
  { "TGU %r+i",           "1001100111010AAAAA1000000BBBBBBB" },
  { "TGU %r-n",           "1001100111010AAAAA1000000BBBBBBB" },
  { "TLEU %r+%r",         "1000100111010AAAAA000000000BBBBB" },
  { "TLEU %r+i",          "1000100111010AAAAA1000000BBBBBBB" },
  { "TLEU %r-n",          "1000100111010AAAAA1000000BBBBBBB" },
  { "TCC %r+%r",          "1001101111010AAAAA000000000BBBBB" },
  { "TCC %r+i",           "1001101111010AAAAA1000000BBBBBBB" },
  { "TCC %r-n",           "1001101111010AAAAA1000000BBBBBBB" },
  { "TGEU %r+%r",         "1001101111010AAAAA000000000BBBBB" },
  { "TGEU %r+i",          "1001101111010AAAAA1000000BBBBBBB" },
  { "TGEU %r-n",          "1001101111010AAAAA1000000BBBBBBB" },
  { "TCS %r+%r",          "1000101111010AAAAA000000000BBBBB" },
  { "TCS %r+i",           "1000101111010AAAAA1000000BBBBBBB" },
  { "TCS %r-n",           "1000101111010AAAAA1000000BBBBBBB" },
  { "TLU %r+%r",          "1000101111010AAAAA000000000BBBBB" },
  { "TLU %r+i",           "1000101111010AAAAA1000000BBBBBBB" },
  { "TLU %r-n",           "1000101111010AAAAA1000000BBBBBBB" },
  { "TPOS %r+%r",         "1001110111010AAAAA000000000BBBBB" },
  { "TPOS %r+i",          "1001110111010AAAAA1000000BBBBBBB" },
  { "TPOS %r-n",          "1001110111010AAAAA1000000BBBBBBB" },
  { "TNEG %r+%r",         "1000110111010AAAAA000000000BBBBB" },
  { "TNEG %r+i",          "1000110111010AAAAA1000000BBBBBBB" },
  { "TNEG %r-n",          "1000110111010AAAAA1000000BBBBBBB" },
  { "TVC %r+%r",          "1001111111010AAAAA000000000BBBBB" },
  { "TVC %r+i",           "1001111111010AAAAA1000000BBBBBBB" },
  { "TVC %r-n",           "1001111111010AAAAA1000000BBBBBBB" },
  { "TVS %r+%r",          "1000111111010AAAAA000000000BBBBB" },
  { "TVS %r+i",           "1000111111010AAAAA1000000BBBBBBB" },
  { "TVS %r-n",           "1000111111010AAAAA1000000BBBBBBB" },
  { "RD %Y,%r",           "10AAAAA1010000000000000000000000" },
  { "WR %r,%r,%Y",        "1000000110000AAAAA000000000BBBBB" },
  { "WR %r,i,%Y",         "1000000110000AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,+i,%Y",        "1000000110000AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,-n,%Y",        "1000000110000AAAAA1BBBBBBBBBBBBB" },
  { "FBA d",              "0001000110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBA +i",             "0001000110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBA -n",             "0001000110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBN d",              "0000000110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBN +i",             "0000000110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBN -n",             "0000000110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBU d",              "0000111110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBU +i",             "0000111110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBU -n",             "0000111110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBG d",              "0000110110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBG +i",             "0000110110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBG -n",             "0000110110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUG d",             "0000101110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUG +i",            "0000101110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUG -n",            "0000101110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBL d",              "0000100110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBL +i",             "0000100110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBL -n",             "0000100110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUL d",             "0000011110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUL +i",            "0000011110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUL -n",            "0000011110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBLG d",             "0000010110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBLG +i",            "0000010110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBLG -n",            "0000010110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBNE d",             "0000001110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBNE +i",            "0000001110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBNE -n",            "0000001110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBE d",              "0001001110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBE +i",             "0001001110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBE -n",             "0001001110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUE d",             "0001010110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUE +i",            "0001010110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUE -n",            "0001010110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBGE d",             "0001011110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBGE +i",            "0001011110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBGE -n",            "0001011110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUGE d",            "0001100110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUGE +i",           "0001100110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBUGE -n",           "0001100110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBLE d",             "0001101110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBLE +i",            "0001101110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBLE -n",            "0001101110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBULE d",            "0001110110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBULE +i",           "0001110110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBULE -n",           "0001110110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBO d",              "0001111110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBO +i",             "0001111110AAAAAAAAAAAAAAAAAAAAAA" },
  { "FBO -n",             "0001111110AAAAAAAAAAAAAAAAAAAAAA" },

  { "LDSBA [%r+%r]i,%r",  "11DDDDD011001AAAAA0CCCCCCCCBBBBB" },
  { "LDSHA [%r+%r]i,%r",  "11DDDDD011010AAAAA0CCCCCCCCBBBBB" },
  { "LDUBA [%r+%r]i,%r",  "11DDDDD010001AAAAA0CCCCCCCCBBBBB" },
  { "LDUHA [%r+%r]i,%r",  "11DDDDD010010AAAAA0CCCCCCCCBBBBB" },
  { "LDA [%r+%r]i,%r",    "11DDDDD010000AAAAA0CCCCCCCCBBBBB" },
  { "LDDA [%r+%r]i,%r",   "11DDDDD010011AAAAA0CCCCCCCCBBBBB" },
  { "STBA %r,[%r+%r]i",   "11AAAAA010101BBBBB0DDDDDDDDCCCCC" },
  { "STHA %r,[%r+%r]i",   "11AAAAA010110BBBBB0DDDDDDDDCCCCC" },
  { "STA %r,[%r+%r]i",    "11AAAAA010100BBBBB0DDDDDDDDCCCCC" },
  { "STDA %r,[%r+%r]i",   "11AAAAA010111BBBBB0DDDDDDDDCCCCC" },
  { "LDSTUBA [%r+%r]i,%r","11DDDDD011101AAAAA0CCCCCCCCBBBBB" },
  { "SWAPA [%r+%r]i,%r",  "11DDDDD011111AAAAA0CCCCCCCCBBBBB" },
  { "RETT %r+%r",         "1000000111001AAAAA000000000BBBBB" },
  { "RETT %r+i",          "1000000111001AAAAA1BBBBBBBBBBBBB" },
  { "RETT %r-n",          "1000000111001AAAAA1BBBBBBBBBBBBB" },
  { "RD %PSR,%r",         "10AAAAA1010010000000000000000000" },
  { "RD %WIM,%r",         "10AAAAA1010100000000000000000000" },
  { "RD %TBR,%r",         "10AAAAA1010110000000000000000000" },
  { "WR %r,%r,%PSR",      "1000000110001AAAAA000000000BBBBB" },
  { "WR %r,i,%PSR",       "1000000110001AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,+i,%PSR",      "1000000110001AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,-n,%PSR",      "1000000110001AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,%r,%WIM",      "1000000110010AAAAA000000000BBBBB" },
  { "WR %r,i,%WIM",       "1000000110010AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,+i,%WIM",      "1000000110010AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,-n,%WIM",      "1000000110010AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,%r,%TBR",      "1000000110011AAAAA000000000BBBBB" },
  { "WR %r,i,%TBR",       "1000000110011AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,+i,%TBR",      "1000000110011AAAAA1BBBBBBBBBBBBB" },
  { "WR %r,-n,%TBR",      "1000000110011AAAAA1BBBBBBBBBBBBB" },

  { "CMP %r,%r",          "1000000010100AAAAA000000000BBBBB" },
  { "CMP %r,i",           "1000000010100AAAAA1BBBBBBBBBBBBB" },
  { "CMP %r,+i",          "1000000010100AAAAA1BBBBBBBBBBBBB" },
  { "CMP %r,-n",          "1000000010100AAAAA1BBBBBBBBBBBBB" },
  { "JMP %r+%r",          "1000000111000AAAAA000000000BBBBB" },
  { "JMP %r+i",           "1000000111000AAAAA1BBBBBBBBBBBBB" },
  { "JMP %r-n",           "1000000111000AAAAA1BBBBBBBBBBBBB" },
  { "CALL %r+%r",         "1001111111000AAAAA000000000BBBBB" },
  { "CALL %r+i",          "1001111111000AAAAA1BBBBBBBBBBBBB" },
  { "CALL %r-n",          "1001111111000AAAAA1BBBBBBBBBBBBB" },
  { "TST %r",             "100000001001000000000000000AAAAA" },
  { "RET",                "10000001110001111110000000000100" },
  { "RETL",               "10000001110000111110000000000100" },
  { "RESTORE",            "10000001111010000000000000000000" },
  { "SAVE",               "10000001111000000000000000000000" },
  { "NOT %r,%r",          "10BBBBB000111AAAAA00000000000000" },
  { "NOT %r",             "10AAAAA000111AAAAA00000000000000" },
  { "NEG %r,%r",          "10BBBBB00010000000000000000AAAAA" },
  { "NEG %r",             "10AAAAA00010000000000000000AAAAA" },
  { "INC %r",             "10AAAAA000000AAAAA10000000000001" },
  { "INC i,%r",           "10BBBBB000000BBBBB1AAAAAAAAAAAAA" },
  { "INCCC %r",           "10AAAAA010000AAAAA10000000000001" },
  { "INCCC i,%r",         "10BBBBB010000BBBBB1AAAAAAAAAAAAA" },
  { "DEC %r",             "10AAAAA000100AAAAA10000000000001" },
  { "DEC i,%r",           "10BBBBB000100BBBBB1AAAAAAAAAAAAA" },
  { "DECCC %r",           "10AAAAA010100AAAAA10000000000001" },
  { "DECCC i,%r",         "10BBBBB010100BBBBB1AAAAAAAAAAAAA" },
  { "BTST %r,%r",         "1000000010001AAAAA000000000BBBBB" },
  { "BTST i,%r",          "1000000010001BBBBB1AAAAAAAAAAAAA" },
  { "BSET %r,%r",         "10BBBBB000010AAAAA000000000BBBBB" },
  { "BSET i,%r",          "10BBBBB000010BBBBB1AAAAAAAAAAAAA" },
  { "BCLR %r,%r",         "10BBBBB000101BBBBB000000000AAAAA" },
  { "BCLR i,%r",          "10BBBBB000101BBBBB1AAAAAAAAAAAAA" },
  { "BTOG %r,%r",         "10BBBBB000011BBBBB000000000AAAAA" },
  { "BTOG i,%r",          "10BBBBB000011BBBBB1AAAAAAAAAAAAA" },
  { "CLR %r",             "10AAAAA0000100000000000000000000" },
  { "CLRB [%r+%r]",       "1100000000101AAAAA000000000BBBBB" },
  { "CLRB [%r+i]",        "1100000000101AAAAA1BBBBBBBBBBBBB" },
  { "CLRB [%r-n]",        "1100000000101AAAAA1BBBBBBBBBBBBB" },
  { "CLRH [%r+%r]",       "1100000000110AAAAA000000000BBBBB" },
  { "CLRH [%r+i]",        "1100000000110AAAAA1BBBBBBBBBBBBB" },
  { "CLRH [%r-n]",        "1100000000110AAAAA1BBBBBBBBBBBBB" },
  { "CLR [%r+%r]",        "1100000000100AAAAA000000000BBBBB" },
  { "CLR [%r+i]",         "1100000000100AAAAA1BBBBBBBBBBBBB" },
  { "CLR [%r-n]",         "1100000000100AAAAA1BBBBBBBBBBBBB" },
  { "MOV %r,%r",          "10BBBBB00001000000000000000AAAAA" },
  { "MOV i,%r",           "10BBBBB000010000001AAAAAAAAAAAAA" },
  { "MOV -n,%r",          "10BBBBB000010000001AAAAAAAAAAAAA" },
  { "MOV %Y,%r",          "10AAAAA1010000000000000000000000" },
  { "MOV %PSR,%r",        "10AAAAA1010010000000000000000000" },
  { "MOV %WIM,%r",        "10AAAAA1010100000000000000000000" },
  { "MOV %TBR,%r",        "10AAAAA1010110000000000000000000" },
  { "MOV %r,%Y",          "100000011000000000000000000AAAAA" },
  { "MOV i,%Y",           "1000000110000000001AAAAAAAAAAAAA" },
  { "MOV -n,%Y",          "1000000110000000001AAAAAAAAAAAAA" },
  { "MOV %r,%PSR",        "100000011000100000000000000AAAAA" },
  { "MOV i,%PSR",         "1000000110001000001AAAAAAAAAAAAA" },
  { "MOV -n,%PSR",        "1000000110001000001AAAAAAAAAAAAA" },
  { "MOV %r,%WIM",        "100000011001000000000000000AAAAA" },
  { "MOV i,%WIM",         "1000000110010000001AAAAAAAAAAAAA" },
  { "MOV -n,%WIM",        "1000000110010000001AAAAAAAAAAAAA" },
  { "MOV %r,%TBR",        "100000011001100000000000000AAAAA" },
  { "MOV i,%TBR",         "1000000110011000001AAAAAAAAAAAAA" },
  { "MOV -n,%TBR",        "1000000110011000001AAAAAAAAAAAAA" },

  { "FITOS %r,%f",        "10BBBBB11010000000011000100AAAAA" },
  { "FITOD %r,%f",        "10BBBBB11010000000011001000AAAAA" },
  { "FITOQ %r,%f",        "10BBBBB11010000000011001100AAAAA" },
  { "FSTOI %f,%r",        "10BBBBB11010000000011000001AAAAA" },
  { "FDTOI %f,%r",        "10BBBBB11010000000011000010AAAAA" },
  { "FQTOI %f,%r",        "10BBBBB11010000000011000011AAAAA" },
  { "FMOVS %f,%f",        "10BBBBB11010000000000000001AAAAA" },
  { "FNEGS %f,%f",        "10BBBBB11010000000000000101AAAAA" },
  { "FABSS %f,%f",        "10BBBBB11010000000000001001AAAAA" },
  { "FSQRTS %f,%f",       "10BBBBB11010000000000101001AAAAA" },
  { "FSQRTD %f,%f",       "10BBBBB11010000000000101010AAAAA" },
  { "FSQRTQ %f,%f",       "10BBBBB11010000000000101011AAAAA" },
  { "FADDS %f,%f,%f",     "10CCCCC110100AAAAA001000001BBBBB" },
  { "FADDD %f,%f,%f",     "10CCCCC110100AAAAA001000010BBBBB" },
  { "FADDQ %f,%f,%f",     "10CCCCC110100AAAAA001000011BBBBB" },
  { "FSUBS %f,%f,%f",     "10CCCCC110100AAAAA001000101BBBBB" },
  { "FSUBD %f,%f,%f",     "10CCCCC110100AAAAA001000110BBBBB" },
  { "FSUBQ %f,%f,%f",     "10CCCCC110100AAAAA001000111BBBBB" },
  { "FMULS %f,%f,%f",     "10CCCCC110100AAAAA001001001BBBBB" },
  { "FMULD %f,%f,%f",     "10CCCCC110100AAAAA001001010BBBBB" },
  { "FMULQ %f,%f,%f",     "10CCCCC110100AAAAA001001011BBBBB" },
  { "FDIVS %f,%f,%f",     "10CCCCC110100AAAAA001001101BBBBB" },
  { "FDIVD %f,%f,%f",     "10CCCCC110100AAAAA001001110BBBBB" },
  { "FDIVQ %f,%f,%f",     "10CCCCC110100AAAAA001001111BBBBB" },
  { "FCMPS %f,%f",        "1000000110100AAAAA001010001BBBBB" },
  { "FCMPD %f,%f",        "1000000110100AAAAA001010010BBBBB" },
  { "FCMPQ %f,%f",        "1000000110100AAAAA001010011BBBBB" },

  { "FSINS %f,%f",        "10BBBBB11010000000011100001AAAAA" },
  { "FSIND %f,%f",        "10BBBBB11010000000011100010AAAAA" },
  { "FSINQ %f,%f",        "10BBBBB11010000000011100011AAAAA" },
  { "FCOSS %f,%f",        "10BBBBB11010000000011100101AAAAA" },
  { "FCOSD %f,%f",        "10BBBBB11010000000011100110AAAAA" },
  { "FCOSQ %f,%f",        "10BBBBB11010000000011100111AAAAA" },
  { "FTANS %f,%f",        "10BBBBB11010000000011101001AAAAA" },
  { "FTAND %f,%f",        "10BBBBB11010000000011101010AAAAA" },
  { "FTANQ %f,%f",        "10BBBBB11010000000011101011AAAAA" },
  { "FLOGS %f,%f",        "10BBBBB11010000000011101101AAAAA" },
  { "FLOGD %f,%f",        "10BBBBB11010000000011101110AAAAA" },
  { "FLOGQ %f,%f",        "10BBBBB11010000000011101111AAAAA" },
  { "FEXPS %f,%f",        "10BBBBB11010000000011110001AAAAA" },
  { "FEXPD %f,%f",        "10BBBBB11010000000011110010AAAAA" },
  { "FEXPQ %f,%f",        "10BBBBB11010000000011110011AAAAA" },
  { "FASINS %f,%f",       "10BBBBB11010000000011110101AAAAA" },
  { "FASIND %f,%f",       "10BBBBB11010000000011110110AAAAA" },
  { "FASINQ %f,%f",       "10BBBBB11010000000011110111AAAAA" },
  { "FACOSS %f,%f",       "10BBBBB11010000000011111001AAAAA" },
  { "FACOSD %f,%f",       "10BBBBB11010000000011111010AAAAA" },
  { "FACOSQ %f,%f",       "10BBBBB11010000000011111011AAAAA" },
  { "FATANS %f,%f",       "10BBBBB11010000000011111101AAAAA" },
  { "FATAND %f,%f",       "10BBBBB11010000000011111110AAAAA" },
  { "FATANQ %f,%f",       "10BBBBB11010000000011111111AAAAA" },

  { "HALT",               "11-----1111110000000000000000000" },
  { "---",             "---" },
  };

word args[8];

int cmatch(char c1, char c2) {
  if (c1 >= 'a' && c1 <= 'z') c1 -= 32;
  if (c2 >= 'a' && c2 <= 'z') c2 -= 32;
  if (c1 == c2) return -1;
  return 0;
  }

extern word  address;
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
    if (match(ops[i].pattern, line) != 0) inst = i;
    i++;
    }
  if (inst >= 0) return translate(ops[inst].trans);
  *err = -1;
  return 0;
  }

