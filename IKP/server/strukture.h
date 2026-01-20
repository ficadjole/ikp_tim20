#ifndef STRUKTURE_H_INCLUDED
#define STRUKTURE_H_INCLUDED
#define PORT 8080
#define MAX 80
#define SA struct sockaddr 

#include <pthread.h>

typedef struct Segment{

    int dostupnost; //0 dostupno, 1 nije dostupno
    size_t velicina;
    void* adresa; //adresa samog segmenta

}Segment;

typedef struct SegmentNode {
    Segment data;
    struct SegmentNode* next;
    struct SegmentNode* prev; //dvostruko spregnuta lista
}SegmentNode;

typedef struct SegmentList{
    SegmentNode* head;
    SegmentNode* tail;
    int freeCount; //broj slobodnih segmenata
    int totalCount;
    int numberOfAllocations;
    int numberOfDeallocations;  //broj alokacija i dealokacija
    pthread_mutex_t lock;
}SegmentList;

typedef struct List{
    void* key;//ovo ce biti adresa segmenta
    Segment* segment;
    struct List* next;
}List;

typedef struct hashMap{

    int numOfElements;
    int capacity;
    List** lista;//ovo je pocetna adresa liste

}hashMap;

typedef struct {
    int connfd;
    struct SegmentList* mojHeap;
    struct hashMap* mojaMapa;
} thread_args_t;


#endif // STRUKTURE_H_INCLUDED
