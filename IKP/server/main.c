#include <arpa/inet.h> // inet_addr()
#include <stdio.h>
#include <unistd.h> // read(), write(), close()
#include <strings.h> // bzero()
#include <stdlib.h>
#include <string.h>
#include "definicijeHashMape.h"
#include "definicijeListe.h"
#include "funkcije.h"

#include <pthread.h>

void func(int connfd, SegmentList* mojHeap, hashMap* mojaMapa) 
{   

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

        char *msg = parsingMessage(mojHeap,mojaMapa,buff);
        
        strcpy(buff,msg);
        free(msg);

        write(connfd, buff, sizeof(buff)); 
  
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
}

void* client_handler(void* arg) {
    thread_args_t* args = (thread_args_t*)arg;
    func(args->connfd, args->mojHeap, args->mojaMapa);
    
    printf("[THREAD] Klijent na socketu %d se odjavio.\n", args->connfd);
    close(args->connfd);
    free(args);
    return NULL;
}


int main() {

    int sockfd, connfd, len;

    struct sockaddr_in servaddr,cli;

    SegmentList mojHeap;
    hashMap mojaMapa;
    initializeHeapManager(&mojHeap, &mojaMapa, 10); //prebacila sam ovdje da bi se inicijalizovao zajednicki resurs samo jednom
    pthread_mutex_init(&mojHeap.lock, NULL);

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
    
    while(1) {
        len = sizeof(cli);
        // Accept the data packet from client and verification 
        connfd = accept(sockfd, (SA*)&cli, &len);

        if (connfd < 0) { 
            printf("Server accept failed...\n"); 
            continue;
        } 

        printf("[SERVER] Prihvacen novi klijent na soketu %d \n", connfd);

        thread_args_t* args = malloc(sizeof(thread_args_t));
        args->connfd = connfd;
        args->mojHeap = &mojHeap;
        args->mojaMapa = &mojaMapa;

        pthread_t tid;
        if(pthread_create(&tid, NULL, client_handler, args) != 0) {
            perror("Thread creation failed");
            free(args);
            close(connfd);
        }

        pthread_detach(tid);
    }

    pthread_mutex_destroy(&mojHeap.lock);

    close(sockfd);

    return 0;
}