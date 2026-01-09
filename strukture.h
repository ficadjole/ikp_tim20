#ifndef STRUKTURE_H_INCLUDED
#define STRUKTURE_H_INCLUDED

typedef struct Segment{

    int dostupnost; //0 dostupno, 1 nije dostupno
    size_t velicina;
    void* adresa;

}Segment;

typedef struct hashMap{

    int numOfElements;
    int capacity;
    Segment* seg;

}hashMap;


#endif // STRUKTURE_H_INCLUDED
