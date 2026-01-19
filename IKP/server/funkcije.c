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

    if(!sep){
        return NULL;
    }

    *sep='\0';
    char *kod_str = buffer;
    char *vrednost = sep + 1;

    switch (atoi(kod_str))
    {
    case 1:{
        
        void* adresa1 = allocate_memory(list,map,atoi(vrednost));
        
        
        sprintf(buff,"%x",adresa1);
        
        break;
    }
    case 2:{
        
        uintptr_t tmp = (uintptr_t)strtoull(vrednost,NULL,0);
        
        adresa = (void*)tmp;

        free_memory(list,map,adresa);
        strcpy(buff,"Uspesno ste oslobodili segment na zeljenoj adresi");
        break;
    }
    default:
        strcpy(buff, "Nepoznat kod");
        break;
    }

    return buff;

}
