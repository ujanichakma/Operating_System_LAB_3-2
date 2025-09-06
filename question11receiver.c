#define KEY 1234
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    int msgid = msgget(KEY, 0666);
    struct msg_buffer msg;

    msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
    printf("Received message: %s\n", msg.msg_text);

    msgctl(msgid, IPC_RMID, NULL); // remove queue
    return 0;
}

