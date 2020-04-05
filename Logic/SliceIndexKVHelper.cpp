#include <spdlog/spdlog.h>

#include "errcode.h"
#include "Proto/sliceindex.pb.h"
#include "PaxosKVServiceClient/PaxosKVServiceClient.hpp"

#include "SliceIndexKVHelper.hpp"

// K: slice_<hex_logical_id> V: PB SliceIdArray
int SliceIndexKVHelper::SetMapping(const uint64_t iLogical, const std::vector<uint64_t> &vecPhysical)
{
    ::sliceindex::SliceIdArray oPB;
    for (const auto i : vecPhysical)
        oPB.add_ids(i);
    auto sKey = fmt::format("slice_{:016x}", iLogical);
    ::paxoskv::SetReq  oReq;
    ::paxoskv::SetResp oRsp;
    oReq.set_key(sKey);
    oReq.set_value(oPB.SerializeAsString());
    
    PaxosKVServiceClient oClient;
    auto iRpcRet = oClient.Set(oReq, oRsp);
    if (iRpcRet != 0)
    {
        spdlog::error("SliceIndexKVHelper::SetMapping - PaxosKV Set failed, retcode: {}", iRpcRet);
        return E_PAXOSKV_SET_RPC_FAILED;
    }
    return 0;
}