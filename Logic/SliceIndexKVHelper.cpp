#include <spdlog/spdlog.h>

#include "errcode.h"
#include "Proto/sliceindex.pb.h"
#include "PaxosKVServiceClient/PaxosKVServiceClient.hpp"

#include "SliceIndexKVHelper.hpp"

static std::string SliceIndexKey(const uint64_t iLogical)
{
    return fmt::format("slice_{:016x}", iLogical);
}

// K: slice_<hex_logical_id> V: PB SliceIdArray
int SliceIndexKVHelper::SetMapping(const uint64_t iLogical, const std::vector<uint64_t> &vecPhysical)
{
    ::sliceindex::SliceIdArray oPB;
    for (const auto i : vecPhysical)
        oPB.add_ids(i);
    auto sKey = SliceIndexKey(iLogical);
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

int SliceIndexKVHelper::GetMapping(const uint64_t iLogical, std::vector<uint64_t> &vecPhysical)
{
    auto sKey = SliceIndexKey(iLogical);
    ::paxoskv::GetReq  oReq;
    ::paxoskv::GetResp oRsp;
    oReq.set_key(sKey);

    PaxosKVServiceClient oClient;
    auto iRpcRet = oClient.Get(oReq, oRsp);
    if (iRpcRet != 0)
    {
        spdlog::error("SliceIndexKVHelper::GetMapping - PaxosKV Get failed, retcode: {}", iRpcRet);
        return E_PAXOSKV_SET_RPC_FAILED;
    }

    ::sliceindex::SliceIdArray oPB;
    if (!oPB.ParseFromString(oRsp.value()))
    {
        spdlog::error("SliceIndexKVHelper::GetMapping - protobuf deserialize failed");
        return E_PROTOBUF_DESERIALIZE_FAILED;
    }

    for (auto i = 0; i < oPB.ids_size(); ++i)
        vecPhysical.push_back(oPB.ids(i));

    return 0;
}