#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) {
 int numbytes;
 int fd[2];
 pid_t pid;
 char line[1024];
 if (pipe(fd) < 0) {
 perror("pipe error");
 exit(1);
 }
 if ((pid = fork()) < 0) {
 perror("fork error");
 exit(1);
 } else if (pid > 0) { // Parent
 close(fd[0]); // Close read end
 write(fd[1], "howdy\n", 6);
 close(fd[1]); // Close write end after writing
 } else { // Child
 close(fd[1]); // Close write end
 numbytes = read(fd[0], line, sizeof(line));
 if (numbytes > 0) {
 write(STDOUT_FILENO, line, numbytes);
 }
 close(fd[0]); // Close read end
 }
 return 0;
}