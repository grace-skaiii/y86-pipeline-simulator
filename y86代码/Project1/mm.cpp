
#include "mm.h"
#include"ReadAssemCode.h"
#include"Tag.h"
#include"WriteBin.h"
#include"Vcache.h"
char* p;
char mem[MM_SIZE];
ul mem_pos = 0;
//cpu从cache中读
int  read_mem(ul addr, uc * val, ul n)//n是字节数，从内存中读取
{
	while (n--)
	{
		if (addr < 0 || addr > MM_SIZE)//越界 
			return -1;
		*val = judge(addr,1,'0');
		val++;
	}
	//val -= bit;
	return 0;
}
//cache从主存中读
int  read(ul addr, uc * val, ul n)//n是字节数，从内存中读取
{
	while (n--)
	{
		if (addr < 0 || addr > MM_SIZE)//越界 
			return -1;
		*val = mem[addr];
		addr++;
		val++;
	}
	return 0;
}
ul atoi64_t(uc *arrTmp)
{
	ul nTmpRes = 0;
	for (int i = 0; i <= 7; i++)
	{
		nTmpRes = nTmpRes * 256 + arrTmp[i];
	}
	return nTmpRes;
}
int read8Bytes(ul addr, ul *val)
{
	uc *bytes = (uc*)malloc(8 * sizeof(uc));
	int i = 7;//小端法！！！
	while (i >= 0)
	{
		if (read_mem(addr, &bytes[i], 1) < 0)
			return -1;
		i--;
		addr++;
	}
	ul result = atoi64_t(bytes);
	//printf("read 0x%llx from 0x%llx in memory\n", addr-8,result);
	*val = result;
	return 0;
}
uc* long2charArr(ul  num)
{
	uc* arr = (uc*)malloc(8 * sizeof(uc));
	int wei = 56;
	unsigned long long temp = num;
	for (int i = 7; i >= 0; i--)
	{
		unsigned long long t = temp << wei;//左移到56-64位，将比它高的位丢失
		arr[i] = (t >> 56) & 0xff;//右移到1-8位，将比它低的位丢失
		wei -= 8;
	}
	return arr;
}
//cpu往cache中写
int  write_mem(ul addr, ul num, int n)//往内存中写值 call rmmov push 
{//小端法
	uc*val = (uc*)malloc(8 * sizeof(uc));
	val = long2charArr(num);
	if (addr + n - 1 > MM_SIZE || addr < 0)
		return -1;
	addr += n - 1;
	while (n--)
	{
		judge(addr, 0, *(val++));
		//mem[addr] = *(val++);
		addr--;
	}
	return 0;
}
//cache往memory中写
int  write(int set,int line)//往内存中写值 call rmmov push 
{//小端法
	ul addr = line << (s + b) | set << b;
	int n = 1 << b;
	/*uc*val = (uc*)malloc(8 * sizeof(uc));
	val = long2charArr(num);*/
	if (addr + n - 1 > MM_SIZE || addr < 0)
		return -1;
	/*addr += n - 1;*/
	int i = 0;
	while (n--)
	{
		mem[addr] = cache->sets[set].lines[line].bytes[i++];
		//addr--;
		addr++;
	}
	return 0;
}
int transform(char c)
{
	if (c >= '0'&&c <= '9')
		return c - '0';
	else
		return 10 + c - 'a';
}
ul addr(char *begin)
{
	return transform(*begin) * 16 * 16 + transform(*(begin + 1)) * 16 + transform(*(begin + 2));
}
uc ctoc(char *begin)
{
	uc res = transform(*begin) * 16 + transform(*(begin + 1));
	return res;
}

void do_Line()
{
	char* pos = p;
	while (*(pos + 6) != '\0'&&*(pos + 6)!='\n')
	{
		if (*(pos) == '0'&&*(pos + 1) == 'x'&&*(pos + 5) == ':')//地址 
		{
			mem_pos = addr(pos + 2);
			pos += 7;
			while (*pos != '\0'&&*pos >= '0'&&*pos <= '9' || (*pos - 'a') >= 0 && (*pos - 'a') <= 5)
			{
				uc data = ctoc(pos);//把两位变一位存起来
				mem[mem_pos++] = data;
				pos += 2;
			}
		}
		pos++;
	}
}
void load_yo(char *file_name)
{
	mem_pos = 0;
	memset(mem, '0', MM_SIZE * sizeof(char));
	FILE* fp = fopen(file_name, "r");
	char line[1024];
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		p = line;
		do_Line();
	}
}
void load_ys(char *file_name)
{
	mem_pos = 0;
	memset(mem, '0', MM_SIZE * sizeof(char));
	FILE* fp = fopen(file_name, "r");
	char line[1024];
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (strlen(line) == 1) 
			continue;
		cur = (uc*)line;
		do_instrLine();
		//memset(line, '0', strlen(line) * sizeof(char));
	}
	ul pos = getPos();
	bin[pos] = '\0';
	rewrite();
	ul i = 0;
	char* p =(char*)bin;
	while (*(p+1) != '\0')
	{
		uc data = ctoc(p);//把两位变一位存起来
		mem[mem_pos++] = data;
		p += 2;
	}
}
ul print_mem(int num)
{
	return mem[num];
}



