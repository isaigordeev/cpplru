//
// Created by Isai Gordeev on 29/06/2025.
//

#pragma once

#include "node.h"
constexpr int DEFAULT_CAPACITY = 1000;

template <typename K> class LRUCacheChain
{
  public:
    explicit LRUCacheChain<K>(int capacity = DEFAULT_CAPACITY)
        : chain_capacity(capacity),
          head(std::make_shared<PrimitiveNode<K>>(K{})),
          tail(std::make_shared<PrimitiveNode<K>>(K{}))
    {
        head->next = tail;
        tail->prev = head;
    }

  private:
    int size = 0;
    int chain_capacity = DEFAULT_CAPACITY;

    std::shared_ptr<PrimitiveNode<K>> head; // Most recently used (MRU) sentinel
    std::shared_ptr<PrimitiveNode<K>>
            tail; // Least recently used (LRU) sentinel

    void remove_tail()
    {

        if (tail->prev.expired() || tail->prev.lock() == head) {
            return;
        }

        auto curr_node = tail->prev.lock()->prev.lock();
        curr_node->next = tail;
        tail->prev = curr_node;

        size--;
    };

    void fronthead_put(std::shared_ptr<PrimitiveNode<K>> node)
    {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void extract_node(std::shared_ptr<PrimitiveNode<K>> node)
    {
        if (!node->prev.expired()) {
            node->prev.lock()->next = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
        node->prev.reset();
        node->next.reset();
        size--;
    }

  public:
    void put(std::shared_ptr<PrimitiveNode<K>> node)
    {
        bool node_already_in_chain =
                (node->next != nullptr || node->prev.lock() != nullptr);

        if (node_already_in_chain) {
            extract_node(node);
        }
        fronthead_put(node);
        size++;

        if (size > chain_capacity) {
            remove_tail();
        }
    }

    int get_size() { return size; }

    std::shared_ptr<PrimitiveNode<K>> get_head() const
    {
        if (head->next == tail) {
            return nullptr;
        }
        return head->next;
    }
};
