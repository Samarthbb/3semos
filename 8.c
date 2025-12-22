// client.c
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
int main() {
    int soc = socket(PF_INET, SOCK_STREAM, 0);
 if (soc < 0) return 1; 
 struct sockaddr_in addr = {
 .sin_family = AF_INET,
 .sin_port = htons(7891),
 .sin_addr.s_addr = inet_addr("127.0.0.1")
 };
 if (connect(soc, (struct sockaddr *) &addr, sizeof(addr)) == 0) {
 printf("Connected to server\nEnter file name: ");
 char fname[50], buffer[1024];
 scanf("%s", fname);
send(soc, fname, sizeof(fname), 0);
 printf("Response:\n");
while (recv(soc, buffer, sizeof(buffer), 0) > 0)
 printf("%s", buffer);
 } else {
 perror("Connection failed");
 }
close(soc);
 return 0;
}

//server.c
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
int welcome = socket(PF_INET, SOCK_STREAM, 0);
struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(7891),
.sin_addr.s_addr = inet_addr("127.0.0.1") };
 bind(welcome, (struct sockaddr*)&addr, sizeof(addr));
 printf("Server is online, waiting for connections...\n");
 listen(welcome, 5);
nt new_soc = accept(welcome, NULL, NULL);
 char fname[50], buffer
 recv(new_soc, fname, sizeof(fname), 0);
 printf("Request received for file: %s\n", fname);
int fd = open(fname, O_RDONLY);
 if (fd < 0) {
 send(new_soc, "File not found\n", 15, 0);
 printf("File not found, notified client.\n");
 } else {
 printf("File found, sending contents to client...\n");
 int n;
 while ((n = read(fd, buffer, sizeof(buffer))) > 0)
 send(new_soc, buffer, n, 0);
 }
 close(fd);
 close(new_soc);
 close(welcome);
 printf("Request completed.\n");
 return 0;
}