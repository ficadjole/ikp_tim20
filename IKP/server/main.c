#include <arpa/inet.h> // inet_addr()
#include <stdio.h>
#include <unistd.h> // read(), write(), close()
#include <strings.h> // bzero()
#include <stdlib.h>
#include <string.h>
#include "definicijeHashMape.h"
#include "definicijeListe.h"
#include "funkcije.h"

void func(int connfd) 
{   
    SegmentList mojHeap;
    hashMap mojaMapa;

    initializeHeapManager(&mojHeap, &mojaMapa, 10);

    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
  
        int n = read(connfd, buff, sizeof(buff)); 

        if( n <= 0) {
            printf("[DISCONNECT] Klijent je zatvorio vezu.\n");
            break;
        }

        printf("[LOG] Zahtev od klijenta: %s\n", buff);

        char *msg = parsingMessage(&mojHeap,&mojaMapa,buff);
        
        strcpy(buff,msg);
        free(msg);

        write(connfd, buff, sizeof(buff)); 
  
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 


int main() {

    int sockfd, connfd, len;

    struct sockaddr_in servaddr,cli;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd == -1){
        printf("Doslo je do greske prilikom kreiranja socketa\n");
        exit(0);
    }else{
        printf("Uspesno kreiran socket\n");
    }

    bzero(&servaddr,sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//bilo koja adresa sa sistema moze da salje poruke
    servaddr.sin_port = htons(PORT);

    if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0){
        printf("Bindovanje soketa je neuspelo!\n");
        exit(0);
    }else{
        printf("Uspesno smo bindovali socket\n");
    }

    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server accept the client...\n"); 
  
    // Function for chatting between client and server 
    func(connfd); 

    close(sockfd);

    return 0;
}