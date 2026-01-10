#ifndef DEFINICIJELISTE_H_INCLUDED
#define DEFINICIJELISTE_H_INCLUDED
#include <stdint.h>
#include "strukture.h"

void initSegmentList(SegmentList* list);
void addSegmentToList(SegmentList* list, size_t size);
SegmentNode* findFirstFit(SegmentList* list, size_t size);
void removeSegmentFromList(SegmentList* list, SegmentNode* node);
void printSegmentList(SegmentList* list);

#endif // DEFINICIJELISTE_H_INCLUDED
