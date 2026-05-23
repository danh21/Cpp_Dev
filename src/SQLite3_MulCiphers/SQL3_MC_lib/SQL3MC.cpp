#include <sqlite3mc.h>
#include "SQL3MC.h"

#include <iostream>

SQL3_MulCiphers::SQL3_MulCiphers(
    const std::string& dbName,
    const std::string& password)
    :
    m_db(nullptr),
    m_dbName(dbName),
    m_password(password)
{
}

SQL3_MulCiphers::~SQL3_MulCiphers()
{
    close();
}

/*=========================================================
 * OPEN DATABASE
 *========================================================*/
bool SQL3_MulCiphers::open()
{
    int rc = sqlite3_open(m_dbName.c_str(),
        reinterpret_cast<sqlite3**>(&m_db));

    if (rc != SQLITE_OK)
    {
        std::cout
            << "Cannot open database"
            << std::endl;

        return false;
    }

    /*
     * APPLY PASSWORD
     */
    sqlite3_key(reinterpret_cast<sqlite3*>(m_db),
        m_password.c_str(),
        (int)m_password.length());

    /*
     * SQLITE3MC FEATURE
     */
    execute("PRAGMA cipher='aes256cbc';");

    return true;
}

/*=========================================================
 * CLOSE DATABASE
 *========================================================*/
void SQL3_MulCiphers::close()
{
    if (m_db)
    {
        sqlite3_close(reinterpret_cast<sqlite3*>(m_db));

        m_db = nullptr;
    }
}

/*=========================================================
 * EXECUTE SQL
 *========================================================*/
bool SQL3_MulCiphers::execute(
    const std::string& sql)
{
    char* errMsg = nullptr;

    int rc = sqlite3_exec(reinterpret_cast<sqlite3*>(m_db),
        sql.c_str(),
        nullptr,
        nullptr,
        &errMsg);

    if (rc != SQLITE_OK)
    {
        std::cout
            << "SQL error: "
            << errMsg
            << std::endl;

        sqlite3_free(errMsg);

        return false;
    }

    return true;
}

/*=========================================================
 * CREATE DATABASE/TABLE
 *========================================================*/
bool SQL3_MulCiphers::createDatabase()
{
    if (!open())
    {
        return false;
    }

    bool status = execute(
        "CREATE TABLE IF NOT EXISTS plates ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "plate TEXT NOT NULL,"
        "date TEXT NOT NULL);");

    close();

    return status;
}

/*=========================================================
 * WRITE RECORDS
 *========================================================*/
bool SQL3_MulCiphers::writeRecords()
{
    if (!open())
    {
        return false;
    }

    /*
     * SAMPLE PLATE DATA
     */
    const char* plates[10] =
    {
        "51A-12345",
        "52B-67890",
        "43C-11111",
        "60D-22222",
        "29E-33333",
        "30F-44444",
        "61G-55555",
        "72H-66666",
        "88K-77777",
        "99L-88888"
    };

    const char* dates[10] =
    {
        "2026-05-23 08:00:00",
        "2026-05-23 08:10:00",
        "2026-05-23 08:20:00",
        "2026-05-23 08:30:00",
        "2026-05-23 08:40:00",
        "2026-05-23 08:50:00",
        "2026-05-23 09:00:00",
        "2026-05-23 09:10:00",
        "2026-05-23 09:20:00",
        "2026-05-23 09:30:00"
    };

    /*
     * INSERT 10 RECORDS
     */
    for (int i = 0; i < 10; i++)
    {
        std::string sql =
            "INSERT INTO plates(plate, date) VALUES('"
            + std::string(plates[i])
            + "', '"
            + std::string(dates[i])
            + "');";

        if (!execute(sql))
        {
            close();

            return false;
        }
    }

    std::cout
        << "Inserted 10 plate records."
        << std::endl;

    close();

    return true;
}

/*=========================================================
 * CALLBACK
 *========================================================*/
int SQL3_MulCiphers::callback(
    void*,
    int argc,
    char** argv,
    char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout
            << azColName[i]
            << " = "
            << (argv[i] ? argv[i] : "NULL")
            << std::endl;
    }

    std::cout
        << "----------------------"
        << std::endl;

    return 0;
}

/*=========================================================
 * READ RECORDS
 *========================================================*/
bool SQL3_MulCiphers::readRecords()
{
    if (!open())
    {
        return false;
    }

    char* errMsg = nullptr;

    int rc = sqlite3_exec(reinterpret_cast<sqlite3*>(m_db),
        "SELECT * FROM plates;",
        callback,
        nullptr,
        &errMsg);

    if (rc != SQLITE_OK)
    {
        std::cout
            << "Read failed: "
            << errMsg
            << std::endl;

        sqlite3_free(errMsg);

        close();

        return false;
    }

    close();

    return true;
}