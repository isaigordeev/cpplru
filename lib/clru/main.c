//
// Created by Isai Gordeev on 22/05/2025.
//

#include "chain.h"
#include "hash.h"
#include "lru.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    LRU* lru = lru_init(2, 10);

    lru_put(lru, 6);
    lru_put(lru, 8);
    lru_put(lru, 5);
    lru_put(lru, 6);
    lru_put(lru, 2);

    // Cleanup
    lru_free(lru);

    return EXIT_SUCCESS;
}