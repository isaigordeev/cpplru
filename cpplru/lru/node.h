//
// Created by Isai Gordeev on 29/06/2025.
//
#pragma once

#include <memory>

template <typename K> struct PrimitiveNode
{
    K key;

    std::shared_ptr<PrimitiveNode>(next);
    std::weak_ptr<PrimitiveNode>(prev);
    std::shared_ptr<PrimitiveNode>(bucket_next);

    explicit PrimitiveNode()
        : key(0), next(nullptr), prev(), bucket_next(nullptr){};
    explicit PrimitiveNode(const K& key)
        : key(key), next(nullptr), prev(), bucket_next(nullptr){};

    const K& get_key() const { return key; }
};
