struct _router
{
	unsigned int id;
	unsigned int process;
	char *ip;
}typedef router;

void die(char *s)
{
    perror(s);
    exit(1);
}

void router_send ();
void router_receive ();

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;


router roteador;

