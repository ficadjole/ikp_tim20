#include <arpa/inet.h> // inet_addr()
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main(int argc, char const *argv[])
{

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd == -1){
        safePrint("Doslo je do greske prilikom kreiranja socketa\n");
        exit(0);
    }else{
        safePrint("Uspesno kreiran socket\n");
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr)) != 0 ){
        safePrint("Konekcija nije uspesno uspotavljena!\n");
        exit(0);
    }else{
        safePrint("Uspesno ste se povezali na server\n");
    }

    unosPodataka(sockfd);

    close(sockfd);

    return 0;
}
