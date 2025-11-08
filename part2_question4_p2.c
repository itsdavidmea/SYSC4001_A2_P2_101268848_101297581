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
    int shmid = shmget(key, sizeof(Shared), 0666);
    struct shared_data *shared = (struct shared_data*) shmat(shmid, NULL, 0);

   while (shared->counter <= 100)
        sleep(1);

    while (shared->counter <= 500) {
        if (shared->counter % shared->multiple == 0)
            printf("P2: %d is a multiple of %d\n", shared->counter, shared->multiple);
        sleep(1);
    }
    shmdt(shared);
    return 0;
}