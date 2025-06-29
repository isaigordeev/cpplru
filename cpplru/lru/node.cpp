//
// Created by Isai Gordeev on 29/06/2025.
//

#include "node.h"

template <typename K>
const K& PrimitiveNode<K>::get_value() const
{
    return value;
}
