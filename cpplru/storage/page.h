//
// Created by Isai GORDEEV on 06/07/2025.
//

#pragma once
#include "record.h"
#include <cstddef>
#include <cstdint>
#include <vector>

class RawPage
{
    // ——————————————————————————————————————————————————————————————
    //   PUBLIC TYPES & CONSTANTS
  public:
    static constexpr size_t PAGE_SIZE = 4096;
    using byte_t = std::byte;
    using page_id_t = std::uint64_t;
    using slot_count_t = std::uint16_t;
    using offset_t = std::uint16_t;
};

class PrimitivePage
{
  public:
    static constexpr int PAGE_SIZE = 4096;
    static constexpr int RECORD_SIZE = sizeof(PrimitiveRecord);
    static constexpr int MAX_RECORDS = PAGE_SIZE / RECORD_SIZE;

    int size = 0;
    std::vector<PrimitiveRecord> data;

    PrimitivePage() = default;

    bool insertRecord(PrimitiveRecord& record)
    {
        if (size < MAX_RECORDS) {
            data.push_back(record);
            size++;
            return true;
        }
        return false;
    }
};