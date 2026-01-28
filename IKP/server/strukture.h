#ifndef STRUKTURE_H_INCLUDED
#define STRUKTURE_H_INCLUDED
#define PORT 8080
#define MAX 80
#define SA struct sockaddr 

#include <pthread.h>

typedef struct Segment{
    int dostupnost; 
    size_t velicina;
    void* adresa; 
}Segment;

typedef struct SegmentNode {
    Segment data;
    struct SegmentNode* next;
    struct SegmentNode* prev;
}SegmentNode;

typedef struct SegmentList{
    SegmentNode* head;
    SegmentNode* tail;
    int freeCount;
    int totalCount;
    int numberOfAllocations;
    int numberOfDeallocations;
    pthread_mutex_t lock;
}SegmentList;

typedef struct List{
    void* key;
    Segment* segment;
    struct List* next;
}List;

typedef struct hashMap{

    int numOfElements;
    int capacity;
    List** lista;

}hashMap;

typedef struct {
    int connfd;
    struct SegmentList* mojHeap;
    struct hashMap* mojaMapa;
} thread_args_t;


#endif // STRUKTURE_H_INCLUDED
