#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct shared_data
{
    int multiple;
    int counter;
} Shared;


int main(){

    key_t key = ftok("shared", 65);
    int shmid = shmget(key, sizeof(Shared), IPC_CREAT | 0666);

    struct shared_data *shared = (struct shared_data*) shmat(shmid, NULL, 0);
    shared->multiple = 3;
    shared->counter = 0;


    pid_t pid = fork();

    if (pid < 0){
        perror("Fork failed");
        return 1;
    }

    if (pid == 0){
        execl("./part2_question4_p2", "P2", NULL);
        perror("Exec failed");
    } 
    else{
        while (shared->counter <= 500) {
            if (shared->counter % shared->multiple == 0){
                printf("Parent: %d is a multiple of %d\n", shared->counter, shared->multiple);
            }
            shared->counter++;
        }
        wait(NULL);
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
    }    
    return 0;
}