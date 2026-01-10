#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "definicijeHashMape.h"
#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261

void createHashMap(hashMap* hashmap,int capacityNumber){
    hashmap->capacity = capacityNumber;
    hashmap->numOfElements = 0;

    hashmap->lista = (List**)malloc(sizeof(List*) * hashmap->capacity);

    for (int i = 0; i < hashmap->capacity; i++) {
        hashmap->lista[i] = NULL;
    }

    return;
}

void setListNode(List* node, void* key, Segment* segment){
    node->key = key;
    node->segment = segment;
    node->next = NULL;
    return;
}

//FNV-1a hash funkcija
//uint32_t znaci da ce uvek biti tacno 32 bita ako je to moguce
uint32_t hashFunction(hashMap* hashmap,void* address){

    uint32_t hash = FNV_OFFSET_BASIS;
    unsigned char* bytes = (unsigned char*)&address;
    for(int i = 0;i<sizeof(void*);i++){
        hash ^=(uint8_t)bytes[i];//xor-ujemo hash vrednost sa adresom
        hash *= FNV_PRIME;
    }

    return hash % hashmap->capacity;
}

void insert(hashMap* hashmap, void *key, Segment *value){

    int hashMapIndex = hashFunction(hashmap,value);

    List* newNode = (List*)malloc(sizeof(List));//kreirali novi deo liste;

    setListNode(newNode,key,value);
    //adresa od value je kljuc, a sama vrednost je podatkak koji se cuva

    if(hashmap->lista[hashMapIndex] == NULL){

        hashmap->lista[hashMapIndex] = newNode;

    }else{
        //desila se kolizija
        //dodajemo novi segment na pocetak liste sa istim indeksom

        newNode->next = hashmap->lista[hashMapIndex];

        hashmap->lista[hashMapIndex] = newNode;

    }

    return;

};

void delete(hashMap* hashmap, void *key){

        int hashMapIndex = hashFunction(hashmap,key);

        List* prethodniElem = NULL;

        List* trenutniElem = hashmap->lista[hashMapIndex];

        while(trenutniElem != NULL){

            if(strcmp((char*)key,(char*)trenutniElem->key)==0){

                if(trenutniElem == hashmap->lista[hashMapIndex]){
                    hashmap->lista[hashMapIndex] = trenutniElem->next;
                }else{

                    prethodniElem->next = trenutniElem->next;

                }

                free(trenutniElem);
                break;

            }

            prethodniElem = trenutniElem;
            trenutniElem = trenutniElem->next;

        }
        return;

}
Segment* search(hashMap* hashmap, void *key);
void printHashMap(hashMap* hashmap){

    List* trenutniElem = NULL;
    Segment* trenutniSegment = NULL;
    printf("-----------Ispis hashMape-----------\n");


    for(int i = 0;i<hashmap->capacity;i++){

        trenutniElem = hashmap->lista[i];

        if(trenutniElem != NULL){
            printf("\nElementi na indexu: %d\n",i);
            int brSeg = 1;
            while(trenutniElem != NULL){
                if(trenutniElem->segment == NULL){
                printf("Error: segment is NULL at index %d\n", i);
                }else{
                    trenutniSegment = trenutniElem->segment;
                    printf("\n--Segment br. %d--\n",brSeg);
                    printf("Dostupnost: %d",trenutniSegment->dostupnost);

                }
                brSeg++;
                trenutniElem = trenutniElem->next;
            }





        }

    }

}
