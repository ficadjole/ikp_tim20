#ifndef STRUKTURE_H_INCLUDED
#define STRUKTURE_H_INCLUDED

typedef struct Segment{

    int dostupnost; //0 dostupno, 1 nije dostupno
    size_t velicina;
    void* adresa; //adresa samog segmenta

}Segment;

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


#endif // STRUKTURE_H_INCLUDED
