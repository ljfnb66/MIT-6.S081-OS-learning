#include "kernel/types.h"
#include "user/user.h"

int main(char argc, char *argv[])
{
    int pid;
    int pipes1[2], pipes2[2];
    char buf[] = {'a'}; // one byte to be transferred
    pipe(pipes1);
    pipe(pipes2);

    int ret = fork();//

    // parent send in pipes1[1], child receives in pipes1[0]
    // child send in pipes2[1], parent receives in pipes2[0]
    // should have checked close &read &write reutrn value for error
    if (ret == 0)
    {
        // i am the child process
        pid = getpid();
        close(pipes1[1]);//close the write in pipes1
        close(pipes2[0]);//close the read in pipes2
        read(pipes1[0], buf, 1);//read one byte from pipes1[0] then write in buf
        printf("%d received ping\n", pid);
        write(pipes2[1], buf, 1);//write one byte in pipes2[1] from the buf byte
        exit(0);
    }
    else
    {
        // i am the parent process
        pid = getpid();
        close(pipes1[0]);
        close(pipes2[1]);
        write(pipes1[1], buf, 1);
        read(pipes2[0], buf, 1);
        printf("%d received pong\n", pid);
        exit(0);
    }
}