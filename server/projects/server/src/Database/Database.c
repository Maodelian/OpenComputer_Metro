#include <Database/Database.h>

void Database_Open(sqlite3** database)
{
    sqlite3_open("database.db", database);
}
