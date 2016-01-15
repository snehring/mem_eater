/*
 * mem_eater.h
 *
 *  Created on: May 22, 2015
 *      Author: snehring
 */
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct sysinfo sysinfo_t;
/*struct that represents the arugments that will be passed to the thread_memwrite function*/
typedef struct mwrite_args
{
	/* ptr to allocated memory we will write to */
	uint8_t*  memory;
	/* ptr to data to write */
	uint8_t* data;
	/*at which offset in memory to start writing */
	uint64_t  offset;
	/* how much to write*/
	uint64_t size;

} mwrite_args_t;

void mem_stuff(void* mem, uint8_t* d);
void read_mem(void* mem, uint64_t size);
void* thread_memwrite(void* arg);
bool validate_input(int argc, char** argv);
