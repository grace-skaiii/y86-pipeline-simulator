#pragma once
#ifndef _READASSEMCODE_H
#define _READASSEMCODE_H
typedef long long ul;
typedef unsigned char uc;
extern uc *cur;
uc* getCur();
uc move2NoBlank();
void getNextInstr(char *save);
void GetNextWord(uc buff[][20]);
int isNumb(uc *c, ul *val);
int isImme(uc *c, ul *val);
void regop(uc* c, ul *val, uc* regname);
void do_tag(uc *instr);
void do_instr(char *instr);
void do_instrLine();
#endif