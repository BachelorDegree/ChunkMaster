#pragma once

#include <vector>
#include <cstdint>

class SliceIndexKVHelper
{
public:
    static int SetMapping(const uint64_t iLogical, const std::vector<uint64_t> &vecPhysical);
};