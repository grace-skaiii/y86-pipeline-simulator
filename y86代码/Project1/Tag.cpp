#include "Tag.h"
#include <string>
#include<iostream>
using namespace std;
struct tag tags[100];
struct tag mark[100];
int cnt_tag = 0, cnt_mark = 0;
ul getAddr(char * name)
{
	int i;
	for (i = 0; i < cnt_tag; i++)
	{
		if (strcmp(tags[i].name, name) == 0)
			return tags[i].pos;
	}
	return 0;
}

void add(uc * name, ul pos)
{
	strcpy(tags[cnt_tag].name, (char*)name);
	tags[cnt_tag++].pos = pos;
}
int find(uc * name)
{
	int i;
	for (i = 0; i < cnt_tag; i++)
		if (strcmp((char*)name, tags[i].name) == 0)
			return i;
	return -1;
}
void tab(uc *name, ul pos)
{
	strcpy(mark[cnt_mark].name, (char*)name);
	mark[cnt_mark++].pos = pos;
}

