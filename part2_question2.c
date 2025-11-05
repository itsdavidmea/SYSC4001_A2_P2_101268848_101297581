// #include <sys/types.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>

// int main()
// {
//     pid_t pid;
//     char *message;
//     int n = 0;
//     int count_child = 0;
//     printf("fork program starting\n");
//     pid = fork();

//     while (1)
//     {

        
        
        
        

//         if (pid < 0)
//         {
//             perror("fork failed");
//             exit(1);
//         }

//         if (pid == 0)
//         {
//             sleep(1);
            
            
//             printf("\nThis is child: %d", n);
//             n++;
            
//         } else if (pid>0) {
            
//             printf("\nThis is parent: %d", n);
//             n++;
//         }

        
//         sleep(4);
        
       
       
        
//         //kill(pid, SIGTERM); 
        
//     }

    
// }