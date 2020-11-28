#include <stdio.h>

int main(int argc, char const *argv[])
{

	
	if (argc != 2) {
		printf("Atenção! Executar usando ./t2 id=ID_ROUTER.\n\n");
		exit(-1);
	}
	//LOCAL_ROUTER = atoi(argv[1]);

	/* code */
	printf("%s\n",argv[1] );
	return 0;
}