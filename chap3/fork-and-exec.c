#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static void child() {
	char *args[] = {"/bin/echo", "hello"};
	printf("I'm a child! My pid is %d.", getpid());
	fflush(stdout);
	execve("/bin/echo", args, NULL);
	err(EXIT_FAILURE, "exec() faild");
}

static void parent(pid_t pid_c) {
	printf("I'm a parent! My pid is %d and the pid of my child is %d.", getpid(), pid_c);
	exit(EXIT_SUCCESS);
}

int main(void) {
	pid_t ret;
	ret = fork();
	
	if (ret == -1) {
		err(EXIT_FAILURE, "fork() faild");
	}

	if (ret == 0) {
		// child process come here because for() returns 0 for child process
		child();
	} else {
		// parent process came here because fork() returns the pid of newly created child process
		parent(ret);
	}

	//shouldn't reach here
	err(EXIT_FAILURE, "shouldn't reach here");
}
