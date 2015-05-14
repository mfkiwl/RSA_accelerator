#include <stdio.h>     
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

#define MAXPENDING 5    /* max outstanding connection requests */
#define RCVBUFSIZE 32   /* size of receive buffer */
#define SNDBUFSIZE 32

/* error handling */
void err_sys(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

void handle_client(int clntSocket);   

int main(int argc, char *argv[])
{
    int servSock;                    
    int clntSock;                    
    struct sockaddr_in servAddr;    
    struct sockaddr_in clntAddr;    
    unsigned short servPort;  

    unsigned int clntLen;            

    if (argc != 2) {
        fprintf(stderr, "usage:  %s <server port>\n", argv[0]);
        exit(1);
    }

    servPort = atoi(argv[1]);  /* first arg:  local port */

    /* server SOCKET */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        err_sys("socket() failed");
      
    /* construct local address structure */
    memset(&servAddr, 0, sizeof(servAddr));   
    servAddr.sin_family = AF_INET;                
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servAddr.sin_port = htons(servPort);      

    /* BIND */
    if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        err_sys("bind() failed");

    /* LISTEN */
    if (listen(servSock, MAXPENDING) < 0)
        err_sys("listen() failed");

    for (;;) {
        /* set the size of the in-out parameter */
        clntLen = sizeof(clntAddr);

        /* wait (ACCEPT) */
        if ((clntSock = accept(servSock, (struct sockaddr *) &clntAddr, 
                               &clntLen)) < 0)
            err_sys("accept() failed");

        /* clntSock is connected to a client! */
        printf("handling client %s\n", inet_ntoa(clntAddr.sin_addr));

        handle_client(clntSock);
    }
    /* ... not reached */
}

void handle_client(int clntSocket)
{
    char msgBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */

    /* RECEIVE */
    if ((recvMsgSize = recv(clntSocket, msgBuffer, RCVBUFSIZE, 0)) < 0)
        err_sys("recv() failed");

    while (recvMsgSize > 0)      /* 0 = end of transmission */
    {
        /* print RECVd message */
        printf("[CLIENT message]: %s\n", msgBuffer);

        /* query user for message */
        char msgReply[SNDBUFSIZE];
        scanf("%31s", msgReply);
        int sizeReply = strlen(msgReply);

        /* SEND message back */
        if (send(clntSocket, msgReply, sizeReply, 0) != sizeReply)
            err_sys("send() failed");

        /* more data to RECEIVE? */
        if ((recvMsgSize = recv(clntSocket, msgBuffer, RCVBUFSIZE, 0)) < 0)
            err_sys("recv() failed");
    }

    close(clntSocket);    /* Close client socket */
}