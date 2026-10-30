#pragma once

#include "Types.hpp"

#include <vector>

struct LevelInfo {
    Price price_;
    Quantity initialQuantity_;
};

using LevelInfos = std::vector<LevelInfo>;
