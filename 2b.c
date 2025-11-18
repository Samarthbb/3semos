#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 100
// structure for message queue
struct mesg_buffer {
 long mesg_type;
 char mesg_text[MAX];
};
int main() {
 key_t key;
 int msgid;
 struct mesg_buffer message;
 // generate unique key
 key = ftok("progfile", 65);
 if (key == -1) {
 perror("ftok failed");
 exit(1);
 }
 // create message queue
 msgid = msgget(key, 0666 | IPC_CREAT);
 if (msgid == -1) {
 perror("msgget failed");
 exit(1);
 }
 message.mesg_type = 1;
 printf("Write Data: ");
 if (fgets(message.mesg_text, MAX, stdin) == NULL) {
 perror("fgets failed");
 exit(1);
 }
 // remove newline character from input
 message.mesg_text[strcspn(message.mesg_text, "\n")] = '\0';
 // send message
 if (msgsnd(msgid, &message, sizeof(message.mesg_text), 0) == -1) {
 perror("msgsnd failed");
 exit(1);
 }
 printf("Data sent is: %s\n", message.mesg_text);
 return 0;
}


Reader Process (reader.c)
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
// structure for message queue
struct mesg_buffer {
 long mesg_type;
 char mesg_text[100];
};
int main() {
 key_t key;
 int msgid;
 struct mesg_buffer message;
 // Generate unique key
 key = ftok("progfile", 65);
 if (key == -1) {
 perror("ftok failed");
 exit(1);
 }
 // Access or create message queue
 msgid = msgget(key, 0666 | IPC_CREAT);
 if (msgid == -1) {
    perror("msgget failed");
 exit(1);
 }
 // Receive message of type 1
 if (msgrcv(msgid, &message, sizeof(message.mesg_text), 1, 0) == -1) {
 perror("msgrcv failed");
 exit(1);
 }
 // Print received message
 printf("Data Received is: %s\n", message.mesg_text);
 // Destroy the message queue
 if (msgctl(msgid, IPC_RMID, NULL) == -1) {
 perror("msgctl (IPC_RMID) failed");
 exit(1);
 }
 return 0;
}
