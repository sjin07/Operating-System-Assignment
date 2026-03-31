#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"

int main(){
	int pid = getpid();

	int n = getnice(pid);
	printf("Current Getnice Value = %d\n", n);

	setnice(pid, 100);
	n = getnice(pid);
	printf("Current Getnice Value, revised = %d\n", n);
	
	printf("Test ps\n");
	ps(0);
	ps(pid);

	uint64 free_bytes = meminfo();
	printf("Free memory: %ld bytes\n", free_bytes);

	pid = fork();
	if (pid < 0){
		printf("fork failed\n");
		exit(1);
	}

	if (pid == 0){
		printf("Child existing\n");
		exit(0);
	} else{
		printf("Parent waiting for pid %d\n", pid);
		int res = waitpid(pid);
		if (res == 0){
			printf("waitpid success!\n");
		} else{
			printf("waitpid failed!\n");
		}

		if (waitpid(999) == -1){
			printf("Non-existent PID test passed\n");
		}
	}

	return 0;
}

