#include "client.h"

void unosPodataka(int sockfd)
{

    char buff[MAX];
    int n;
    int b = 1;
    int odabir = 0;
    while(b!=0){

        bzero(buff,sizeof(buff)); //postavlja na nula buffer

        safePrint(">> Odaberite jednu od mogucnosti\n");
        safePrint(">> 1 - allocate_memory(int velicina)\n");
        safePrint(">> 2 - free_memory(void* adresa)\n");
        safePrint(">> 3 - STRESS TEST (Automatska simulacija) \n");

        fgets(buff,sizeof(buff),stdin);
        odabir = atoi(buff);

        switch (odabir)
        {
        case 1:
            safePrint(">> Unesite zeljenu velicinu koju zelite da alocirate (format 1|xxx) : ");
            fgets(buff, sizeof(buff), stdin);
            break;
        case 2:
            safePrint(">> Unesite adresu segmenta koji zelite da oslobodite (format 2|xxx) : ");
            fgets(buff, sizeof(buff), stdin);
            break;
        case 3:
        {
            char adrese[20][MAX];

            safePrint("[START] Stress test: Alociranje 20 blokova...\n");

            for(int i = 0; i < 20; i++) {
                sprintf(buff, "1|%d", (rand()%100) + 10);
                write(sockfd, buff, sizeof(buff));

                bzero(buff, sizeof(buff));
                read(sockfd, buff, sizeof(buff));

                char *pos = strstr(buff, "0x");
                if (pos) {
                    sscanf(pos, "%s", adrese[i]);
                }
                safePrint("Test %d/20: %s", i+1, buff);
            }

            safePrint("\n[STEP 2] Stress test: Oslobađanje svakog drugog bloka (fragmentacija)...\n");
            for(int i = 0; i < 20; i += 2) {
                sprintf(buff, "2|%s", adrese[i]);
                write(sockfd, buff, sizeof(buff));
                
                bzero(buff, sizeof(buff));
                read(sockfd, buff, sizeof(buff));
                safePrint("Oslobođeno %d/10: %s", (i/2)+1, buff);
            }
            
            safePrint("\n[FINISH] Stress test završen. Pogledajte logove servera.\n");
            continue; 
        }
        default:
            break;
        }
        
        write(sockfd,buff,sizeof(buff));

        bzero(buff,sizeof(buff));

        read(sockfd,buff,sizeof(buff));

        safePrint(">> Poruka SERVERA: 0x%s\n",buff);

        if((strncmp(buff,"exit",4))==0){
            safePrint(">> Server prekinuo konekciju\n");
            break;
        }

    }
    
}

void safePrint(char* poruka,...){

    va_list args;
    va_start(args, poruka);
    
    flockfile(stdout);
        vprintf(poruka, args);
    funlockfile(stdout);

    va_end(args);
}