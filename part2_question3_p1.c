#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(){

    pid_t pid = fork();

    if (pid < 0){
        perror("Fork failed");
        return 1;
    }

    if (pid == 0){
        execl("./part2_question3_p2", "P2", NULL);
        perror("Exec failed");
    } 

    int status = 0;
    waitpid(pid, &status, 0);
    printf("P2 lower than -500. Exiting\n");
    
    return 0;
}