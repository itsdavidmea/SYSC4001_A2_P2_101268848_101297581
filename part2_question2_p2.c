#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(){

    int cycle_num = 0;
    while (1){
        cycle_num--;
        if (cycle_num % 3 == 0){
            printf("P2 number: %d is a multiple of 3\n", cycle_num);
        }
        else{
            printf("P2 number: %d\n", cycle_num);
        }
        sleep(1);
    }
    return 0;
}