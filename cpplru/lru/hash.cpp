//
// Created by Isai Gordeev on 29/06/2025.
//

#include "hash.h"

template <typename K>
size_t LRUHashTable<K>::hash(K& key){
    return hasher(key);
}

template <typename K>
size_t LRUHashTable<K>::hash_node(PrimitiveNode<K>& node){
    return hash(node.get_value());
}
