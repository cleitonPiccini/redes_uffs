#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <pthread.h>
#include <sys/time.h>
#include "func.c"

int main(int argc, char const *argv[])
{
	int *j = malloc(sizeof(int));
    int i=0;
    *j = i;
    pthread_t threads[2];

	config_router("roteador.config", atoi(argv[1]));
	printf("id do roteador = %d\n", roteador.id);

	pthread_create(&threads[0], NULL, router_send, NULL);
	pthread_create(&threads[1], NULL, router_receive, NULL);
    
  	pthread_join(threads[1], NULL);
  	pthread_join(threads[0], NULL);
    
	return 0;
}