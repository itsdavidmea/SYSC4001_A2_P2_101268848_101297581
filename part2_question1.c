#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main()
{
    pid_t pid;
    char *message;
    int n = 0;
    int count_child = 0;
    printf("fork program starting\n");
    pid = fork();

    while (1)
    {

        
        n++;
        message = "\nThis is the parent";
        printf("%s: %d", message, n);
        
       

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            sleep(1);
            message = "\nThis is the child";
            count_child++;
            printf("%s: %d", message, count_child);
            
        }

        sleep(4);
        //kill(pid, SIGTERM); 
        
    }

    exit(0);
}