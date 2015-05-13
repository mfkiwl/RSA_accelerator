#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>    
#include <unistd.h>    

#define RCVBUFSIZE 32   /* size of receive buffer */

/* error handling */
void err_sys(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock;                           /* socket descriptor */
    struct sockaddr_in servAddr;        /* server address */
    unsigned short servPort;            /* server port */
    char *servIP;                       /* server IP address (dotted quad) */
    
    char *msgString;                    /* msg string to send to server */
    char msgBuffer[RCVBUFSIZE];         /* buffer for msg string */
    unsigned int msgStringLen;      
    
    int bytesRcvd, totalBytesRcvd;      /* bytes read in single recv() and total bytes read */

    if ((argc < 3) || (argc > 4))       /* test for correct number of arguments */
    {
       fprintf(stderr, "usage: %s <server IP> <word> [<port>]\n",
               argv[0]);
       exit(1);
    }

    servIP = argv[1];               /* first arg: server IP address (dotted quad) */
    msgString = argv[2];            /* second arg: string to echo */

    if (argc == 4)
        servPort = atoi(argv[3]);   /* use given port, if any */
    else
        servPort = 7;               /* default */

    /* SOCKET */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        err_sys("socket() failed");

    /* construct the server address structure */
    memset(&servAddr, 0, sizeof(servAddr));     
    servAddr.sin_family      = AF_INET;             
    servAddr.sin_addr.s_addr = inet_addr(servIP);   
    servAddr.sin_port        = htons(servPort); 

    /* CONNECT */
    if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        err_sys("connect() failed");

    msgStringLen = strlen(msgString);          /* Determine input length */

    /* SEND */
    if (send(sock, msgString, msgStringLen, 0) != msgStringLen)
        err_sys("send() sent a different number of bytes than expected");

    /* RECEIVE */
    totalBytesRcvd = 0;
    printf("received: ");                /* Setup to print the echoed string */
    while (totalBytesRcvd < msgStringLen)
    {
        /* RECEIVE */
        if ((bytesRcvd = recv(sock, msgBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            err_sys("recv() failed or connection closed prematurely");
        totalBytesRcvd += bytesRcvd;   /* total bytes */
        msgBuffer[bytesRcvd] = '\0';  
        printf("%s", msgBuffer);      /* print buffer */
    }

    printf("\n");   

    close(sock);
    exit(0);
}