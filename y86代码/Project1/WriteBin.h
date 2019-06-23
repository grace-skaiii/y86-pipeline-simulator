#pragma once
#ifndef _WRITEBIN_H
#define _WRITEBIN_H
#define MAXLEN 0x400+5
typedef long long ul;
typedef unsigned char uc;
extern uc bin[MAXLEN];
extern ul pos;
typedef void(*instr_handl)();//º¯Êý¾ä±ú
struct instructions
{
	uc name[20];
	uc id[2];
	instr_handl handle;
};
struct reg_s
{
	uc name[20];
	uc id;
};

void do_pos();
void do_align();
void do_quad();
void do_nop();
void do_halt();
void do_rrmovq();
void do_irmovq();
void do_rmmovq();
void do_mrmovq();
void do_addq();
void do_subq();
void do_andq();
void do_xorq();
void do_jmp();
void do_jle();
void do_jl();
void do_je();
void do_jne();
void do_jge();
void do_jg();
void do_cmovle();
void do_cmovl();
void do_cmove();
void do_cmovne();
void do_cmovge();
void do_cmovg();
void do_call();
void do_ret();
void do_pushq();
void do_popq();
void do_iaddq();
instr_handl instrHandleByname(char * name);
uc*  instrIdByname(char *name);
uc  regIdByname(uc *name);
ul getPos();
void writeByte2Bin(uc *byte, ul  n);
ul alignAddr(ul num);
void write_imme(uc* t);
void rewrite();
#endif
