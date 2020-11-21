#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, const char **argv){
    int fork_id[10];
    int x;
    for(x=0; x<10; x++){
        fork_id[x] = fork();
        if(fork_id[x] == 0){
            //execl("/usr/bin/sleep", "5", NULL);
            //printf("10 sou o numero = %d\n", fork_id[x]);
            break;
        }
           printf("sou o numero = %d\n", fork_id[x]);
    }

    sleep(10);

    return 0;
}