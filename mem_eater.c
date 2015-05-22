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

static ulong total_mem = 0;
static long total_procs;
static pthread_t* threads;

void mem_stuff(void* mem, char d);
void read_mem(void* mem, ulong size);
void* thread_memwrite(void* arg);

int main(int argc, char** argv)
{
	total_procs = sysconf(_SC_NPROCESSORS_ONLN);
	total_procs = 2;
	threads = malloc(sizeof(pthread_t) * total_procs);
	sysinfo_t* info = malloc(sizeof(sysinfo_t));
	sysinfo(info);
	total_mem = (ulong) info->totalram;
	free(info);
	printf("This system has %lu bytes of memory.\n", total_mem);
	printf("We will now attempt to allocate ALL OF IT!!!!!!!!\n");
	void* mems = malloc(sizeof(char) * total_mem);
	if (mems)
	{
		printf(
				"We've successfully managed to allocate ALL OF THE MEMORY! Let's do stuff with it!\n");
		printf("Initializing the memory...\n");
		mem_stuff((char*) mems, 'f');
		printf("The memory should be initialized now.\n");
		printf("Pointlessly reading memory...\n");
		printf("Sleeping for a bit to let things calm down.\n");
		sleep(60);
	}
	else
	{
		fprintf(stderr, "Failed to allocate memory. We're done here.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void mem_stuff(void* mem, char d)
{
	ulong i;
	ulong j = 0;
	ulong sub = total_mem / total_procs;
	uint rem = total_mem % total_procs;

	for (i = 0; i < total_procs; i++)
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
	for (i = 0; i < total_procs; i++)
	{
		pthread_join(threads[i], NULL);
	}

}
void* thread_memwrite(void* arg)
{
	ulong i;
	for (i = 0; i < ((mwrite_args_t*) arg)->size; i++)
	{
		/**
		 * Copy data to memory location specified in arg size times
		 */
		*((((mwrite_args_t*) arg)->memory) + (((mwrite_args_t*) arg)->offset)
				+ i) = ((mwrite_args_t*) arg)->data;

	}
	pthread_exit(NULL);
}
void read_mem(void* mem, ulong size)
{
	ulong i;
	char fah;
	for (i = 0; i < size; i++)
	{
		fah = *(((char *) mem) + i);
	}
}

