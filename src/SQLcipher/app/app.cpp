#include "SQLCipherDB.h"

int main()
{
    SQLCipherDB db(
        "plates.db",
        "myStrongPassword123");

    db.createDatabase();

    db.writeRecords();

    db.readRecords();



    // test fail
    /*SQLCipherDB db1(
        "plates.db",
        "vvfvfvdfv");

	db1.readRecords();*/

    return 0;
}