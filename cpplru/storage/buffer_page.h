//
// Created by Isai GORDEEV on 01/07/2025.
//

#pragma once

#include "page.h"

struct BufferPage {
  PrimitivePage page;
  bool dirty = false;
  int pinCount = 0;
  int pageId = -1;
};