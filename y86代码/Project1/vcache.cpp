#include"Vcache.h"
#include"mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int replace = 0;//Ĭ�� LRU
int s = 4;
int E = 4;
int b = 3;
Cache* cache=new Cache();
void initCache()
{
	int i=0, j;
	cache->set_num = (1 << s);
	cache->line_num = E;
	cache->sets =new Set[cache->set_num* sizeof(Set)];
	while(i<cache->set_num)
	{
		cache->sets[i].lines = new Line[cache->line_num * sizeof(Line)];
		j = 0;
		while (j < cache->line_num)
		{
			cache->sets[i].lines[j].valid = 0;
			cache->sets[i].lines[j].byte_num = (1 << b);
			cache->sets[i].lines[j].bytes = new uc[(1 << b) * sizeof(uc)];
			j++;
		}
		i++;
	}
}

uc judge(ul addr,int choice,uc word)//choiceΪ1�������choiceΪ0����д
{
	int i = 0;
	uc byte;
	int set = getSet(addr);
	int tag = getTag(addr);
	int index = getByte(addr);
	unsigned long long mask = ~((1 << b) - 1);
	ul temp = mask & addr;
	while(i < cache->line_num)
	{
		if (cache->sets[set].lines[i].valid && cache->sets[set].lines[i].tag==tag)
		{
			//hit
			if (choice)
			{
				byte = cache->sets[set].lines[i].bytes[index];
				updateTimes(cache, set, i);
				return byte;
			}
			else
			{
				cache->sets[set].lines[i].bytes[index] = word;
				return '0';
			}
		}
		i++;
	}
	//not hit
	i = 0;
	while(i < cache->line_num)
	{
		if (!cache->sets[set].lines[i].valid)
		{
			cache->sets[set].lines[i].valid = 1;
			cache->sets[set].lines[i].tag = tag;
			read(temp, cache->sets[set].lines[i].bytes, cache->sets[set].lines[i].byte_num);
			if (choice)
			{
				byte = cache->sets[set].lines[i].bytes[index];
				updateTimes(cache, set, i);
				return byte;
			}
			else
			{
				cache->sets[set].lines[i].bytes[index] = word;
				return '0';
			}
		}
		i++;
	}
	//replace ���滻������Ҫд���ڴ�
	i = 0;
	if(replace)////�滻����ΪLFU,�滻��ʹ�ô������ٵ�һ��
	{
		while (i < cache->line_num)
		{
			if (cache->sets[set].lines[i].times == 1)
			{
				write(set,i);//��д�����޸�
				cache->sets[set].lines[i].valid = 1;
				cache->sets[set].lines[i].tag = tag;
				read(temp, cache->sets[set].lines[i].bytes, cache->sets[set].lines[i].byte_num);
				if (choice)
				{
					byte = cache->sets[set].lines[i].bytes[index];
					updateTimes(cache, set, i);
					return byte;
				}
				else
				{
					cache->sets[set].lines[i].bytes[index] = word;
					return '0';
				}
			}
			i++;
		}
	}
	else//�滻����ΪLRU,�滻�����δ���ʵ�һ��
	{
		int temp = cache->sets[set].lines[0].time;
		int line = 0;
		i = 1;
		while (i < cache->line_num)
		{
			if (cache->sets[set].lines[i].time>temp)
			{
				temp = cache->sets[set].lines[i].time;
				line = i;
			}
			i++;
		}
		write(set, line);
		cache->sets[set].lines[line].valid = 1;
		cache->sets[set].lines[line].tag = tag;
		read(temp, cache->sets[set].lines[line].bytes, cache->sets[set].lines[line].byte_num);
		if (choice)
		{
			byte = cache->sets[set].lines[i].bytes[index];
			updateTimes(cache, set, i);
			return byte;
		}
		else
		{
			cache->sets[set].lines[i].bytes[index] = word;
			return '0';
		}
	}
}
int getSet(ul addr)
{
	unsigned long long mask = (~(1 << 63)) >> (63 - s);
	unsigned long long t = addr;
	t = (t << (64 - b - s)) >> (64 - s);
	addr = t;
	return (mask & addr);
}
//get tag bits of the address
int getTag(ul addr)
{
	unsigned long long mask = (~(1 << 63)) >> (s+b-1);
	addr=addr >> (s+b);
	return (mask & addr);
}
int getByte(ul addr)
{
	unsigned long long mask = (1 << b) - 1;
	return mask & addr;
}
void updateTimes(Cache *cache, int set, int line)
{
	int i=0;
	while (i < cache->line_num)
	{
		if (cache->sets[set].lines[i].valid && cache->sets[set].lines[i].times > cache->sets[set].lines[line].times)
			cache->sets[set].lines[i].times--;//����Ч��timesֵ���ڱ������е�������timesֵ-1�������滻ʱѡ��times=1���У�LFU��
		if (cache->sets[set].lines[i].valid &&i != line)//�Ѳ��Ǳ������е�������Ч�е�time��+1�������滻ʱѰ�����δʹ�õģ�LRU��
			cache->sets[set].lines[i].time++;
		i++;
	}
	cache->sets[set].lines[line].times= cache->line_num;//���滻�е�times��time����
	cache->sets[set].lines[line].time = 0;
}