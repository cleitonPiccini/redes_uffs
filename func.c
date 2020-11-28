#define MAX 10
#define MAX_L 300

#define BUFLEN 512  //Max length of buffer
//#define BUFLEN 512  //Max length of buffer
//#define PORT 8888   //The port on which to listen for incoming data
 
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

router config_router (char *nome_arquivo, int id)
{
	FILE *arquivo = NULL;
	router r;
	int i;
	char *linha;
	char *token;
	
	r.id = 0;
	r.process = 0;
	r.ip = "0.0.0.0";
		
	arquivo = fopen( nome_arquivo,"r");
	if (arquivo == NULL)
	{
		printf("Falha abertura do arquivo roteador.config");
		return r;	
	} 

	linha = (char *) malloc(MAX_L * sizeof(char));
	fseek(arquivo, 0 , SEEK_SET);

	for ( i = 0; i < MAX; i++)
	{
		if (feof(arquivo)) break;
		
		fgets(linha, MAX_L, arquivo);
		token = strtok(linha, " ");  
		
		if (atoi(token) < 1) break;
		
		if (atoi(token) == id)
		{
			r.id = atoi(token);
      		token = strtok(NULL, " ");
      		r.process = atoi(token);
      		token = strtok(NULL, " \n");
      		r.ip = token;
      		break;
		}
	}

	fclose(arquivo);
	return r;
}

router router_link (char *nome_arquivo, int id)
{
	FILE *arquivo = NULL;
	router r;
	int i;
	char *linha;
	char *token;
	
	r.id = 0;
	r.process = 0;
	r.ip = "0.0.0.0";
		
	arquivo = fopen( nome_arquivo,"r");
	if (arquivo == NULL)
	{
		printf("Falha abertura do arquivo roteador.config");
		return r;	
	} 

	linha = (char *) malloc(MAX_L * sizeof(char));
	fseek(arquivo, 0 , SEEK_SET);

	for ( i = 0; i < MAX; i++)
	{
		if (feof(arquivo)) break;
		
		fgets(linha, MAX_L, arquivo);
		token = strtok(linha, " ");  
		
		if (atoi(token) < 1) break;
		
		if (atoi(token) == id)
		{
			r.id = atoi(token);
      		token = strtok(NULL, " ");
      		r.process = atoi(token);
      		token = strtok(NULL, " \n");
      		r.ip = token;
      		break;
		}
	}

	fclose(arquivo);
	return r;
}


void router_server (router roteador)
{
	 
    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(roteador.process);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);
         
        //now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
    }
 
    close(s);
    //return 0;
}


void router_client (router roteador)
{

    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(roteador.process);
     
    if (inet_aton(roteador.ip , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 
    while(1)
    {
        //printf("Enter message : ");
        //gets(message);
        //scanf("%s",message);
        message[0] = 'o';
        message[1] = 'i';
        message[2] = ' ';
        message[3] = 'g';
        message[4] = 'e';
        message[5] = 'n';
        message[6] = 't';
        message[7] = 'e';
        //message[0] = "oi gente";
        //message[0] = "oi gente";
        sleep(4); 
        //send the message
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }
         
        puts(buf);
    }
 
    close(s);

}