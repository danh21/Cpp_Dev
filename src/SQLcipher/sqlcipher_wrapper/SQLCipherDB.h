#pragma once

#include <string>

#ifdef SQLCIPHERWRAPPER_EXPORTS
#define SQLCIPHER_API __declspec(dllexport)
#else
#define SQLCIPHER_API __declspec(dllimport)
#endif

class SQLCIPHER_API SQLCipherDB
{
public:
    SQLCipherDB(const std::string& dbName,
        const std::string& password);

    ~SQLCipherDB();

    bool createDatabase();

    bool writeRecords();

    bool readRecords();

private:
    void* m_db;

    std::string m_dbName;

    std::string m_password;

private:
    bool open();

    void close();

    bool execute(const std::string& sql);

    static int callback(void*,
        int argc,
        char** argv,
        char** azColName);
};