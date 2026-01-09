#ifndef DEFINICIJEHASHMAPE_H_INCLUDED
#define DEFINICIJEHASHMAPE_H_INCLUDED
#include "strukture.h"

void createHashMap(hashMap* hashmap,int capacityNumber);
int hashFunction(hashMap* hashmap,char* key);
void insert(hashMap* hashmap, char *key, Segment *value);
void delete(hashMap* hashmap, char *key);
Segment* search(hashMap* hashmap, char *key);

#endif // DEFINICIJEHASHMAPE_H_INCLUDED
