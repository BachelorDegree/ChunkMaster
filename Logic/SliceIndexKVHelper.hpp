#pragma once

#include <vector>
#include <cstdint>

class SliceIndexKVHelper
{
public:
    static int SetMapping(const uint64_t iLogical, const std::vector<uint64_t> &vecPhysical);
    static int GetMapping(const uint64_t iLogical, std::vector<uint64_t> &vecPhysical);
    static int GetLogicalId(const uint64_t iPhysical, uint64_t &outLogical);
};