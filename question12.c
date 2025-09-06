#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65); // unique key
    int msgid = msgget(key, 0666 | IPC_CREAT);
    pid_t pid = fork();

    if (pid == 0) {
        // Child receives
        struct msg_buffer msg;
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        printf("Child received: %s\n", msg.msg_text);
    } else {
        // Parent sends
        struct msg_buffer msg = {1, "Hello from parent!"};
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL); // remove message queue
    }

    return 0;
}

