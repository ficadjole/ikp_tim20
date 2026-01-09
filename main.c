#include <stdio.h>
#include <stdlib.h>
#include "definicijeHashMape.h"

int main()
{
    hashMap hm;
    createHashMap(&hm,3);
    unsigned long hashVrednost = hashFunction(&hm,"abubakar");
    printf("%lu",&hashVrednost);

    return 0;
}
