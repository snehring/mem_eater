/*
 * mem_eater.c
 * A simple program to allocate and use all of the memory on a system
 *
 *  Created on: May 22, 2015
 *      Author: snehring
 */

#include <sys/sysinfo.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "mem_eater.h"

static uint64_t total_mem = 0;
static uint32_t total_procs;
static pthread_t* threads;


int main(int argc, char** argv)
{
	total_procs = sysconf(_SC_NPROCESSORS_ONLN);
	if((total_procs = total_procs/4)==0)
	{
		total_procs = 1;
	}
		
	threads = malloc(sizeof(pthread_t) * total_procs);
	sysinfo_t* info = malloc(sizeof(sysinfo_t));
	sysinfo(info);
	total_mem = (ulong) info->totalram;
	free(info);
	printf("This system has %lu bytes of memory.\n", total_mem);
	printf("We will now attempt to allocate ALL OF IT!!!!!!!!\n");
	void* mems = malloc(sizeof(uint8_t) * total_mem);
	if (mems)
	{
		printf(
				"We've successfully managed to allocate ALL OF THE MEMORY! Let's do stuff with it!\n");
		printf("Initializing the memory...\n");
		mem_stuff((uint8_t*) mems, 'f');
		printf("The memory should be initialized now.\n");
		printf("Pointlessly reading memory...\n");
		read_mem(mems, total_mem);
		printf("Sleeping for a bit to let things calm down.\n");
		sleep(1);
		printf("We're done here.\n");
	}
	else
	{
		fprintf(stderr, "Failed to allocate memory. We're done here.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void mem_stuff(void* mem, uint8_t d)
{
	uint64_t j = 0;
	uint64_t sub = total_mem / total_procs;
	uint32_t rem = total_mem % total_procs;

	for (uint64_t i = 0; i < total_procs; i++)
	{
		mwrite_args_t * arg = (mwrite_args_t*) malloc(sizeof(mwrite_args_t));
		arg->memory = mem;
		arg->data = d;
		arg->offset = j;
		arg->size = sub;
		if (i + 1 == total_procs && rem)
		{
			if (j + sub + rem <= total_mem)
				arg->size = sub + rem;
			else
				arg->size = rem;
		}
		/*
		 * Dispatch some threads
		 */
		pthread_create(&threads[i], NULL, thread_memwrite, arg);
		j = j + sub;
	}
	for (uint64_t i = 0; i < total_procs; i++)
	{
		pthread_join(threads[i], NULL);
	}

}
void* thread_memwrite(void* arg)
{
	for (uintptr_t i = 0; i < ((mwrite_args_t*) arg)->size; i++)
	{
		/**
		 * Copy data to memory location specified in arg size times
		 */
		*((((mwrite_args_t*) arg)->memory) + (((mwrite_args_t*) arg)->offset)
				+ i) = ((mwrite_args_t*) arg)->data;

	}
	pthread_exit(NULL);
}
void read_mem(void* mem, uint64_t size)
{
	uint64_t i;
	uint8_t fah;
	for (i = 0; i < size; i++)
	{
		fah = *(((uint8_t *) mem) + i);
	}
}

