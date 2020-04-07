#include "Global.hpp"
#include <fmt/format.h>
#include "coredeps/SliceId.hpp"

libco::CoMutex* g_pMutexAllChunk;

std::string CanonicalChunkServerName(uint64_t iMachineId)
{
    Storage::SliceId oMachineId(iMachineId);
    return fmt::format(FMT_STRING("ChunkServerService.{}.{}"), oMachineId.Cluster(), oMachineId.Machine());
}
