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
	router roteador;
	router vizinho;
	vizinho.id = 2;
	vizinho.process = 25000;
	vizinho.ip = "127.0.0.1";

	roteador = config_router("roteador.config", atoi(argv[1]));
	printf("id do roteador = %d\n", roteador.id);

	if (roteador.id == 1) router_server (roteador);

	if (roteador.id == 2) router_client (vizinho);

	return 0;
}