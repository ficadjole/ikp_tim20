#include <stdio.h>
#include <stdlib.h>

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
