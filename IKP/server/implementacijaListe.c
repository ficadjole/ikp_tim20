#include <stdio.h>
#include <stdlib.h>

#include "definicijeListe.h"

pthread_mutex_t print_mtx = PTHREAD_MUTEX_INITIALIZER;

void initSegmentList(SegmentList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->freeCount = 0;
    list->totalCount = 0;
}

void addSegmentToList(SegmentList* list, size_t size) {
    SegmentNode* newNode = (SegmentNode*)malloc(sizeof(SegmentNode));

    if(newNode == NULL) return;

    //inicijalizacija samog segmenta
    newNode->data.velicina = size;
    newNode->data.dostupnost = 0;
    newNode->data.adresa = malloc(size);

    //povezivanje liste
    newNode->next = NULL;
    newNode->prev = list->tail;

    if(list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode; //ako je lista bila prazna
    }

    list->tail = newNode;
    list->totalCount++;
    list->freeCount++;
}

SegmentNode* findFirstFit(SegmentList* list, size_t size) {
    SegmentNode* current = list->head;

    while(current != NULL) {
        if(current->data.dostupnost == 0 && current->data.velicina >= size){
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void removeSegmentFromList(SegmentList* list, SegmentNode* node) {
    if(node == NULL || list->head == NULL) return;

    if(node->prev != NULL) {
        node->prev->next = node->next;
    } else{
        list->head = node->next;
    }

    if(node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    if(node->data.dostupnost == 0) {
        list->freeCount--;
    }

    list->totalCount--;

    free(node->data.adresa);
    free(node);
}

void removeDataFromSegment(SegmentNode* node) {

    if(node == NULL) return;

    node->data.dostupnost = 0;

}

void findSegment(SegmentList* list, void* address){

    SegmentNode* current = list->head;

    while(current != NULL) {
        if(current->data.adresa == address){
            
            removeDataFromSegment(current);
            list->freeCount++;
            return;
        }

        current = current->next;
    }

}


void printSegmentList(SegmentList* list) {
    SegmentNode* current = list->head;
    int i = 0;

    safePrint("\n======= PREGLED HEAP MEMORIJE =======\n");
    safePrint("Ukupno segmenata: %d | Slobodnih: %d\n", list->totalCount, list->freeCount);
    safePrint("--------------------------------------\n");

    if (current == NULL) {
        safePrint("Lista je prazna.\n");
        return;
    }

    while (current != NULL) {
        safePrint("Segment [%d]: \n", i++);
        safePrint("  - Adresa: %p\n", current->data.adresa);
        safePrint("  - Velicina: %zu bajtova\n", current->data.velicina);
        safePrint("  - Status: %s\n", (current->data.dostupnost == 0) ? "SLOBODAN" : "ZAUZET");
        safePrint("--------------------------------------\n");
        current = current->next;
    }
    safePrint("======================================\n\n");
}

void testListe(){
     SegmentList mojaLista;
    initSegmentList(&mojaLista);

    safePrint("---Testiranje Liste Segmenata ---\n");

    addSegmentToList(&mojaLista, 100);
    addSegmentToList(&mojaLista, 500);
    addSegmentToList(&mojaLista, 200);

    printSegmentList(&mojaLista);

    size_t trazenaVelicina = 300;
    SegmentNode* pronadjen = findFirstFit(&mojaLista, trazenaVelicina);

    if (pronadjen != NULL) {
        safePrint("Pronadjen segment! Adresa: %p, Velicina: %zu\n",
                pronadjen->data.adresa, pronadjen->data.velicina);


        pronadjen->data.dostupnost = 1;
        mojaLista.freeCount--;
    } else {
        safePrint("Nema dovoljno velikog slobodnog segmenta.\n");
    }

    printSegmentList(&mojaLista);

    if (pronadjen != NULL) {
        safePrint("\nBrisem pronadjeni segment iz liste...\n");
        removeSegmentFromList(&mojaLista, pronadjen);
    }

    printSegmentList(&mojaLista);
}

void safePrint(char* poruka, ...) {
    va_list args;
    va_start(args, poruka);

    pthread_mutex_lock(&print_mtx);
    vprintf(poruka, args);
    fflush(stdout); 
    pthread_mutex_unlock(&print_mtx);

    va_end(args);
}

