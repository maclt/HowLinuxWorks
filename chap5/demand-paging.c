#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define BUFFER_SIZE (1024*1024*100)
#define NCYCLE 10
#define PAGE_SIZE 4096

int main(void){
	char *p;
	time_t t;
	char *s;

	// show the time
	t = time(NULL);
	s = ctime(&t);
	printf("%.*s:before allocation, please press Enter key\n", (int)(strlen(s)-1), s);
	getchar();

	// allocate the memory
	p = malloc(BUFFER_SIZE);
	if (p == NULL){
		err(EXIT_FAILURE, "malloc() failed");
	}

	// show the time after allocate the memory
	t = time(NULL);
	s = ctime(&t);
	printf("%.*s:allocated %dMB, please press Enter key\n", (int)(strlen(s)-1), s, BUFFER_SIZE / (1024*1024));
	getchar();

	// loop
	int i;
	for(i = 0; i < BUFFER_SIZE; i+= PAGE_SIZE) {
		p[i] = 0;
		int cycle = i / (BUFFER_SIZE / NCYCLE);
		if(cycle != 0 && i % (BUFFER_SIZE / NCYCLE) == 0){
			t = time(NULL);
			s = ctime(&t);
			printf("%.*s:touched %dMB\n", (int)(strlen(s)-1), s, i / (1024 * 1024));
			sleep(1);
		}
	}

	// end of the program
	t = time(NULL);
	s = ctime(&t);
	printf("%.*s:touched %dMB, please press Enter key\n", (int)(strlen(s)-1), s, BUFFER_SIZE / (1024 * 1024));
	getchar();

	exit(EXIT_SUCCESS);
}
