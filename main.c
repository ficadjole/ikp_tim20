#include <stdio.h>
#include <stdlib.h>
#include "definicijeHashMape.h"

int main()
{
    hashMap hm;
    createHashMap(&hm,2);

    Segment* segment = malloc(sizeof(Segment));
    segment->dostupnost = 0;
    segment->adresa = segment;
    segment->velicina = NULL;

    Segment* segment2 = malloc(sizeof(Segment));
    segment2->dostupnost = 0;
    segment2->adresa = segment2;
    segment2->velicina = NULL;

    List lista;
    setListNode(&lista,segment,segment);

    setListNode(&lista,segment2,segment2);

    insert(&hm,segment->adresa,segment);

    insert(&hm,segment2->adresa,segment2);

    printHashMap(&hm);

    delete(&hm,segment);

    printHashMap(&hm);


    return 0;
}
