//
// Created by Isai GORDEEV on 01/07/2025.
//

#pragma once

struct PrimitiveRecord
{
    int idx;

    bool operator==(const PrimitiveRecord& other) const
    {
        return idx == other.idx;
    }
    PrimitiveRecord() : idx(0){};
    explicit PrimitiveRecord(int idx) : idx(idx){};
};
