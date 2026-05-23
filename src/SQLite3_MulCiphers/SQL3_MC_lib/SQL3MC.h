#pragma once

#include <string>

/*
 * DLL EXPORT/IMPORT MACRO
 */
#ifdef SQL3MC_EXPORTS
#define SQL3MC_API __declspec(dllexport)
#else
#define SQL3MC_API __declspec(dllimport)
#endif

class SQL3MC_API SQL3_MulCiphers
{
public:
    SQL3_MulCiphers(const std::string& dbName,
        const std::string& password);

    ~SQL3_MulCiphers();

    bool createDatabase();

    bool writeRecords();

    bool readRecords();

private:
    void* m_db;

    std::string m_dbName;

    std::string m_password;

    bool open();

    void close();

    bool execute(const std::string& sql);

    static int callback(void*,
        int argc,
        char** argv,
        char** azColName);
};