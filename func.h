#define MAX_ROUTER 10
#define MAX_LINE 300

#define BUFLEN 512

struct _router
{
	unsigned int id;
	unsigned int process;
	char *ip;
	unsigned int hop;
}typedef router;

void die(char *s)
{
    perror(s);
    exit(1);
}

void router_send ();
void router_receive ();

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

router local_router;
router routers [MAX_ROUTER];