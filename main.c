#include <stdio.h>
#include <stdlib.h>
#include "definicijeHashMape.h"
#include "definicijeListe.h"

int main()
{
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

    testiranjeRada();
    return 0;
}
