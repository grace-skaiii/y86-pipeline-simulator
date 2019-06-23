#include"ReadAssemCode.h"
#include"Tag.h"
#include"WriteBin.h"
#include<string>
#include<iostream>
using namespace std;
uc *cur;
uc* getCur()
{
	return cur;
}
uc move2NoBlank()
{
	while (*cur == ' ' || *cur == '\t' || *cur == '\n')
		cur++;
	return *cur;
}
void getNextInstr(char *save)
{
	while (*cur != '\0'&&*cur != ' ' &&*cur != '\t' &&*cur != '\n')
	{
		*save++ = *cur++;
	}
	*save = '\0';
}
void GetNextWord(uc buff[][20])
{
	int flag = 0;
	int alp = 0;
	int cnt = 0;
	while (*cur != '\0' && *cur != '\n')
	{
		if (*cur == '#' || *cur == '/')//注释行
			break;
		//遇到逗号了
		if (*cur == ',')
		{
			if (flag == 1)
			{
				flag = 0;
				buff[cnt++][alp] = '\0';
				alp = 0;
			}
		}
		else if (*cur == ' ' || *cur == '\t' || *cur == '\n')
		{
			if (flag == 1)
			{
				flag = 0;
				buff[cnt++][alp] = '\0';
				alp = 0;
			}
		}
		else
		{
			if (flag == 0)
				flag = 1;
			buff[cnt][alp++] = *cur;
		}
		cur++;
	}
	if (flag == 1)
	{
		flag = 0;
		buff[cnt][alp] = '\0';
	}
}
int isNumb(uc *c, ul *val)
{
	if (c == NULL)
		return 0;
	int is16 = 0;
	uc * cc = c;
	//0x开头或者0X开头 是16进制
	if (cc[0] == '0' && (cc[1] == 'x' || cc[1] == 'X'))
	{
		is16 = 1;
		cc += 2;
	}
	if (*cc == '-')
		cc++;
	while (*cc != '\0')
	{
		if (is16)
		{
			if (!(*cc >= '0' && *cc <= '9') && !(*cc >= 'a' && *cc <= 'f') && !(*cc >= 'A'&&*cc <= 'F'))
				return 0;
		}
		else
		{
			if (!(*cc >= '0' && *cc <= '9'))
				return 0;
		}
		cc++;
	}
	if (is16)
	{
		sscanf((char*)c, "%llx", val);
		return 1;
	}
	else
	{
		sscanf((char*)c, "%lld", val);
		return 1;
	}
}
int isImme(uc *c, ul *val)
{
	if (*c != '$')
		return 0;
	return isNumb(c + 1, val);
}

void regop(uc* c, ul *val, uc* regname)
{
	int i;
	uc *regstart = NULL, *regend = NULL, *temp = c;
	for (i = 0; temp[i] != ')'; i++)
	{
		if (temp[i] == '(')
		{
			temp[i] = '\0';
			regstart = temp + i + 1;
		}
	}
	regend = temp + i;
	int len = regend - regstart;
	while (len--)
		*regname++ = *regstart++;
	*regname = '\0';
	if (c[0] == '(')
		*val = 0;
	else
		isNumb(temp, val);
}
void do_tag(uc *instr)
{
	int len = strlen((char*)instr);
	instr[len - 1] = '\0';    //去掉":"
	ul save = getPos();
	add(instr, save);
	if (move2NoBlank() != '\0')
	{
		do_instrLine();
	}
}

void do_instr(char *instr)
{
	//cout << "instr!" << endl;
	instr_handl handl = instrHandleByname(instr);
	handl();
}
void do_instrLine()
{
	char instr[200];
	uc c = move2NoBlank();
	if (c == '#' || c == '/' || c == '\0' || c == '\n') return;
	getNextInstr(instr);
	int len = strlen(instr);
	move2NoBlank();
	if (instr[len - 1] == ':')
		do_tag((uc*)instr);
	else
		do_instr(instr);
}
