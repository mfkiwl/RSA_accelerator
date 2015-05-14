#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>    
#include <unistd.h>    

#define RCVBUFSIZE 256   /* size of receive buffer */

/* error handling */
void err_sys(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

int create_socket(char *servIP, unsigned short servPort, 
    struct sockaddr_in *servAddr) {

    /* SOCKET */
    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        err_sys("socket() failed");

    /* construct  structure */
    memset(servAddr, 0, sizeof(*servAddr));     
    servAddr->sin_family      = AF_INET;             
    servAddr->sin_addr.s_addr = inet_addr(servIP);   
    servAddr->sin_port        = htons(servPort); 

    /* CONNECT */
    if (connect(sock, (struct sockaddr *) servAddr, sizeof(*servAddr)) < 0)
        err_sys("connect() failed");

    return sock;
}

int main(int argc, char *argv[])
{
    int sock;                           
    struct sockaddr_in servAddr;        
    unsigned short servPort;            
    char *servIP;                       
    
    char msgString[RCVBUFSIZE];                    
    char msgBuffer[RCVBUFSIZE];         
    unsigned int msgStringLen;      
    
    int bytesRcvd;      

    if (argc != 3) {
       fprintf(stderr, "usage: %s <server IP> <port>\n", argv[0]);
       exit(1);
    }

    servIP = argv[1];               
    servPort = atoi(argv[2]);    

    sock = create_socket(servIP, servPort, &servAddr);              

    /* PROMPT for input */
    printf(">> "); scanf("%256s", msgString);
    msgStringLen = strlen(msgString);

    do {

        /* SEND */
        if (send(sock, msgString, msgStringLen, 0) != msgStringLen)
            err_sys("send() failed");

        /* RECEIVE */
        printf("<server>: ");                

        bytesRcvd = recv(sock, msgBuffer, RCVBUFSIZE - 1, 0); msgBuffer[bytesRcvd] = '\0';  
        
        printf("%s\n", msgBuffer);      /* print buffer */

        /* PROMPT for input */
        printf(">> "); scanf("%255s", msgString); msgString[RCVBUFSIZE - 1] = '\0';
        msgStringLen = strlen(msgString);

    } while(msgStringLen > 0);

    close(sock);
    exit(0);
}