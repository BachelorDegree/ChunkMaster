#include <colib/co_routine_specific.h>
#include "ChunkMasterServiceImpl.hpp"
struct __ChunkMasterServiceImplWrapper{
    ChunkMasterServiceImpl * pImpl;
};
CO_ROUTINE_SPECIFIC(__ChunkMasterServiceImplWrapper, g_coChunkMasterServiceImplWrapper)
ChunkMasterServiceImpl *ChunkMasterServiceImpl::GetInstance()
{
    return g_coChunkMasterServiceImplWrapper->pImpl;
}
void ChunkMasterServiceImpl::SetInstance(ChunkMasterServiceImpl *pImpl)
{
    g_coChunkMasterServiceImplWrapper->pImpl = pImpl;
}
