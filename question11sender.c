#define KEY 1234
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    int msgid = msgget(KEY, 0666 | IPC_CREAT);
    struct msg_buffer msg = {1, "Hello from sender!"};

    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
    printf("Message sent.\n");

    return 0;
}

