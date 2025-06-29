//
// Created by Isai Gordeev on 29/06/2025.
//
#pragma once

#include <memory>

template<typename K, typename V>

struct PrimitiveNode {
  K key;
  V value;

  std::shared_ptr<PrimitiveNode>(next);
  std::weak_ptr<PrimitiveNode>(prev);

  std::shared_ptr<PrimitiveNode>(bucket_next);

  PrimitiveNode(const K& key, const V& value):key(key), value(value), next(nullptr), prev(), bucket_next(nullptr){
  }
};