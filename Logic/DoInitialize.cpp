#include <spdlog/spdlog.h>
#include "coredeps/TfcConfigCodec.hpp"

AlohaIO::TfcConfigCodec LibConf;

void DoInitialize(const char *apConfFile)
{
    // Parse config file
    spdlog::info("Parsing business library config file...");
    int iRet = LibConf.ParseFile(apConfFile);
    if (iRet != 0)
    {
        throw std::runtime_error(string("Parse config file failed: ").append(apConfFile));
    }
}