#include "func.h"


//#define BUFLEN 512  //Max length of buffer
//#define PORT 8888   //The port on which to listen for incoming data
 

//
void config_router (int id)
{
	FILE *arquivo = NULL;
	//router r;
	int i;
	char *linha;
	char *token;
	
	router[id].id = id;
	
	arquivo = fopen( "roteador.config","r");
	if (arquivo == NULL)
	{
		printf("Falha abertura do arquivo roteador.config");
		return;	
	} 

	linha = (char *) malloc(MAX_LINE * sizeof(char));
	fseek(arquivo, 0 , SEEK_SET);

	for ( i = 0; i < MAX_ROUTER; i++)
	{
		if (feof(arquivo)) break;
		
		fgets(linha, MAX_LINE, arquivo);
		token = strtok(linha, " ");  
		
		if (atoi(token) < 1) break;
		
		if (atoi(token) == id)
		{
      		token = strtok(NULL, " ");
      		router[id].process = atoi(token);
      		token = strtok(NULL, " \n");
      		router[id].ip = token;
      		break;
		}
	}

	fclose(arquivo);
}

void router_link ()
{
    FILE *arquivo = NULL;
    
    int index_arquivo, index_vizinhos;
    char *linha;
    char *token;
    
    vizinhos[0].id = 0;
    vizinhos[0].process = 0;
    vizinhos[0].ip = "0.0.0.0";
    vizinhos[0].hop = 0;
        
    arquivo = fopen( "enlace.config","r");
    if (arquivo == NULL)
    {
        printf("Falha abertura do arquivo enlace.config");
        return; 
    } 

    linha = (char *) malloc(MAX_LINE * sizeof(char));
    fseek(arquivo, 0 , SEEK_SET);

    for ( index_arquivo = 0, index_vizinhos = 0; index_arquivo < MAX_ROUTER; index_arquivo++)
    {

        //if (fscanf(f, "%d %d %d", &router1, &router2, &cost) != EOF)

        if (feof(arquivo)) break;
        
        fgets(linha, MAX_LINE, arquivo);
        token = strtok(linha, " ");  
        
        if (atoi(token) < 1) break;
        
        if (atoi(token) == roteador.id)
        {
            
            token = strtok(NULL, " ");
            vizinhos[index_vizinhos].id = atoi(token);
            token = strtok(NULL, " \n");
            vizinhos[index_vizinhos].hop = atoi(token);
            config_router(index_vizinhos)
            index_vizinhos++;
        }
    }
    printf("oi eu sou o vizinho numero %d\n",vizinhos[0].id );
    


    fclose(arquivo);
}

void router_process 

void router_send ()
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
     printf("%d\n", &slen );
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
        //try to receive some data, this is a blocking call
        if (recv_len == -1)
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


void router_receive (void *id_thread)
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
        strcpy(message, "vetor distancia\n");
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

