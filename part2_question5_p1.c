#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
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

    int shmid = shmget(key, sizeof(struct Shared), 0666 | IPC_CREAT);
    struct Shared *s = (struct Shared *) shmat(shmid, NULL, 0);

    int semid = semget(key, 1, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 1);

    s->multiple = 3;
    s->counter = 0;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        execl("./part2_question5_p2", "P2", NULL);
        perror("Exec failed");

    } 
    else {
        while (1) {
            P(semid);
            if (s->counter > 500) {
                V(semid); 
                break;
            }
            if (s->counter % s->multiple == 0)
                printf("Parent: %d is a multiple of %d\n", s->counter, s->multiple);
            s->counter++;
            V(semid);

            sleep(1);
        }

        wait(NULL);
        shmdt(s);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
