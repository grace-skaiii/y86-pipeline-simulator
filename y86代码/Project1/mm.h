
#ifndef _MM_H
#define _MM_H
#include <stdio.h>
#include<stdlib.h>
#include<string>
#define MM_SIZE 0x200+5 
extern char mem[MM_SIZE];
typedef  long long ul;
typedef  unsigned char uc;

ul atoi64_t(uc *arrTmp);

int transform(char c);

int  read(ul addr, uc *val, ul n);

int  read_mem(ul addr, uc * val, ul n);

int  write_mem(ul addr,ul num, int n);

int  write(int set, int line);

int read8Bytes(ul addr, ul*val);

ul addr(char *begin);

uc ctoc(char *begin);

//char* load_file(char* file_name);

void do_Line();

void load_yo(char *file_name);

void load_ys(char* file_name);

ul print_mem(int num);

uc* long2charArr(ul  num);

#endif


