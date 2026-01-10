#ifndef DEFINICIJEHASHMAPE_H_INCLUDED
#define DEFINICIJEHASHMAPE_H_INCLUDED
#include <stdint.h>
#include "strukture.h"

void createHashMap(hashMap* hashmap,int capacityNumber);
void setListNode(List* node, void* key, Segment* segment);
uint32_t hashFunction(hashMap* hashmap,void* address);
void insert(hashMap* hashmap, void* key, Segment* value);
void delete(hashMap* hashmap, void* key);
Segment* search(hashMap* hashmap, void* key);
void printHashMap(hashMap* hasmap);

#endif // DEFINICIJEHASHMAPE_H_INCLUDED
