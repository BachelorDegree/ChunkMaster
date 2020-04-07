#pragma once

#include <string>
#include <cstdint>
#include <colib/co_mutex.h>

extern libco::CoMutex* g_pMutexAllChunk;
std::string CanonicalChunkServerName(uint64_t iMachineId);
