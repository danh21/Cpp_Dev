#include <iostream>

#include "SQL3MC.h"

int main()
{
    SQL3_MulCiphers db(
        "plates.db",
        "myStrongPassword123");

    /*
     * CREATE DATABASE
     */
    if (!db.createDatabase())
    {
        std::cout
            << "createDatabase failed"
            << std::endl;

        return -1;
    }

    /*
     * WRITE RECORDS
     */
    if (!db.writeRecords())
    {
        std::cout
            << "writeRecords failed"
            << std::endl;

        return -1;
    }

    std::cout << std::endl;

    /*
     * READ RECORDS
     */
    if (!db.readRecords())
    {
        std::cout
            << "readRecords failed"
            << std::endl;

        return -1;
    }



    /*
	 * TEST FAILURE CASE BECAUSE OF WRONG PASSWORD
     */
    /*SQL3_MulCiphers db_fail(
        "plates.db",
        "sdcsdincsk");

    if (!db_fail.readRecords())
    {
        std::cout
            << "readRecords failed"
            << std::endl;

        return -1;
    }*/

    return 0;
}