//
// Created by Isai GORDEEV on 14/09/2025.
//

#pragma once

#include <cassert>

#include "primitive_semaphore.h"

template <class Tag, class SemaphoreClass>
class TaggedSemaphore {
 public:
  class Permit {
    friend class TaggedSemaphore;

   private:
    Permit() = default;

    void Invalidate() { valid_ = false; }

   private:
    bool valid_{true};

   public:
    ~Permit() { assert(!valid_); }
  };

 public:
  explicit TaggedSemaphore(size_t permits) : tagged_semaphore_(permits) {}

  Permit Acquire() {
    tagged_semaphore_.Acquire();
    return Permit{};
  }

  void Release(Permit&& permit) {
    tagged_semaphore_.Release();
    permit.Invalidate();
  }

 private:
  SemaphoreBase<SemaphoreClass> tagged_semaphore_;
};