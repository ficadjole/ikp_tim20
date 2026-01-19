#include "client.h"

void unosPodataka(int sockfd)
{

    char buff[MAX];
    int n;
    int b = 1;
    int odabir = 0;
    while(b!=0){

        bzero(buff,sizeof(buff)); //postavlja na nula buffer

        printf(">> Odaberite jednu od mogucnosti\n");
        printf(">> 1 - allocate_memory(int velicina)\n");
        printf(">> 2 - free_memory(void* adresa)\n");

        fgets(buff,sizeof(buff),stdin);
        odabir = atoi(buff);

        switch (odabir)
        {
        case 1:
            printf(">> Unesite zeljenu velicinu koju zelite da alocirate (format 1|xxx) : ");
            fgets(buff, sizeof(buff), stdin);
            break;
        case 2:
            printf(">> Unesite adresu segmenta koji zelite da oslobodite (format 2|xxx) : ");
            fgets(buff, sizeof(buff), stdin);
            break;
        default:
            break;
        }
        
        write(sockfd,buff,sizeof(buff));

        bzero(buff,sizeof(buff));

        read(sockfd,buff,sizeof(buff));

        printf(">> Poruka SERVERA: 0x%s\n",buff);

        if((strncmp(buff,"exit",4))==0){
            printf(">> Server prekinuo konekciju\n");
            break;
        }

    }
    
}