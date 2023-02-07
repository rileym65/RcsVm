#include "header.h"


// void getRegisters(word rs1, word rs2, word rd) {
//   if (rs1 < 8) sprintf(rs1,"%%g%d", rs1);
//   else if (rs1 < 16) sprintf(rs1,"%%o%d", rs1-8);
//   else if (rs1 < 24) sprintf(rs1,"%%l%d", rs1-16);
//   else if (rs1 < 32) sprintf(rs1,"%%i%d", rs1-24);
//   else sprintf(rs1,"%%r%d",rs1);
//   }

word Disassem(word addr, char* dest) {
  char srs1[6];
  char srs2[6];
  char srd[6];
  char tmp[80];
  char tmp2[32];
  word inst;
  word opcode;
  word disp;
  word v;
  word i;
  word rs1, rs2, rd;
  word asi;
  inst = (memory[addr] << 24) | (memory[addr+1] << 16) | (memory[addr+2] << 8) | memory[addr+3];
  opcode = ((inst >> 19) & 0x3f) | ((inst >> 24) & 0xc0);
  if ((inst & 0xc0000000) == 0x00000000) opcode &= 0xf8;
  if ((inst & 0xc0000000) == 0x40000000) opcode &= 0xc0;
  sprintf(dest,"%08x: %08x ", addr, inst);

  rs1 = (inst >> 14) & 0x1f;
  rs2 = inst & 0x1f;
  rd = (inst >> 25) & 0x1f;
  i = inst & 0x1fff;
  if (i & 0x1000) i |= 0xffffe000;
  if (rs1 < 8) sprintf(srs1,"%%g%d", rs1);
  else if (rs1 < 16) sprintf(srs1,"%%o%d", rs1-8);
  else if (rs1 < 24) sprintf(srs1,"%%l%d", rs1-16);
  else if (rs1 < 32) sprintf(srs1,"%%i%d", rs1-24);
  else sprintf(srs1,"%%r%d",rs1);
  if (rs2 < 8) sprintf(srs2,"%%g%d", rs2);
  else if (rs2 < 16) sprintf(srs2,"%%o%d", rs2-8);
  else if (rs2 < 24) sprintf(srs2,"%%l%d", rs2-16);
  else if (rs2 < 32) sprintf(srs2,"%%i%d", rs2-24);
  else sprintf(srs2,"%%r%d",rs1);
  if (rd < 8) sprintf(srd,"%%g%d", rd);
  else if (rd < 16) sprintf(srd,"%%o%d", rd-8);
  else if (rd < 24) sprintf(srd,"%%l%d", rd-16);
  else if (rd < 32) sprintf(srd,"%%i%d", rd-24);
  else sprintf(srd,"%%r%d",rd);

  addr += 4;
  switch (opcode) {
    case 0x00:
         strcat(dest,"UNDEF");
         break;
    case 0x01:
         strcat(dest,"UNDEF");
         break;
    case 0x02:
         strcat(dest,"UNDEF");
         break;
    case 0x03:
         strcat(dest,"UNDEF");
         break;
    case 0x04:
         strcat(dest,"UNDEF");
         break;
    case 0x05:
         strcat(dest,"UNDEF");
         break;
    case 0x06:
         strcat(dest,"UNDEF");
         break;
    case 0x07:
         strcat(dest,"UNDEF");
         break;
    case 0x08:
         strcat(dest,"UNDEF");
         break;
    case 0x09:
         strcat(dest,"UNDEF");
         break;
    case 0x0a:
         strcat(dest,"UNDEF");
         break;
    case 0x0b:
         strcat(dest,"UNDEF");
         break;
    case 0x0c:
         strcat(dest,"UNDEF");
         break;
    case 0x0d:
         strcat(dest,"UNDEF");
         break;
    case 0x0e:
         strcat(dest,"UNDEF");
         break;
    case 0x0f:
         strcat(dest,"UNDEF");
         break;

    case 0x10:
         disp = inst & 0x3fffff;
         if ((disp & 0x200000) != 0) disp |= 0xffc00000;
         disp <<= 2;
         disp = addr + disp - 4;
         switch ((inst >> 25) & 0x0f) {
           case 0x00:
                sprintf(tmp,"BN          %x",disp);
                strcat(dest, tmp);
                break;
           case 0x01:
                sprintf(tmp,"BE          %x",disp);
                strcat(dest, tmp);
                break;
           case 0x02:
                sprintf(tmp,"BLE         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x03:
                sprintf(tmp,"BL          %x",disp);
                strcat(dest, tmp);
                break;
           case 0x04:
                sprintf(tmp,"BLEU        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x05:
                sprintf(tmp,"BCS         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x06:
                sprintf(tmp,"BNEG        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x07:
                sprintf(tmp,"BVS         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x08:
                sprintf(tmp,"BA          %x",disp);
                strcat(dest, tmp);
                break;
           case 0x09:
                sprintf(tmp,"BNE         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0a:
                sprintf(tmp,"BG          %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0b:
                sprintf(tmp,"BGE         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0c:
                sprintf(tmp,"BGU         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0d:
                sprintf(tmp,"BCC         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0e:
                sprintf(tmp,"BPOS        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0f:
                sprintf(tmp,"BVC         %x",disp);
                strcat(dest, tmp);
                break;
           }
         break;
    case 0x11:
         strcat(dest,"UNDEF");
         break;
    case 0x12:
         strcat(dest,"UNDEF");
         break;
    case 0x13:
         strcat(dest,"UNDEF");
         break;
    case 0x14:
         strcat(dest,"UNDEF");
         break;
    case 0x15:
         strcat(dest,"UNDEF");
         break;
    case 0x16:
         strcat(dest,"UNDEF");
         break;
    case 0x17:
         strcat(dest,"UNDEF");
         break;
    case 0x18:
         strcat(dest,"UNDEF");
         break;
    case 0x19:
         strcat(dest,"UNDEF");
         break;
    case 0x1a:
         strcat(dest,"UNDEF");
         break;
    case 0x1b:
         strcat(dest,"UNDEF");
         break;
    case 0x1c:
         strcat(dest,"UNDEF");
         break;
    case 0x1d:
         strcat(dest,"UNDEF");
         break;
    case 0x1e:
         strcat(dest,"UNDEF");
         break;
    case 0x1f:
         strcat(dest,"UNDEF");
         break;

    case 0x20:
         v = (inst & 0x3fffff) << 10;
         rd = (inst >> 25) & 0x1f;
         sprintf(tmp,"SETHI       %x,%s",v,srd);
         strcat(dest, tmp);
         break;
    case 0x21:
         strcat(dest,"UNDEF");
         break;
    case 0x22:
         strcat(dest,"UNDEF");
         break;
    case 0x23:
         strcat(dest,"UNDEF");
         break;
    case 0x24:
         strcat(dest,"UNDEF");
         break;
    case 0x25:
         strcat(dest,"UNDEF");
         break;
    case 0x26:
         strcat(dest,"UNDEF");
         break;
    case 0x27:
         strcat(dest,"UNDEF");
         break;
    case 0x28:
         strcat(dest,"UNDEF");
         break;
    case 0x29:
         strcat(dest,"UNDEF");
         break;
    case 0x2a:
         strcat(dest,"UNDEF");
         break;
    case 0x2b:
         strcat(dest,"UNDEF");
         break;
    case 0x2c:
         strcat(dest,"UNDEF");
         break;
    case 0x2d:
         strcat(dest,"UNDEF");
         break;
    case 0x2e:
         strcat(dest,"UNDEF");
         break;
    case 0x2f:
         strcat(dest,"UNDEF");
         break;

    case 0x30:
         disp = inst & 0x3fffff;
         if ((disp & 0x200000) != 0) disp |= 0xffc00000;
         disp <<= 2;
         disp = addr + disp - 4;
         switch ((inst >> 25) & 0x0f) {
           case 0x00:
                sprintf(tmp,"FBN         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x01:
                sprintf(tmp,"FBNE        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x02:
                sprintf(tmp,"FBLG        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x03:
                sprintf(tmp,"FBUL        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x04:
                sprintf(tmp,"FBL         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x05:
                sprintf(tmp,"FBUG        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x06:
                sprintf(tmp,"FBG         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x07:
                sprintf(tmp,"FBU         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x08:
                sprintf(tmp,"FBA         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x09:
                sprintf(tmp,"FBE         %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0a:
                sprintf(tmp,"FBUE        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0b:
                sprintf(tmp,"FBGE        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0c:
                sprintf(tmp,"FBUGE       %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0d:
                sprintf(tmp,"FBLE        %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0e:
                sprintf(tmp,"FBULE       %x",disp);
                strcat(dest, tmp);
                break;
           case 0x0f:
                sprintf(tmp,"FBO         %x",disp);
                strcat(dest, tmp);
                break;
           }
         break;
    case 0x31:
         strcat(dest,"UNDEF");
         break;
    case 0x32:
         strcat(dest,"UNDEF");
         break;
    case 0x33:
         strcat(dest,"UNDEF");
         break;
    case 0x34:
         strcat(dest,"UNDEF");
         break;
    case 0x35:
         strcat(dest,"UNDEF");
         break;
    case 0x36:
         strcat(dest,"UNDEF");
         break;
    case 0x37:
         strcat(dest,"UNDEF");
         break;
    case 0x38:
         strcat(dest,"UNDEF");
         break;
    case 0x39:
         strcat(dest,"UNDEF");
         break;
    case 0x3a:
         strcat(dest,"UNDEF");
         break;
    case 0x3b:
         strcat(dest,"UNDEF");
         break;
    case 0x3c:
         strcat(dest,"UNDEF");
         break;
    case 0x3d:
         strcat(dest,"UNDEF");
         break;
    case 0x3e:
         strcat(dest,"UNDEF");
         break;
    case 0x3f:
         strcat(dest,"UNDEF");
         break;

    case 0x40:
         disp = (inst & 0x3fffffff) << 2;
         disp = addr + disp - 4;
         sprintf(tmp,"CALL        %x",disp);
         strcat(dest, tmp);
         break;
    case 0x41:
         strcat(dest,"UNDEF");
         break;
    case 0x42:
         strcat(dest,"UNDEF");
         break;
    case 0x43:
         strcat(dest,"UNDEF");
         break;
    case 0x44:
         strcat(dest,"UNDEF");
         break;
    case 0x45:
         strcat(dest,"UNDEF");
         break;
    case 0x46:
         strcat(dest,"UNDEF");
         break;
    case 0x47:
         strcat(dest,"UNDEF");
         break;
    case 0x48:
         strcat(dest,"UNDEF");
         break;
    case 0x49:
         strcat(dest,"UNDEF");
         break;
    case 0x4a:
         strcat(dest,"UNDEF");
         break;
    case 0x4b:
         strcat(dest,"UNDEF");
         break;
    case 0x4c:
         strcat(dest,"UNDEF");
         break;
    case 0x4d:
         strcat(dest,"UNDEF");
         break;
    case 0x4e:
         strcat(dest,"UNDEF");
         break;
    case 0x4f:
         strcat(dest,"UNDEF");
         break;

    case 0x50:
         strcat(dest,"UNDEF");
         break;
    case 0x51:
         strcat(dest,"UNDEF");
         break;
    case 0x52:
         strcat(dest,"UNDEF");
         break;
    case 0x53:
         strcat(dest,"UNDEF");
         break;
    case 0x54:
         strcat(dest,"UNDEF");
         break;
    case 0x55:
         strcat(dest,"UNDEF");
         break;
    case 0x56:
         strcat(dest,"UNDEF");
         break;
    case 0x57:
         strcat(dest,"UNDEF");
         break;
    case 0x58:
         strcat(dest,"UNDEF");
         break;
    case 0x59:
         strcat(dest,"UNDEF");
         break;
    case 0x5a:
         strcat(dest,"UNDEF");
         break;
    case 0x5b:
         strcat(dest,"UNDEF");
         break;
    case 0x5c:
         strcat(dest,"UNDEF");
         break;
    case 0x5d:
         strcat(dest,"UNDEF");
         break;
    case 0x5e:
         strcat(dest,"UNDEF");
         break;
    case 0x5f:
         strcat(dest,"UNDEF");
         break;

    case 0x60:
         strcat(dest,"UNDEF");
         break;
    case 0x61:
         strcat(dest,"UNDEF");
         break;
    case 0x62:
         strcat(dest,"UNDEF");
         break;
    case 0x63:
         strcat(dest,"UNDEF");
         break;
    case 0x64:
         strcat(dest,"UNDEF");
         break;
    case 0x65:
         strcat(dest,"UNDEF");
         break;
    case 0x66:
         strcat(dest,"UNDEF");
         break;
    case 0x67:
         strcat(dest,"UNDEF");
         break;
    case 0x68:
         strcat(dest,"UNDEF");
         break;
    case 0x69:
         strcat(dest,"UNDEF");
         break;
    case 0x6a:
         strcat(dest,"UNDEF");
         break;
    case 0x6b:
         strcat(dest,"UNDEF");
         break;
    case 0x6c:
         strcat(dest,"UNDEF");
         break;
    case 0x6d:
         strcat(dest,"UNDEF");
         break;
    case 0x6e:
         strcat(dest,"UNDEF");
         break;
    case 0x6f:
         strcat(dest,"UNDEF");
         break;

    case 0x70:
         strcat(dest,"UNDEF");
         break;
    case 0x71:
         strcat(dest,"UNDEF");
         break;
    case 0x72:
         strcat(dest,"UNDEF");
         break;
    case 0x73:
         strcat(dest,"UNDEF");
         break;
    case 0x74:
         strcat(dest,"UNDEF");
         break;
    case 0x75:
         strcat(dest,"UNDEF");
         break;
    case 0x76:
         strcat(dest,"UNDEF");
         break;
    case 0x77:
         strcat(dest,"UNDEF");
         break;
    case 0x78:
         strcat(dest,"UNDEF");
         break;
    case 0x79:
         strcat(dest,"UNDEF");
         break;
    case 0x7a:
         strcat(dest,"UNDEF");
         break;
    case 0x7b:
         strcat(dest,"UNDEF");
         break;
    case 0x7c:
         strcat(dest,"UNDEF");
         break;
    case 0x7d:
         strcat(dest,"UNDEF");
         break;
    case 0x7e:
         strcat(dest,"UNDEF");
         break;
    case 0x7f:
         strcat(dest,"UNDEF");
         break;

    case 0x80:
         if (inst & 0x2000)
           sprintf(tmp,"ADD         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ADD         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x81:
         if (inst & 0x2000)
           sprintf(tmp,"AND         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"AND         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x82:
         if (inst & 0x2000)
           sprintf(tmp,"OR          %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"OR          %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x83:
         if (inst & 0x2000)
           sprintf(tmp,"XOR         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"XOR         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x84:
         if (inst & 0x2000)
           sprintf(tmp,"SUB         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SUB         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x85:
         if (inst & 0x2000)
           sprintf(tmp,"ANDN        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ANDN        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x86:
         if (inst & 0x2000)
           sprintf(tmp,"ORN         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ORN         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x87:
         if (inst & 0x2000)
           sprintf(tmp,"XNOR        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"XNOR        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x88:
         if (inst & 0x2000)
           sprintf(tmp,"ADDX        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ADDX        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x89:
         strcat(dest,"UNDEF");
         break;
    case 0x8a:
         if (inst & 0x2000)
           sprintf(tmp,"UMUL        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"UMUL        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x8b:
         if (inst & 0x2000)
           sprintf(tmp,"SMUL        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SMUL        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x8c:
         if (inst & 0x2000)
           sprintf(tmp,"SUBX        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SUBX        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x8d:
         strcat(dest,"UNDEF");
         break;
    case 0x8e:
         if (inst & 0x2000)
           sprintf(tmp,"UDIV        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"UDIV        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x8f:
         if (inst & 0x2000)
           sprintf(tmp,"SDIV        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SDIV        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;

    case 0x90:
         if (inst & 0x2000)
           sprintf(tmp,"ADDCC       %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ADDCC       %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x91:
         if (inst & 0x2000)
           sprintf(tmp,"ANDCC       %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ANDCC       %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x92:
         if (inst & 0x2000)
           sprintf(tmp,"ORCC        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ORCC        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x93:
         if (inst & 0x2000)
           sprintf(tmp,"XORCC       %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"XORCC       %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x94:
         if (inst & 0x2000)
           sprintf(tmp,"SUBCC       %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SUBCC       %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x95:
         if (inst & 0x2000)
           sprintf(tmp,"ANDNCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ANDNCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x96:
         if (inst & 0x2000)
           sprintf(tmp,"ORNCC       %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ORNCC       %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x97:
         if (inst & 0x2000)
           sprintf(tmp,"XNORCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"XNORCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x98:
         if (inst & 0x2000)
           sprintf(tmp,"ADDXCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"ADDXCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x99:
         strcat(dest,"UNDEF");
         break;
    case 0x9a:
         if (inst & 0x2000)
           sprintf(tmp,"UMULCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"UMULCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x9b:
         if (inst & 0x2000)
           sprintf(tmp,"SMULCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SMULCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x9c:
         if (inst & 0x2000)
           sprintf(tmp,"SUBXCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SUBXCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x9d:
         strcat(dest,"UNDEF");
         break;
    case 0x9e:
         if (inst & 0x2000)
           sprintf(tmp,"UDIVCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"UDIVCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0x9f:
         if (inst & 0x2000)
           sprintf(tmp,"SDIVCC      %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SDIVCC      %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;

    case 0xa0:
         strcat(dest,"UNDEF");
         break;
    case 0xa1:
         strcat(dest,"UNDEF");
         break;
    case 0xa2:
         strcat(dest,"UNDEF");
         break;
    case 0xa3:
         strcat(dest,"UNDEF");
         break;
    case 0xa4:
         strcat(dest,"UNDEF");
         break;
    case 0xa5:
         if (inst & 0x2000)
           sprintf(tmp,"SLL         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SLL         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xa6:
         if (inst & 0x2000)
           sprintf(tmp,"SRL         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SRL         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xa7:
         if (inst & 0x2000)
           sprintf(tmp,"SRA         %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SRA         %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xa8:
         rd = (inst >> 25) & 0x1f;
         sprintf(tmp,"RD          %%y,%s",srd);
         strcat(dest, tmp);
         break;
    case 0xa9:
         rd = (inst >> 25) & 0x1f;
         sprintf(tmp,"RD          %%psr,%s",srd);
         strcat(dest, tmp);
         break;
    case 0xaa:
         rd = (inst >> 25) & 0x1f;
         sprintf(tmp,"RD          %%wim,%s",srd);
         strcat(dest, tmp);
         break;
    case 0xab:
         rd = (inst >> 25) & 0x1f;
         sprintf(tmp,"RD          %%tbr,%s",srd);
         strcat(dest, tmp);
         break;
    case 0xac:
         strcat(dest,"UNDEF");
         break;
    case 0xad:
         strcat(dest,"UNDEF");
         break;
    case 0xae:
         strcat(dest,"UNDEF");
         break;
    case 0xaf:
         strcat(dest,"UNDEF");
         break;

    case 0xb0:
         if (inst & 0x2000)
           sprintf(tmp,"WR          %s,%d,%%y",srs1,i);
         else
           sprintf(tmp,"WR          %s,%s,%%y",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xb1:
         if (inst & 0x2000)
           sprintf(tmp,"WR          %s,%d,%%psr",srs1,i);
         else
           sprintf(tmp,"WR          %s,%s,%%psr",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xb2:
         if (inst & 0x2000)
           sprintf(tmp,"WR          %s,%d,%%wim",srs1,i);
         else
           sprintf(tmp,"WR          %s,%s,%%wim",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xb3:
         if (inst & 0x2000)
           sprintf(tmp,"WR          %s,%d,%%tbr",srs1,i);
         else
           sprintf(tmp,"WR          %s,%s,%%tbr",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xb4:
    case 0xb5:
         i = (inst >> 5) & 0x1ff;
         switch (i) {
           case 0x01: 
                sprintf(tmp,"FMOVS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0x05: 
                sprintf(tmp,"FNEGS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0x09: 
                sprintf(tmp,"FABSS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0x29: 
                sprintf(tmp,"FSQRTS      %%f%d,%%f%d",rs2,rd);
                break;
           case 0x2a: 
                sprintf(tmp,"FSQRTD      %%f%d,%%f%d",rs2,rd);
                break;
           case 0x2b: 
                sprintf(tmp,"FSQRTQ      %%f%d,%%f%d",rs2,rd);
                break;
           case 0x41: 
                sprintf(tmp,"FADDS       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x42: 
                sprintf(tmp,"FADDD       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x43: 
                sprintf(tmp,"FADDQ       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x45: 
                sprintf(tmp,"FSUBS       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x46: 
                sprintf(tmp,"FSUBD       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x47: 
                sprintf(tmp,"FSUBQ       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x49: 
                sprintf(tmp,"FMULS       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x4a: 
                sprintf(tmp,"FMULD       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x4b: 
                sprintf(tmp,"FMULQ       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x4d: 
                sprintf(tmp,"FDIVS       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x4e: 
                sprintf(tmp,"FDIVD       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x4f: 
                sprintf(tmp,"FDIVQ       %%f%d,%%f%d,%%f%d",rs1,rs2,rd);
                break;
           case 0x51: 
                sprintf(tmp,"FCMPS       %%f%d,%%f%d",rs1,rs2);
                break;
           case 0x52: 
                sprintf(tmp,"FCMPD       %%f%d,%%f%d",rs1,rs2);
                break;
           case 0x53: 
                sprintf(tmp,"FCMPF       %%f%d,%%f%d",rs1,rs2);
                break;
           case 0xc1: 
                sprintf(tmp,"FSTOI       %%f%d,%s",rs2,srd);
                break;
           case 0xc2: 
                sprintf(tmp,"FDTOI       %%f%d,%s",rs2,srd);
                break;
           case 0xc3: 
                sprintf(tmp,"FQTOI       %%f%d,%s",rs2,srd);
                break;
           case 0xc4: 
                sprintf(tmp,"FITOS       %s,%%f%d",srs2,rd);
                break;
           case 0xc8: 
                sprintf(tmp,"FITOD       %s,%%f%d",srs2,rd);
                break;
           case 0xcc: 
                sprintf(tmp,"FITOQ       %s,%%f%d",srs2,rd);
                break;
           case 0xe1: 
                sprintf(tmp,"FSINS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xe2: 
                sprintf(tmp,"FSIND       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xe3: 
                sprintf(tmp,"FSINQ       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xe5: 
                sprintf(tmp,"FCOSS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xe6: 
                sprintf(tmp,"FCOSD       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xe7: 
                sprintf(tmp,"FCOSQ       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xe9: 
                sprintf(tmp,"FTANS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xea: 
                sprintf(tmp,"FTAND       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xeb: 
                sprintf(tmp,"FTANQ       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xed: 
                sprintf(tmp,"FLOGS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xee: 
                sprintf(tmp,"FLOGD       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xef: 
                sprintf(tmp,"FLOGQ       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf1: 
                sprintf(tmp,"FEXPS       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf2: 
                sprintf(tmp,"FEXPD       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf3: 
                sprintf(tmp,"FEXPF       %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf5: 
                sprintf(tmp,"FASINS      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf6: 
                sprintf(tmp,"FASIND      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf7: 
                sprintf(tmp,"FASINQ      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xf9: 
                sprintf(tmp,"FACOSD      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xfa: 
                sprintf(tmp,"FACOSD      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xfb: 
                sprintf(tmp,"FACOSD      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xfd: 
                sprintf(tmp,"FATAND      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xfe: 
                sprintf(tmp,"FATAND      %%f%d,%%f%d",rs2,rd);
                break;
           case 0xff: 
                sprintf(tmp,"FATAND      %%f%d,%%f%d",rs2,rd);
                break;
           default:
                sprintf(tmp,"UNDEF: %02x",i);
                break;
           }
         strcat(dest, tmp);
         break;
    case 0xb6:
         strcat(dest,"UNDEF");
         break;
    case 0xb7:
         strcat(dest,"UNDEF");
         break;
    case 0xb8:
         if (inst & 0x2000)
           sprintf(tmp,"JMPL        %s+%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"JMPL        %s+%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xb9:
         if (inst & 0x2000)
           sprintf(tmp,"RETT        %s+%d",srs1,i);
         else
           sprintf(tmp,"RETT        %s+%s",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xba:
         if (inst & 0x2000)
           sprintf(tmp2,"%s+%d",srs1,i);
         else
           sprintf(tmp,"%s+%s",srs1,srs2);
         switch ((inst >> 25) & 0x0f) {
           case 0x00:
                sprintf(tmp,"TN          %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x01:
                sprintf(tmp,"TE          %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x02:
                sprintf(tmp,"TLE         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x03:
                sprintf(tmp,"TL          %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x04:
                sprintf(tmp,"TLEU        %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x05:
                sprintf(tmp,"TCS         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x06:
                sprintf(tmp,"TNEG        %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x07:
                sprintf(tmp,"TVS         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x08:
                sprintf(tmp,"TA          %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x09:
                sprintf(tmp,"TNE         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x0a:
                sprintf(tmp,"TG          %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x0b:
                sprintf(tmp,"TGE         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x0c:
                sprintf(tmp,"TGU         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x0d:
                sprintf(tmp,"TCC         %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x0e:
                sprintf(tmp,"TPOS        %s",tmp2);
                strcat(dest, tmp);
                break;
           case 0x0f:
                sprintf(tmp,"TVC         %s",tmp2);
                strcat(dest, tmp);
                break;
           }
         break;
    case 0xbb:
         strcat(dest,"UNDEF");
         break;
    case 0xbc:
         if (inst & 0x2000)
           sprintf(tmp,"SAVE        %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"SAVE        %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xbd:
         if (inst & 0x2000)
           sprintf(tmp,"RESTORE     %s,%d,%s",srs1,i,srd);
         else
           sprintf(tmp,"RESTORE     %s,%s,%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xbe:
         strcat(dest,"UNDEF");
         break;
    case 0xbf:
         strcat(dest,"UNDEF");
         break;

    case 0xc0:
         if (inst & 0x2000)
           sprintf(tmp,"LD          [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LD          [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xc1:
         if (inst & 0x2000)
           sprintf(tmp,"LDUB        [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LDUB        [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xc2:
         if (inst & 0x2000)
           sprintf(tmp,"LDUH        [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LDUH        [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xc3:
         if (inst & 0x2000)
           sprintf(tmp,"LDD         [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LDD         [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xc4:
         if (inst & 0x2000)
           sprintf(tmp,"ST          %s,[%s+%d]",srd,srs1,i);
         else
           sprintf(tmp,"ST          %s,[%s+%s]",srd,srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xc5:
         if (inst & 0x2000)
           sprintf(tmp,"STB         %s,[%s+%d]",srd,srs1,i);
         else
           sprintf(tmp,"STB         %s,[%s+%s]",srd,srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xc6:
         if (inst & 0x2000)
           sprintf(tmp,"STH         %s,[%s+%d]",srd,srs1,i);
         else
           sprintf(tmp,"STH         %s,[%s+%s]",srd,srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xc7:
         if (inst & 0x2000)
           sprintf(tmp,"STD         %s,[%s+%d]",srd,srs1,i);
         else
           sprintf(tmp,"STD         %s,[%s+%s]",srd,srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xc8:
         strcat(dest,"UNDEF");
         break;
    case 0xc9:
         if (inst & 0x2000)
           sprintf(tmp,"LDSB        [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LDSB        [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xca:
         if (inst & 0x2000)
           sprintf(tmp,"LDSH        [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LDSH        [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xcb:
         strcat(dest,"UNDEF");
         break;
    case 0xcc:
         strcat(dest,"UNDEF");
         break;
    case 0xcd:
         if (inst & 0x2000)
           sprintf(tmp,"LDSTUB      [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"LDSTUB      [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;
    case 0xce:
         strcat(dest,"UNDEF");
         break;
    case 0xcf:
         if (inst & 0x2000)
           sprintf(tmp,"SWAP        [%s+%d],%s",srs1,i,srd);
         else
           sprintf(tmp,"SWAP        [%s+%s],%s",srs1,srs2,srd);
         strcat(dest, tmp);
         break;

    case 0xd0:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDA         [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDA         [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xd1:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDUBA       [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDUBA       [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xd2:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDUHA       [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDUHA       [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xd3:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDDA        [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDDA        [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xd4:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"STA         %s,[%s+%d]%d",srd,srs1,i,asi);
         else
           sprintf(tmp,"STA         %s,[%s+%s]%d",srd,srs1,srs2,asi);
         strcat(dest, tmp);
         break;
    case 0xd5:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"STBA        %s,[%s+%d]%d",srd,srs1,i,asi);
         else
           sprintf(tmp,"STBA        %s,[%s+%s]%d",srd,srs1,srs2,asi);
         strcat(dest, tmp);
         break;
    case 0xd6:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"STHA        %s,[%s+%d]%d",srd,srs1,i,asi);
         else
           sprintf(tmp,"STHA        %s,[%s+%s]%d",srd,srs1,srs2,asi);
         strcat(dest, tmp);
         break;
    case 0xd7:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"STDA        %s,[%s+%d]%d",srd,srs1,i,asi);
         else
           sprintf(tmp,"STDA        %s,[%s+%s]%d",srd,srs1,srs2,asi);
         strcat(dest, tmp);
         break;
    case 0xd8:
         strcat(dest,"UNDEF");
         break;
    case 0xd9:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDSBA       [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDSBA       [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xda:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDSHA       [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDSHA       [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xdb:
         strcat(dest,"UNDEF");
         break;
    case 0xdc:
         strcat(dest,"UNDEF");
         break;
    case 0xdd:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"LDSTUBA     [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"LDSTUBA     [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;
    case 0xde:
         strcat(dest,"UNDEF");
         break;
    case 0xdf:
         asi = (inst >> 5) & 0xff;
         if (inst & 0x2000)
           sprintf(tmp,"SWAPA       [%s+%d]%d,%s",srs1,i,asi,srd);
         else
           sprintf(tmp,"SWAPA       [%s+%s]%d,%s",srs1,srs2,asi,srd);
         strcat(dest, tmp);
         break;

    case 0xe0:
         if (inst & 0x2000)
           sprintf(tmp,"LD          [%s+%d],%%f%d",srs1,i,rd);
         else
           sprintf(tmp,"LD          [%s+%s],%%f%d",srs1,srs2,rd);
         strcat(dest, tmp);
         break;
    case 0xe1:
         if (inst & 0x2000)
           sprintf(tmp,"LD          [%s+%d],%%fsr",srs1,i);
         else
           sprintf(tmp,"LD          [%s+%s],%%fsr",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xe2:
         strcat(dest,"UNDEF");
         break;
    case 0xe3:
         if (inst & 0x2000)
           sprintf(tmp,"LDD         [%s+%d],%%f%d",srs1,i,rd);
         else
           sprintf(tmp,"LDD         [%s+%s],%%f%d",srs1,srs2,rd);
         strcat(dest, tmp);
         break;
    case 0xe4:
         if (inst & 0x2000)
           sprintf(tmp,"ST          %%f%d,[%s+%d]",rd,srs1,i);
         else
           sprintf(tmp,"ST          %%f%d,[%s+%s]",rd,srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xe5:
         if (inst & 0x2000)
           sprintf(tmp,"ST          %%fsr,[%s+%d]",srs1,i);
         else
           sprintf(tmp,"ST          %%fsr,[%s+%s]",srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xe6:
         strcat(dest,"UNDEF");
         break;
    case 0xe7:
         if (inst & 0x2000)
           sprintf(tmp,"STD         %%f%d,[%s+%d]",rd,srs1,i);
         else
           sprintf(tmp,"STD         %%f%d,[%s+%s]",rd,srs1,srs2);
         strcat(dest, tmp);
         break;
    case 0xe8:
         strcat(dest,"UNDEF");
         break;
    case 0xe9:
         strcat(dest,"UNDEF");
         break;
    case 0xea:
         strcat(dest,"UNDEF");
         break;
    case 0xeb:
         strcat(dest,"UNDEF");
         break;
    case 0xec:
         strcat(dest,"UNDEF");
         break;
    case 0xed:
         strcat(dest,"UNDEF");
         break;
    case 0xee:
         strcat(dest,"UNDEF");
         break;
    case 0xef:
         strcat(dest,"UNDEF");
         break;

    case 0xf0:
         strcat(dest,"UNDEF");
         break;
    case 0xf1:
         strcat(dest,"UNDEF");
         break;
    case 0xf2:
         strcat(dest,"UNDEF");
         break;
    case 0xf3:
         strcat(dest,"UNDEF");
         break;
    case 0xf4:
         strcat(dest,"UNDEF");
         break;
    case 0xf5:
         strcat(dest,"UNDEF");
         break;
    case 0xf6:
         strcat(dest,"UNDEF");
         break;
    case 0xf7:
         strcat(dest,"UNDEF");
         break;
    case 0xf8:
         strcat(dest,"UNDEF");
         break;
    case 0xf9:
         strcat(dest,"UNDEF");
         break;
    case 0xfa:
         strcat(dest,"UNDEF");
         break;
    case 0xfb:
         strcat(dest,"UNDEF");
         break;
    case 0xfc:
         strcat(dest,"UNDEF");
         break;
    case 0xfd:
         strcat(dest,"UNDEF");
         break;
    case 0xfe:
         strcat(dest,"UNDEF");
         break;
    case 0xff:
         strcat(dest,"HALT");
         break;
    default: 
         sprintf(tmp,"             DB     $%02x",memory[addr]); addr++; break;
    }
//  strcat(dest, tmp);
  return addr;
  }

