#ifndef DEFINICIJELISTE_H_INCLUDED
#define DEFINICIJELISTE_H_INCLUDED
#include <stdint.h>
#include <stdarg.h>
#include "strukture.h"

void initSegmentList(SegmentList* list);
void addSegmentToList(SegmentList* list, size_t size);
SegmentNode* findFirstFit(SegmentList* list, size_t size);
void removeSegmentFromList(SegmentList* list, SegmentNode* node);
void removeDataFromSegment(SegmentNode* node);
void findSegment(SegmentList* list, void* address);
void printSegmentList(SegmentList* list);
void testListe();
void safePrint(char*poruka,...);

#endif // DEFINICIJELISTE_H_INCLUDED
