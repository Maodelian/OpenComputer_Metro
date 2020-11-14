#ifndef METRO_DATABASE_TRAVELCARD_H
#define METRO_DATABASE_TRAVELCARD_H
#include <Database/Database.h>

struct travelcard_t
{
    int id;
    int count;
};

void travelcard_insert(char* sql, struct travelcard_t* travelcard);

void travelcard_select(char* sql, char* condition);

void travelcard_update(char* sql, struct travelcard_t* travelcard, char* condition);

void travelcard_parse(sqlite3_stmt* stmt, struct travelcard_t* travelcard);

#endif
