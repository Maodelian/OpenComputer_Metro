#include <Database/travelcard.h>
#include <stdio.h>

void travelcard_insert(char* sql, struct travelcard_t* travelcard)
{
    sprintf(sql, "INSERT INTO travelcard VALUES (%d, %d);", travelcard->id, travelcard->count);
}

void travelcard_select(char* sql, char* condition)
{
    sprintf(sql, "SELECT * FROM travelcard WHERE %s;", condition);
}

void travelcard_update(char* sql, struct travelcard_t* travelcard, char* condition)
{
    sprintf(sql, "UPDATE travelcard SET id = %d, count = %d WHERE %s;", travelcard->id, travelcard->count, condition);
}

void travelcard_parse(sqlite3_stmt* stmt, struct travelcard_t* travelcard)
{
    travelcard->id = sqlite3_column_int(stmt, 0);
    travelcard->count = sqlite3_column_int(stmt, 1);
}
