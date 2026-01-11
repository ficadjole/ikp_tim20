#include <stdio.h>
#include <stdlib.h>
#include "definicijeHashMape.h"
#include "definicijeListe.h"
#include "funkcije.h"

int main() {
    SegmentList mojHeap;
    hashMap mojaMapa;

    initializeHeapManager(&mojHeap, &mojaMapa, 10);

    void* adresa1 = allocate_memory(&mojHeap, &mojaMapa, 100);

    void* adresa2 = allocate_memory(&mojHeap, &mojaMapa, 500);

    printf("\n--- Stanje nakon alokacija ---\n");
    printSegmentList(&mojHeap);
    printHashMap(&mojaMapa);

    return 0;
}
