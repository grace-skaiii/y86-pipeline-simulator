#pragma once
#ifndef _TAG_H
#define _TAG_H
#define MAX_SYMBOL_NAME 128
#define MAX_SYMBOL_NUM 1024
typedef long long ul;
typedef unsigned char uc;
struct tag
{
	char name[20];
	ul pos;
};
extern struct tag tags[100];
extern struct tag mark[100];
extern int cnt_tag, cnt_mark;
ul getAddr(char * name);
void add(uc * name, ul addr);
int find(uc * name);
void tab(uc *name, ul pos);
#endif