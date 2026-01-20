#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "funkcije.h"

void initializeHeapManager(SegmentList* list, hashMap* map, int mapCapacity){
    initSegmentList(list);
    createHashMap(map, mapCapacity);
    printf("HeapManager started successfully.\n");
}

void* allocate_memory(SegmentList* list, hashMap* map, size_t size){
    SegmentNode* found = findFirstFit(list, size);

    if(found == NULL) {
        printf("Free segment is not found. Allocating new...\n");
        addSegmentToList(list, size);
        found = list->tail;
    }

    found->data.dostupnost = 1;
    list->freeCount--;

    insert(map, found->data.adresa, &(found->data));

    printf("Successfully alocated! Address: %p, Size: %zu\n", found->data.adresa, found->data.velicina);

    return found->data.adresa;
}

float calculateFragmentation(SegmentList* list){
    if(list->totalCount == 0){
        return 0.0f;
    }

    float fragmentation = ((float)list->freeCount/(float)list->totalCount)*100.0f;

    return fragmentation;
}

void free_memory(SegmentList* list, hashMap* map, void *address){

    printf("\nPokazivac: %p\n",address);
    delete(map,address);
    findSegment(list,address);

}

char* parsingMessage (SegmentList* list, hashMap* map, char* buffer) {
    
    char *buff = malloc(MAX);
    int kod = 0;
    char *sep = strchr(buffer,'|');
    void *adresa = NULL;

    if(strlen(buffer) < 1 || buffer[0] == '\n') {
        strcpy(buff, "[SERVER] Greska: Poruka je prazna.\n");
        return buff;
    }

    if(!sep){
        strcpy(buff, "[SERVER] Format Error: Koristi format KOD|VREDNOST npr. 1|100 \n");
        return buff;
    }

    *sep='\0';
    char *kod_str = buffer;
    char *vrednost = sep + 1;

    switch (atoi(kod_str))
    {
    case 1:{
        
        int velicina = atoi(vrednost);

        if(velicina <= 0) {
            strcpy(buff, "[SERVER] Alokacija neuspela: Velicina mora biti veca od 0 \n");
        } else {
            void* adresa1 = allocate_memory(list,map,atoi(vrednost));

            if(adresa1 == NULL) {
                strcpy(buff, "[SERVER] Alokacija neuspela: Nema memorije. \n");
            } else {
                sprintf(buff,"[SERVER] Alokacija uspela. Alocirano %d bajtova na adresi: %p \n",velicina,adresa1);
            }
        }
        
        break;
    }
    case 2:{
        
        uintptr_t tmp = (uintptr_t)strtoull(vrednost,NULL,0);
        if(tmp == 0) {
            strcpy(buff, "[SERVER] Oslobadjanje neuspelo: Nevalidna adresa.\n");
        } else {
            adresa = (void*)tmp;
            free_memory(list,map,adresa);
            sprintf(buff, "[SERVER] Oslobadjanje uspelo. Memorija na adresi %p je oslobodjena.\n", adresa);
        }
        break;
    }
    default:
        sprintf(buff, "[SERVER] Nepoznat kod (%s). Koristi 1 (Alloc) ili 2 (Free).\n", kod_str);
        break;
    }

    return buff;

}
