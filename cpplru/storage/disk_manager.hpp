//
// Created by Isai GORDEEV on 14/09/2025.
//

#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "page.h"

class DiskManager {
 public:
  explicit DiskManager(const std::string& file_name) : fileName(file_name) {}

  void writePage(int page_id, const PrimitivePage& page) {
    std::ofstream out(fileName,
                      std::ios::binary | std::ios::in | std::ios::out);
    if (!out) {
      // Create file if not exists
      out.open(fileName, std::ios::binary | std::ios::trunc);
    }
    out.seekp(page_id * PrimitivePage::PAGE_SIZE, std::ios::beg);
    for (const auto& record : page.data) {
      out.write(reinterpret_cast<const char*>(&record.idx), sizeof(record.idx));
    }
    out.close();
  }

  PrimitivePage readPage(int page_id) {
    PrimitivePage page;
    std::ifstream in(fileName, std::ios::binary);
    if (!in) return page;

    in.seekg(page_id * PrimitivePage::PAGE_SIZE, std::ios::beg);
    for (int i = 0; i < PrimitivePage::MAX_RECORDS; i++) {
      PrimitiveRecord record;
      in.read(reinterpret_cast<char*>(&record.idx), sizeof(record.idx));
      if (in.gcount() != sizeof(record.idx)) break;
      page.data.push_back(record);
      page.size++;
    }
    in.close();
    return page;
  }

 private:
  std::string fileName;
};
