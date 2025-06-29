#include <iostream>

extern "C" {
#include "lru.h" // C interface
}

int main()
{
    std::cout << "Using LRU cache from C in C++!" << std::endl;

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
