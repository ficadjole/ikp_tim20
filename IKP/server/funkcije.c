#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "funkcije.h"
#include "definicijeListe.h"

void initializeHeapManager(SegmentList* list, hashMap* map, int mapCapacity){
    initSegmentList(list);
    createHashMap(map, mapCapacity);
    list->numberOfAllocations = 0;
    list->numberOfDeallocations = 0;
    safePrint("HeapManager started successfully.\n");
}

void* allocate_memory(SegmentList* list, hashMap* map, size_t size){
   //sleep(5); za testiranje
   pthread_mutex_lock(&list->lock);
    safePrint("\n[ALLOCATION] ----------------------------------\n");
    SegmentNode* found = findFirstFit(list, size);

    if(found == NULL) {
        safePrint("Free segment is not found. Allocating new...\n");
        addSegmentToList(list, size);
        found = list->tail;
    }

    found->data.dostupnost = 1;
    list->freeCount--;

    insert(map, found->data.adresa, &(found->data));

    safePrint("Successfully alocated! Address: %p, Size: %zu\n", found->data.adresa, found->data.velicina);

    pthread_mutex_unlock(&list->lock);
    safePrint("[THREAD %lu] Klijent je ZAVRSIO alokaciju.\n", (unsigned long)pthread_self());
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
    pthread_mutex_lock(&list->lock);

    safePrint("\n[DEALLOCATION] ----------------------------------\n");
    safePrint("[THREAD %lu] Pokrenut zahtev za oslobadjanje.\n", (unsigned long)pthread_self());
    safePrint("[INFO] Ciljna adresa: %p\n", address);

    safePrint("\nPokazivac: %p\n",address);
    delete(map,address);
    findSegment(list,address);

    if(list->freeCount > 5) {
        cleanupSegments(list);
    }

    pthread_mutex_unlock(&list->lock);

}

void cleanupSegments(SegmentList* list) {
    while(list->freeCount > 5) {
        SegmentNode* node = list->tail;

        while(node != NULL && node->data.dostupnost != 0) {
            node = node->prev;
        }

        if(node != NULL) {
            removeSegmentFromList(list, node);
            safePrint("[CLEANUP] Segmen uspesno uklonjen. Preostalo slobodnih: %d\n", list->freeCount);
        } else {
            break;
        }
    }
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

    vrednost[strcspn(vrednost, "\r\n")] = 0;

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
                pthread_mutex_lock(&list->lock);
                list->numberOfAllocations++;
                pthread_mutex_unlock(&list->lock);
                printInstr(list);
            }
        }
        
        break;
    }
    case 2: {
    char *clean_addr = vrednost;
    while(*clean_addr == ' ') clean_addr++; 
    clean_addr[strcspn(clean_addr, "\r\n ")] = 0; //bez ovog nece lijepo da radi dealociranje

    uintptr_t tmp = (uintptr_t)strtoull(clean_addr, NULL, 0);
    void* adresa_za_free = (void*)tmp;


    pthread_mutex_lock(&list->lock);
    Segment* provera = search(map, adresa_za_free);
    pthread_mutex_unlock(&list->lock);

    if (provera == NULL) {
        sprintf(buff, "[SERVER] Greska: Adresa %p nije u mapi (proveri unos).\n", adresa_za_free);
    } else {
        free_memory(list, map, adresa_za_free);
        sprintf(buff, "[SERVER] Oslobadjanje uspelo za adresu %p.\n", adresa_za_free);
        pthread_mutex_lock(&list->lock);
        list->numberOfDeallocations++;
        pthread_mutex_unlock(&list->lock);
        printInstr(list);
    }
    break;
    }
    default:
        sprintf(buff, "[SERVER] Nepoznat kod (%s). Koristi 1 (Alloc) ili 2 (Free).\n", kod_str);
        break;
    }

    return buff;
}

void printInstr(SegmentList* list) {

    pthread_mutex_lock(&list->lock);

    float fragm = 0.0;

    if(list->totalCount > 0) {
        fragm = calculateFragmentation(list);
    }

    int nA = list->numberOfAllocations;
    int nD = list->numberOfDeallocations;
    float fg = fragm;

    pthread_mutex_unlock(&list->lock);

    safePrint("\n>>>> INSTRUMENTALIZACIJA SISTEMA <<<<\n");
    safePrint("1) Ukupan broj alokacija:   %d\n", nA);
    safePrint("2) Ukupan broj dealokacija: %d\n", nD);
    safePrint("3) Stepen fragmentacije:    %.2f%%\n", fg);
    safePrint("--------------------------------------\n");


}
