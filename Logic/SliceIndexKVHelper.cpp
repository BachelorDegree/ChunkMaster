#include <cstring>
#include <spdlog/spdlog.h>

#include "errcode.h"
#include "Proto/sliceindex.pb.h"
#include "PaxosKVServiceClient/PaxosKVServiceClient.hpp"

#include "SliceIndexKVHelper.hpp"

static std::string SliceIndexKey(const uint64_t iLogical)
{
    return fmt::format("slice_{:016x}", iLogical);
}

static std::string SliceReverseIndexKey(const uint64_t iPhysical)
{
    return fmt::format("rslice_{:016x}", iPhysical);
}

// K: slice_<hex_logical_id> V: PB SliceIdArray (正查)
// K: rslice_<hex_physical_id> V: binary uint64_t (反查)
int SliceIndexKVHelper::SetMapping(const uint64_t iLogical, const std::vector<uint64_t> &vecPhysical)
{
    // 正查索引
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
        spdlog::error("SliceIndexKVHelper::SetMapping - l2p PaxosKV Set failed, retcode: {}", iRpcRet);
        return E_PAXOSKV_SET_RPC_FAILED;
    }

    // 反查索引
    for (const auto i : vecPhysical)
    {
        char buf[32];
        memcpy(buf, &iLogical, sizeof(iLogical));
        oReq.set_key(SliceReverseIndexKey(i));
        oReq.set_value(buf, sizeof(iLogical));
        auto iRpcRet = oClient.Set(oReq, oRsp);
        if (iRpcRet != 0)
        {
            spdlog::error("SliceIndexKVHelper::SetMapping - p2l PaxosKV Set failed, retcode: {}", iRpcRet);
            return E_PAXOSKV_SET_RPC_FAILED;
        }
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
        return E_PAXOSKV_GET_RPC_FAILED;
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

int SliceIndexKVHelper::GetLogicalId(const uint64_t iPhysical, uint64_t &outLogical)
{
    auto sKey = SliceReverseIndexKey(iPhysical);
    ::paxoskv::GetReq  oReq;
    ::paxoskv::GetResp oRsp;
    oReq.set_key(sKey);

    PaxosKVServiceClient oClient;
    auto iRpcRet = oClient.Get(oReq, oRsp);
    if (iRpcRet != 0)
    {
        spdlog::error("SliceIndexKVHelper::GetLogicalId - PaxosKV Get failed, retcode: {}", iRpcRet);
        return E_PAXOSKV_SET_RPC_FAILED;
    }

    auto &oValue = oRsp.value();
    if (oValue.size() != sizeof(outLogical))
    {
        spdlog::error("SliceIndexKVHelper::GetLogicalId - value length not correct, actual: {}, should be: {}", oValue.size(), sizeof(outLogical));
        return E_KV_VALUE_LENGTH_NOT_CORRECT;
    }
    memcpy(&outLogical, oValue.data(), sizeof(outLogical));

    return 0;
}
