/*
 * mem_eater.h
 *
 *  Created on: May 22, 2015
 *      Author: snehring
 */
#pragma once
#include <stdint.h>

typedef struct sysinfo sysinfo_t;
typedef struct mwrite_args
{
	uint8_t*  memory;
	uint8_t data;
	uint64_t  offset;
	uint64_t size;

} mwrite_args_t;

void mem_stuff(void* mem, uint8_t d);
void read_mem(void* mem, uint64_t size);
void* thread_memwrite(void* arg);
