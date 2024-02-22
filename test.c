#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int infile;
    int pid[3];

    pid[0] = fork();
    if (pid[0] == 0)
    {
        infile = open("infile", O_RDONLY);
        dup2(infile, STDIN_FILENO);
        close(infile);
        execlp("cat", "cat", NULL);
    }
    wait(NULL);
    close(infile);
    pid[1] = fork();
    if (pid[1] == 0)
    {
        dup2(STDIN_FILENO, STDOUT_FILENO);
        execlp("rev", "rev", NULL);
    }
    wait(NULL);
    pid[2] = fork();
    if (pid[2] == 0)
    {
        dup2(STDIN_FILENO, STDOUT_FILENO);
        execlp("rev", "rev", NULL);
    }
    wait(NULL);
    int outfile;

    outfile = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
    dup2(STDIN_FILENO, STDOUT_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    execlp("cat", "cat", NULL);
}