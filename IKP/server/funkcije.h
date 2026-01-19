#ifndef FUNKCIJE_H_INCLUDED
#define FUNKCIJE_H_INCLUDED

#include "definicijeHashMape.h"
#include "definicijeListe.h"

void initializeHeapManager(SegmentList* list, hashMap* map, int mapCapacity);
void* allocate_memory(SegmentList* list, hashMap* map, size_t size);
float calculateFragmentation(SegmentList* list);
void free_memory(SegmentList* list, hashMap* map, void *adresa);

char* parsingMessage(SegmentList* list, hashMap* map,char*buffer);

#endif // FUNKCIJE_H_INCLUDED
