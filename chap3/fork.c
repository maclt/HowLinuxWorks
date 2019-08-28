#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static void child() {
	printf("I'm a child! My pid is %d.", getpid());
	exit(EXIT_SUCCESS);
}

static void parent(pid_t pid_c) {
	printf("I'm a parent! My pid is %d and the pid pf my child is %d.", getpid(), pid_c);
	exit(EXIT_SUCCESS);
}

int main(void) {
	pid_t ret;
	ret = fork();
	
	if (ret == -1) {
		err(EXIT_FAILURE, "fork() failed");
	}
	
	if (ret == 0) {
		// child process come here because fork() returns 0 for child process
		child();
	} else {
		// parent process come here because fork() returns the pid of newly created childe process
		parent(ret);
	}

	//shouldn't reach here
	err(EXIT_FAILURE, "shouldn't reach here");
}
