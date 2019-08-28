#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define BUFFER_SIZE 1000
#define ALLOC_SIZE (100*1024*1024)

static char command[BUFFER_SIZE];

int main(void) {
	pid_t pid;

	// show /proc/{pid}/maps
	pid = getpid();
	snprintf(command, BUFFER_SIZE, "cat /proc/%d/maps", pid);

	puts("*** memory map before memory allocation ***");
	fflush(stdout);
	system(command); // execute "cat /proc/{pid}/maps"

	// get memory
	void *new_memory;
	new_memory = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(new_memory == (void *) -1) {
		err(EXIT_FAILURE, "mmap() faild");
	}

	// show /proc/{pid}/maps again
	puts("");
	printf("*** suceeded to allocate memory: address = %p; size = 0x%x ***\n", new_memory, ALLOC_SIZE);
	puts("");
	puts("*** memory map after memory allocation ***");
	fflush(stdout);
	system(command);

	if(munmap(new_memory, ALLOC_SIZE) == -1) {
		err(EXIT_FAILURE, "munmap() faild");
	}
	exit(EXIT_SUCCESS);
}
