#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define MAX_L 300

struct _roteador
{
	unsigned int id;
	unsigned int process;
	char *ip;
}typedef roteador;

int main()
{
	FILE *arquivo = NULL;
	roteador r[MAX];
	int i;
	char *linha;
	char *token;
	
	arquivo = fopen("roteador.config","r");
	
	if (arquivo == NULL)
	{
		printf("Falha abertura do arquivo roteador.config");
		return 0;	
	} 

	linha = (char *) malloc(MAX_L * sizeof(char));
	
	fseek(arquivo, 0 , SEEK_SET);

	for ( i = 0; i < MAX; i++)
	{
		if (feof(arquivo)) break;
		fgets(linha, MAX_L, arquivo);
		
		token = strtok(linha, " ");  
		if (atoi(token) < 1) break;
		
		r[i].id = atoi(token);
      	
      	token = strtok(NULL, " ");
      	r[i].process = atoi(token);

      	token = strtok(NULL, " \n");
      	r[i].ip = token;
	}
	for (int j = 0; j < i; j++)
	{
		printf("%d\n", r[j].id);
		printf("%d\n", r[j].process);
		printf("%s\n", r[j].ip);
	}

	fclose(arquivo);
}
