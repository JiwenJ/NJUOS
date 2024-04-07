#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
// we do the fork and make the child process do system function,
//then the output of system() will go through pipe into the father's buffer which has already been prepared, atlast father process write the buffer into stdin.
int main()
{
    pid_t pid;
    char buf[1024];
    int fd[2]; //fd[0] read   fd[0]write
    if( pipe(fd) == -1)
        printf("pipe failed\n");//1 stdout 2 stderr 3 stdin 4 fd[0] 5 fd[1]
    pid = fork();
    if( pid > 0 )//father
    {
        //1 stdout 2 stderr 3 stdin 4 fd[0] 5 fd[1]
        close(fd[1]);
        read(fd[0],buf,1024);
        write(1,buf,1024);//write 1024bytes which are fetched from child process into stdin(terminal)
        wait(NULL);
        close(4);
        close(5);
   
    }
    else if( pid == 0)//child
    {
        int child_stdout = dup(1); // 1 stdout 2 stderr 3 stdin 4 fd[0] 5 fd[1] 6 stdout
        close(1);                   // 1 None 2 stderr 3 stdin 4 fd[0] 5 fd[1] 6 stdout
        int child_write_fd = dup(fd[1]);//1 fd[1] 2 stderr 3 stdin 4 fd[0] 5 fd[1] 6 stdout
        close(fd[0]);//1 fd[1] 2 stderr 3 stdin 4 None 5 fd[1] 6 stdout
        system("cat system.c");//1 fd[1] 2 stderr 3 stdin 4 None 5 fd[1] 6 stdout
        close(1);//1 None 2 stderr 3 stdin 4 None 5 fd[1] 6 stdout
        int resume_stdout = dup(child_stdout); //1 stdout 2 stderr 3 stdin 4 None 5 fd[1] 6 stdout
        close(5);
        close(6);
        sleep(2);//wait the father do write, wait 2 seconds
        printf("all are resumed \n");
        exit(1);
    }
    return 0;
}