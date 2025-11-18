#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
int main()
{
pid_t pid;
int status;
// Fork a child process
pid = fork();
if (pid < 0)
{
// Error occurred
fprintf(stderr, "Fork Failed\n");
return 1;
}
else if (pid == 0)
{
// Child process
printf("This is the child process with pid = %d\n", getpid());
// Execute /bin/ls
execl("/bin/ls", "ls", NULL);
perror("execl failed");
exit(1);
}
else
{
// Wait for the child to complete
printf("Parent process, PID = %u\n", getpid());
waitpid(pid, &status, 0);
printf("Child completed with pid = %d\n", pid);
}
return 0;
}
