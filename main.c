#include <stdio.h>
#include <stdlib.h>
#include "definicijeHashMape.h"
#include "definicijeListe.h"

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

    //testiranje Liste

    SegmentList mojaLista;
    initSegmentList(&mojaLista);

    printf("---Testiranje Liste Segmenata ---\n");

    addSegmentToList(&mojaLista, 100);
    addSegmentToList(&mojaLista, 500);
    addSegmentToList(&mojaLista, 200);

    printSegmentList(&mojaLista);

    size_t trazenaVelicina = 300;
    SegmentNode* pronadjen = findFirstFit(&mojaLista, trazenaVelicina);

    if (pronadjen != NULL) {
        printf("Pronadjen segment! Adresa: %p, Velicina: %zu\n",
                pronadjen->data.adresa, pronadjen->data.velicina);


        pronadjen->data.dostupnost = 1;
        mojaLista.freeCount--;
    } else {
        printf("Nema dovoljno velikog slobodnog segmenta.\n");
    }

    printSegmentList(&mojaLista);

    if (pronadjen != NULL) {
        printf("\nBrisem pronadjeni segment iz liste...\n");
        removeSegmentFromList(&mojaLista, pronadjen);
    }

    printSegmentList(&mojaLista);

    return 0;
}
