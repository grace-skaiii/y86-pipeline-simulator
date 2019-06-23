#pragma once
#ifndef VCACHE_H
#define VCACHE_H
typedef long long ul;
typedef unsigned char uc;
extern int s,E,b,replace;
struct Line
{
	int valid;
	int tag;
	int byte_num;
	uc* bytes;
	int times;
	int time;
};
struct Set
{
	Line *lines;
};
struct Cache
{
	int set_num;
	int line_num;
	Set *sets;
};
extern Cache *cache;
void initCache();
uc judge(ul addr, int choice, uc word);
int getSet(ul addr);
int getTag(ul addr);
int getByte(ul addr);
void updateTimes(Cache *cache, int set, int line);

#endif