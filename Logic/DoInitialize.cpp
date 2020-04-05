#include <cstdlib>
#include <spdlog/spdlog.h>
#include "coredeps/TfcConfigCodec.hpp"

#include "SQLite.hpp"

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
    g_pSqliteDatabase->exec("CREATE TABLE chunks (chunk_id INTEGER PRIMARY KEY, cluster_id INTERGER, machine_id INTERGER, disk_id INTERGER, logical_used INTERGER, actual_used INTERGER, state INTERGER);");
    g_pSqliteDatabase->exec("CREATE INDEX actual_used ON chunks (actual_used);");
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
    // Intialize SQLite
    InitializeSQLite();
    CreateSQLiteTables();
}