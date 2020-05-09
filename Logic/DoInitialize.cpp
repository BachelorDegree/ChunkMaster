#include <cstdlib>
#include <spdlog/spdlog.h>
#include "coredeps/TfcConfigCodec.hpp"

#include "SQLite.hpp"
#include "Global.hpp"

AlohaIO::TfcConfigCodec LibConf;

static void InitializeSQLite(void)
{
    // Check config
    if (!LibConf.HasKV("root\\sqlite", "path"))
        throw std::invalid_argument("Config file doesn't have `root\\sqlite\\path`");
    auto sPath = LibConf.GetKV("root\\sqlite", "path");
    // Clear previous data
    auto sCommand = fmt::format("rm -rf {}/*", sPath);
    spdlog::info("Run system(): {}", sCommand);
    system(sCommand.c_str());
    // Create SQLite DB
    g_pSqliteDatabase = new SQLite::Database(fmt::format("{}/chunkmaster.db3", sPath), SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    g_pSqliteDatabase->exec("PRAGMA synchronous = OFF;");
}

static void CreateSQLiteTables(void)
{
    g_pSqliteDatabase->exec("CREATE TABLE chunks (chunk_id INTEGER PRIMARY KEY, cluster_id INTEGER, machine_id INTEGER, disk_id INTEGER, logical_used INTEGER, actual_used INTEGER, state INTEGER);");
    g_pSqliteDatabase->exec("CREATE INDEX actual_used ON chunks (actual_used);");
}

static void InitializeGlobalVariables(void)
{
    g_pMutexAllChunk = new libco::CoMutex;
}

void DoInitialize(const char *apConfFile)
{
    // Parse config file
    spdlog::info("Parsing business library config file...");
    int iRet = LibConf.ParseFile(apConfFile);
    if (iRet != 0)
    {
        throw std::runtime_error(string("Parse config file failed: ").append(apConfFile));
    }

    // Initialize global vars
    InitializeGlobalVariables();

    // Intialize SQLite
    InitializeSQLite();
    CreateSQLiteTables();
}
