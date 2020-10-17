#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int i;
    int processNum;
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        if (pid == 0)
            break;
        printf("[parent %d] child pid: %d\n", getpid(), pid);
    }
    processNum = i;
    if (pid == -1)
    {
        fprintf(stderr, "failed\n");
    }
    else if (pid == 0)
    {
        // 子プロセス
        printf("[child %d] chid(%d)\n", getpid(), processNum);
        sleep(10);
    }
    else
    {
        // 親プロセス
        for (i = 0; i < processNum; i++)
        {
            pid = wait(NULL);
            printf("[parent %d]child(pid=%d) finished\n", getpid(), pid);
        }
    }
    return 0;
}
