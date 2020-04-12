#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t trace_cmd_pid, traced_prog_pid;
	char traced_pid_str[10];

	if (argc < 2) {
		printf("Usage: %s [COMMAND TO TRACE]\n", argv[0]);
		exit(1);
	}

	traced_prog_pid = fork();
	if (traced_prog_pid) { // Parent
		sprintf(traced_pid_str, "%d", traced_prog_pid);
		trace_cmd_pid = fork();
		if (trace_cmd_pid) { // Parent
			sleep(3); // Wait until trace-cmd is initilized
			
			kill(traced_prog_pid, SIGCONT); // Continue the traced process
			waitpid(traced_prog_pid, NULL, 0); // Wait for it to finish
			kill(trace_cmd_pid, SIGINT); // Send interupt to trace-cmd to finish its execution
			wait(NULL);
		} else { // Child
			// Start ftrace tracing of the first child-process
			char *trace_cmd_args[] = {"trace-cmd", "record", "-p", "function_graph", "-P", traced_pid_str, NULL}; 
			execvp("trace-cmd", trace_cmd_args);
			perror("Executing trace-cmd failed");
		}
	} else { // Child
		raise(SIGSTOP); // Suspend the process and wait for SIGCONT to start running
		execvp(argv[1], (char * const*)&(argv[1]));
		perror("Executing program failed");
	}

	return 0;
}