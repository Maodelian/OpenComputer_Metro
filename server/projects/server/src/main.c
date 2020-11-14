#include <Socket.h>
#include <Database/Database.h>
#include <Database/travelcard.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int sockfd;
    sqlite3* database;
    int lastid = 1;
    Database_Open(&database);
    if (!Socket_Open(&sockfd)) return -1;
    while (1)
    {
        int fd = accept(sockfd, 0, 0);
        char command[32];
        int argument;
        {
            char buffer[128];
            int length = recv(fd, buffer, 128, 0);
            buffer[length] = '\x00';
            sscanf(buffer, "%s %d", command, &argument);
        }
        if (strcmp(command, "CREATE") == 0)
        {
            struct travelcard_t travelcard;
            {
                travelcard.id = lastid;
                travelcard.count = argument;
            }
            char sql[256];
            travelcard_insert(sql, &travelcard);
            sqlite3_exec(database, sql, 0, 0, 0);
            {
                char buffer[4];
                buffer[0] = (char)((lastid >> 24) & 0xFF);
                buffer[1] = (char)((lastid >> 16) & 0xFF);
                buffer[2] = (char)((lastid >> 8) & 0xFF);
                buffer[3] = (char)(lastid & 0xFF);;
                send(fd, buffer, 4, 0);
            }
            lastid++;
        }
        else if (strcmp(command, "GO") == 0)
        {
            char sql[256];
            char condition[64];
            sprintf(condition, "id = %d", argument);
            travelcard_select(sql, condition);
            sqlite3_stmt *stmt;
            sqlite3_prepare(database, sql, 256, &stmt, 0);
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                struct travelcard_t travelcard;
                travelcard_parse(stmt, &travelcard);
                if (travelcard.count > 0) {
                    travelcard.count--;
                    travelcard_update(sql, &travelcard, condition);
                    sqlite3_exec(database, sql, 0, 0, 0);
                    {
                        send(fd, "OK", 2, 0);
                        char buffer[4];
                        buffer[0] = (char)((travelcard.count >> 24) & 0xFF);
                        buffer[1] = (char)((travelcard.count >> 16) & 0xFF);
                        buffer[2] = (char)((travelcard.count >> 8) & 0xFF);
                        buffer[3] = (char)(travelcard.count & 0xFF);;
                        send(fd, buffer, 4, 0);
                    }
                }
                else
                {
                    send(fd, "EC", 2, 0);
                }
            }
            else
            {
                send(fd, "ER", 2, 0);
            }
            sqlite3_finalize(stmt);
        }
        close(fd);
    }
}
