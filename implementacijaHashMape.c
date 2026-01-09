#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definicijeHashMape.h"

void createHashMap(hashMap* hashmap,int capacityNumber){
    hashmap->capacity = capacityNumber;
    hashmap->numOfElements = 0;
    return;
}
int hashFunction(hashMap* hashmap,char* key){

    unsigned long i = 0;
    for(int j = 0; key[j];j++){
        i += key[j];
    }
    printf("%d\n",hashmap->capacity);
    return i % hashmap->capacity;

}
void insert(hashMap* hashmap, char *key, Segment *value);
void delete(hashMap* hashmap, char *key);
Segment* search(hashMap* hashmap, char *key);
