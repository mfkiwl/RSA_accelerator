#include <stdio.h>     
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

#define MAXPENDING 5    /* max outstanding connection requests */
#define RCVBUFSIZE 256   /* size of receive buffer */
#define SNDBUFSIZE 256

/* error handling */
void err_sys(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

void handle_client(int clntSocket);   

int create_socket(struct sockaddr_in *servAddr, unsigned short *servPort) {
    int servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* construct local addr structure */
    memset(servAddr, 0, sizeof(*servAddr));   
    servAddr->sin_family = AF_INET;                
    servAddr->sin_addr.s_addr = htonl(INADDR_ANY); 
    servAddr->sin_port = htons(*servPort);  

    /* BIND & LISTEN*/
    bind(servSock, (struct sockaddr *) servAddr, sizeof(*servAddr));
    listen(servSock, MAXPENDING);

    return servSock;
}

int main(int argc, char *argv[])
{                                 
    struct sockaddr_in servAddr;    
    struct sockaddr_in clntAddr;    
    unsigned short servPort;  

    unsigned int clntLen;            

    if (argc != 2) {
        fprintf(stderr, "usage:  %s <server port>\n", argv[0]);
        exit(1);
    }

    servPort = atoi(argv[1]);  /* first arg: local port */
    clntLen = sizeof(clntAddr);

    int servSock = create_socket(&servAddr, &servPort);     

    for (;;) {

        /* ACCEPT */
        int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntLen);

        /* HANDLE CLIENT */
        printf("[handling client] %s\n", inet_ntoa(clntAddr.sin_addr));

        handle_client(clntSock);
    }
}

void handle_client(int clntSocket)
{
    char msgBuffer[RCVBUFSIZE]; char msgReply[SNDBUFSIZE];
    int recvMsgSize;                    

    recvMsgSize = recv(clntSocket, msgBuffer, RCVBUFSIZE, 0);

    while (recvMsgSize > 0)      /* 0 = end of transmission */
    {
        /* print RECVd message */
        printf("<client>: %s\n", msgBuffer);

        /* PROMPT for response */
        printf(">> "); scanf("%255s", msgReply); msgReply[SNDBUFSIZE - 1] = '\0';

        /* SEND message back */
        send(clntSocket, msgReply, strlen(msgReply), 0);

        /* RECEIVE */
        recvMsgSize = recv(clntSocket, msgBuffer, RCVBUFSIZE, 0);
    }

    close(clntSocket);    /* Close client socket */
}