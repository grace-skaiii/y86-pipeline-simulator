#include"WriteBin.h"
#include"ReadAssemCode.h"
#include"Tag.h"
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<iostream>
using namespace std;
uc bin[MAXLEN];
ul pos = 0;
struct instructions instrs[] =
{
	{".pos", {'f','f'}, do_pos},
	{".align", {'f','f'}, do_align},
	{".quad",{'f','f'}, do_quad},
	{"nop", {'0','0'}, do_nop},
	{"halt", {'1','0'}, do_halt},
	{"rrmovq", {'2','0'}, do_rrmovq},
	{"irmovq", {'3','0'}, do_irmovq},
	{"rmmovq", {'4','0'}, do_rmmovq},
	{"mrmovq", {'5','0'}, do_mrmovq},
	{"addq", {'6','0'}, do_addq},
	{"subq", {'6','1'}, do_subq},
	{"andq", {'6','2'}, do_andq},
	{"xorq", {'6','3'}, do_xorq},
	{"jmp", {'7','0'}, do_jmp},
	{"jle", {'7','1'}, do_jle},
	{"jl", {'7','2'}, do_jl},
	{"je", {'7','3'}, do_je},
	{"jne", {'7','4'}, do_jne},
	{"jge", {'7','5'}, do_jge},
	{"jg", {'7','6'}, do_jg},
	{"cmovle", {'2','1'}, do_cmovle},
	{"cmovl", {'2','2'}, do_cmovl},
	{"cmove", {'2','3'}, do_cmove},
	{"cmovne", {'2','4'}, do_cmovne},
	{"cmovge", {'2','5'}, do_cmovge},
	{"cmovg", {'2','6'}, do_cmovg},
	{"call", {'8','0'}, do_call},
	{"ret", {'9','0'}, do_ret},
	{"pushq", {'a','0'}, do_pushq},
	{"popq", {'b','0'}, do_popq},
	{"iaddq",{'c','0'},do_iaddq},
	{"..", {'f','f'}, NULL}
};
struct reg_s regs[] =
{
	{"%rax", '0'},
	{"%rcx", '1'},
	{"%rdx", '2'},
	{"%rbx", '3'},
	{"%rsp", '4'},
	{"%rbp", '5'},
	{"%rsi", '6'},
	{"%rdi", '7'},
	{"%r8",'8'},
	{"%r9",'9'},
	{"%r10",'a'},
	{"%r11",'b'},
	{"%r12",'c'},
	{"%r13",'d'},
	{"%r14",'e'},
	{"..", 'f'}
};
instr_handl instrHandleByname(char * name)
{
	int i;
	for (i = 0; strcmp("..", (char*)instrs[i].name) != 0; i++)
	{
		if (strcmp(name, (char*)instrs[i].name) == 0)
			return instrs[i].handle;
	}
	return NULL;
}
uc*  instrIdByname(char *name)
{
	int i;
	for (i = 0; strcmp("..", (char*)instrs[i].name) != 0; i++)
	{
		if (strcmp(name, (char*)instrs[i].name) == 0)
		{
			//cout << "hh" << endl;
			return instrs[i].id;
		}
	}
	uc id[2] = { '0','0' };
	return id;
}
uc  regIdByname(uc *name)
{
	int i;
	for (i = 0; strcmp("..", (char*)regs[i].name) != 0; i++)
	{
		if (strcmp((char*)name, (char*)regs[i].name) == 0)
		{
			//cout << "hh" << endl;
			return regs[i].id;
		}
	}
	return 'f';
}
ul getPos()
{
	return pos;
}
void writeByte2Bin(uc *byte, ul  n)
{
	ul i = 0;
	while (i < n)
	{
		//cout << pos << "p";
		bin[pos++] = *byte;
		byte++;
		i++;
	}
}
ul alignAddr(ul num)
{
	ul tmp = num * 2;
	ul newpos = (pos + tmp - 1) / tmp * tmp;
	return newpos;//返回新地址
}
void write_imme(uc* t)
{
	int i = strlen((char*)t) - 1, re;
	uc temp = '0';
	if (!(i % 2))
	{
		re = 16 - i;
		while (i >= 4)
		{
			uc temp = t[i - 1];
			writeByte2Bin(&temp, 1);
			temp = t[i];
			writeByte2Bin(&temp, 1);
			i -= 2;
		}
		if (i == 2)
		{
			uc temp = '0';
			writeByte2Bin(&temp, 1);
			temp = t[i];
			writeByte2Bin(&temp, 1);
		}
		while (re--)
			writeByte2Bin(&temp, 1);
	}
	if (i % 2)
	{
		re = 17 - i;
		while (i >= 3)
		{
			uc temp = t[i - 1];
			writeByte2Bin(&temp, 1);
			temp = t[i];
			writeByte2Bin(&temp, 1);
			i -= 2;
		}
		while (re--)
		{
			writeByte2Bin(&temp, 1);
		}
	}
}
void do_pos()
{
	uc buff[2][20];
	GetNextWord(buff);
	ul addr = 0;
	isNumb(buff[0], &addr);
	uc temp = '0';
	while (pos < addr * 2)
	{
		writeByte2Bin(&temp, 1);
	}
}

void do_align()
{
	ul tmp;
	uc buff[2][20];
	GetNextWord(buff);
	isNumb(buff[0], &tmp);
	ul newpos = alignAddr(tmp);
	//cout << oldpos << "maya" << endl;
	uc temp = '0';
	ul i = newpos - pos;
	while (i > 0)
	{
		writeByte2Bin(&temp, 1);
		i--;
	}
}
void do_quad()
{
	uc buff[2][20];
	GetNextWord(buff);
	ul im = 0;
	if (!(isNumb(buff[0], &im)))//是tag
	{
		int i;
		if ((i = find(buff[0])) != -1)//在tag中找到
		{
			ul poss = tags[i].pos;
			char p[20];
			p[0] = '0'; p[1] = 'x';
			sprintf(p + 2, "%llx", poss / 2);
			write_imme((uc*)p);
		}
		else//在后面 存起来
		{
			ul save = pos;
			uc temp[16];
			memset(temp, 'x', 16 * sizeof(uc));
			writeByte2Bin(temp, 16);
			tab(buff[0], save);
		}
	}
	else
	{
		write_imme(buff[0]);
	}
}
void do_nop()
{
	uc bytes[] = { '1','0' };
	writeByte2Bin(bytes, 2);
}
void do_halt()
{
	uc bytes[] = { '0','0' };
	writeByte2Bin(bytes, 2);
}
void do_rrmovq()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "rrmovq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	writeByte2Bin(bytes, 2);
	uc temp = regIdByname(buff[0]);
	writeByte2Bin(&temp, 1);
	temp = regIdByname(buff[1]);
	writeByte2Bin(&temp, 1);
}
void do_irmovq()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "irmovq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	writeByte2Bin(bytes, 2);
	uc temp = 'f';
	writeByte2Bin(&temp, 1);
	temp = regIdByname(buff[1]);
	writeByte2Bin(&temp, 1);
	ul im = 0;
	if (!(isImme(buff[0], &im)))//是tag
	{
		int i;
		if ((i = find(buff[0])) != -1)//在tag中找到
		{
			ul poss = tags[i].pos;
			char p[20];
			p[0] = '0'; p[1] = 'x';
			sprintf(p + 2, "%llx", poss / 2);
			write_imme((uc*)p);
		}
		else//在后面 存起来
		{
			ul save = pos;
			uc temp[16];
			memset(temp, 'x', 16 * sizeof(uc));
			writeByte2Bin(temp, 16);
			tab(buff[0], save);
		}
	}
	else
	{
		char p[20];
		p[0] = '0'; p[1] = 'x';
		sprintf(p + 2, "%llx", im);
		write_imme((uc*)p);
	}
}
void do_rmmovq()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "rmmovq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	writeByte2Bin(bytes, 2);
	uc temp = regIdByname(buff[0]);
	writeByte2Bin(&temp, 1);
	uc reg[20];
	ul num = 0;
	regop(buff[1], &num, reg);
	temp = regIdByname(reg);
	writeByte2Bin(&temp, 1);
	char p[20];
	p[0] = '0'; p[1] = 'x';
	sprintf(p + 2, "%llx", num);
	write_imme((uc*)p);
}
void do_mrmovq()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "mrmovq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	writeByte2Bin(bytes, 2);
	uc temp = regIdByname(buff[1]);//mrmov先写右边的寄存器
	writeByte2Bin(&temp, 1);
	uc reg[20];
	ul num = 0;
	regop(buff[0], &num, reg);
	temp = regIdByname(reg);
	writeByte2Bin(&temp, 1);
	char p[20];
	p[0] = '0'; p[1] = 'x';
	sprintf(p + 2, "%llx", num);
	write_imme((uc*)p);
}
void do_op(char* name)
{
	uc buff[2][20];
	GetNextWord(buff);
	uc* bytes = instrIdByname(name);
	writeByte2Bin(bytes, 2);
	uc temp = regIdByname(buff[0]);
	writeByte2Bin(&temp, 1);
	temp = regIdByname(buff[1]);
	writeByte2Bin(&temp, 1);
}
void do_addq()
{
	const char* cpc = "addq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_op(pc);
}
void do_subq()
{
	const char* cpc = "subq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_op(pc);
}
void do_andq()
{
	const char* cpc = "andq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_op(pc);
}
void do_xorq()
{
	const char* cpc = "xorq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_op(pc);
}
void do_jxx(char* name)
{
	uc buff[2][20];
	GetNextWord(buff);
	uc* temp = instrIdByname(name);
	writeByte2Bin(temp, 2);
	ul im = 0;
	if (!(isNumb(buff[0], &im)))//是tag
	{
		int i;
		if ((i = find(buff[0])) != -1)//在tag中找到
		{
			ul poss = tags[i].pos;
			char p[20];
			p[0] = '0'; p[1] = 'x';
			sprintf(p + 2, "%llx", poss / 2);
			write_imme((uc*)p);
		}
		else//在后面 存起来
		{
			ul save = pos;
			uc temp[16];
			memset(temp, 'x', 16 * sizeof(uc));
			writeByte2Bin(temp, 16);
			tab(buff[0], save);
		}
	}
	else
	{
		char p[20];
		p[0] = '0'; p[1] = 'x';
		sprintf(p + 2, "%llx", im);;
		write_imme((uc*)p);
	}
}
void do_jmp()
{
	const char* cpc = "jmp";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_jle()
{
	const char* cpc = "jle";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_jl()
{
	const char* cpc = "jl";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_je()
{
	const char* cpc = "je";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_jne()
{
	const char* cpc = "jne";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_jge()
{
	const char* cpc = "jge";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_jg()
{
	const char* cpc = "jg";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_jxx(pc);
}
void do_cmov(char* name)
{
	uc buff[2][20];
	GetNextWord(buff);
	uc* bytes = instrIdByname(name);
	//得到指令的id
	writeByte2Bin(bytes, 2);
	uc temp = regIdByname(buff[0]);
	writeByte2Bin(&temp, 1);
	temp = regIdByname(buff[1]);
	writeByte2Bin(&temp, 1);
}
void do_cmovle()
{
	const char* cpc = "cmovle";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_cmov(pc);
}
void do_cmovl()
{
	const char* cpc = "cmovl";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_cmov(pc);
}
void do_cmove()
{
	const char* cpc = "cmove";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_cmov(pc);
}
void do_cmovne()
{
	const char* cpc = "cmovne";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_cmov(pc);
}
void do_cmovge()
{
	const char* cpc = "cmovge";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_cmov(pc);
}
void do_cmovg()
{
	const char* cpc = "cmovg";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_cmov(pc);
}
void do_call()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "call";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	//得到指令的id
	writeByte2Bin(bytes, 2);
	ul im = 0;
	if (!(isNumb(buff[0], &im)))//是tag
	{
		int i;
		if ((i = find(buff[0])) != -1)//在tag中找到
		{
			ul poss = tags[i].pos;
			char p[20];
			p[0] = '0'; p[1] = 'x';
			sprintf(p + 2, "%llx", poss / 2);
			write_imme((uc*)p);
		}
		else//在后面 存起来
		{
			ul save = pos;
			uc temp[16];
			memset(temp, 'x', 16 * sizeof(uc));
			writeByte2Bin(temp, 16);
			tab(buff[0], save);
		}
	}
	else
	{
		char p[20];
		p[0] = '0'; p[1] = 'x';
		sprintf(p + 2, "%llx", im);;
		write_imme((uc*)p);
	}
}
void do_ret()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "ret";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	//得到指令的id
	writeByte2Bin(bytes, 2);

}
void do_pxx(char* name)
{
	uc buff[2][20];
	GetNextWord(buff);
	uc* bytes = instrIdByname(name);
	//得到指令的id
	writeByte2Bin(bytes, 2);
	//设置寄存器id
	uc temp = regIdByname(buff[0]);
	writeByte2Bin(&temp, 1);
}
void do_pushq()
{
	const char* cpc = "pushq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_pxx(pc);
}
void do_popq()
{
	const char* cpc = "popq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	do_pxx(pc);
}
void do_iaddq()
{
	uc buff[2][20];
	GetNextWord(buff);
	const char* cpc = "iaddq";
	char* pc = new char[100];
	strcpy(pc, cpc);
	uc* bytes = instrIdByname(pc);
	writeByte2Bin(bytes, 2);
	uc temp = 'f';
	writeByte2Bin(&temp, 1);
	temp = regIdByname(buff[1]);
	writeByte2Bin(&temp, 1);
	ul im = 0;
	if (!(isImme(buff[0], &im)))//是tag
	{
		int i;
		if ((i = find(buff[0])) != -1)//在tag中找到
		{
			ul poss = tags[i].pos;
			char p[20];
			p[0] = '0'; p[1] = 'x';
			sprintf(p + 2, "%llx", poss / 2);
			write_imme((uc*)p);
		}
		else//在后面 存起来
		{
			ul save = pos;
			uc temp[16];
			memset(temp, 'x', 16 * sizeof(uc));
			writeByte2Bin(temp, 16);
			tab(buff[0], save);
		}
	}
	else
	{
		char p[20];
		p[0] = '0'; p[1] = 'x';
		sprintf(p + 2, "%llx", im);
		write_imme((uc*)p);
	}
}
void rewrite()
{
	for (int i = 0; i < cnt_mark; i++)
	{
		uc* name = (uc*)mark[i].name;

		pos = mark[i].pos;//需要被写入的地址
		ul id;
		if ((id = find(name)) != -1)
		{
			ul poss = tags[id].pos;//被写入的数据
			char p[20];
			p[0] = '0'; p[1] = 'x';
			sprintf(p + 2, "%llx", poss / 2);
			write_imme((uc*)p);
		}
	}
}
