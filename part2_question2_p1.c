#include <sys/types.h>
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
        execl("./part2_question2_p2", "P2", NULL);
        perror("Exec failed");
    } 

    else{
        int cycle_num = 0;
        while (1){
            if (cycle_num % 3 == 0){
                printf("Cycle number: %d - %d is a multiple of 3\n", cycle_num, cycle_num);
            }
            else{
                printf("Cycle number: %d\n", cycle_num);
            }
            cycle_num++;
            sleep(1);
        }
    }
    return 0;
}