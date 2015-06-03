/*
 * mem_eater.h
 *
 *  Created on: May 22, 2015
 *      Author: snehring
 */

#ifndef MEM_EATER_H_
#define MEM_EATER_H_



#endif /* MEM_EATER_H_ */

typedef struct sysinfo sysinfo_t;
typedef struct mwrite_args
{
	char* memory;
	char data;
	ulong offset;
	ulong size;

} mwrite_args_t;

void mem_stuff(void* mem, char d);
void read_mem(void* mem, ulong size);
void* thread_memwrite(void* arg);
