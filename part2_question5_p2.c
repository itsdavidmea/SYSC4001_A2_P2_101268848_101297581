#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdlib.h>

struct Shared {
    int multiple;
    int counter;
};

void P(int semid) {
    struct sembuf p = {0, -1, 0};
    semop(semid, &p, 1);
}
void V(int semid) {
    struct sembuf v = {0, +1, 0};
    semop(semid, &v, 1);
}

int main() {
    key_t key = ftok("shared", 65);

    int shmid = shmget(key, sizeof(struct Shared), 0666);
    int semid = semget(key, 1, 0666);
    struct Shared *s = (struct Shared *) shmat(shmid, NULL, 0);

    while (1) {
        P(semid); 
        if (s->counter > 500) {
            V(semid);
            break;
        }

        if (s->counter > 100 && s->counter % s->multiple == 0)
            printf("Child: %d is a multiple of %d\n", s->counter, s->multiple);

        V(semid); 
        sleep(1);
    }

    shmdt(s);
    return 0;
}
