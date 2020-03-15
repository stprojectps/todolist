#include <sqlite3.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "sql.h"
#include "../tools/tools.h"

/*************************** Global variable ***************************/
static sqlite3 *db = NULL;
static char *sql_errmsg;
static char sql_req[SQLR_MAX];

/************************** PRIVATE FUNCTIONS **************************/
static enum STATUS_CODE
dbComposeRequest(const char* _genetic_request, ...)
{
    int
    cpy_count,
    n = 0;

    /* clean sql_req memory area */
    tools_memop_bzero(sql_req, (sizeof(char) * SQLR_MAX));

    va_list ap;
    va_start(ap, _genetic_request);

    while(_genetic_request[n])
    {
        if(_genetic_request[n] == '%')
        {
            n++;
            switch(_genetic_request[n])
            {
                case 's':
                    cpy_count += snprintf((sql_req+cpy_count), (SQLR_MAX-cpy_count-1),"%s", va_arg(ap, char *));
                break;
                case 'd':
                    cpy_count += snprintf((sql_req+cpy_count), (SQLR_MAX-cpy_count-1),"%d", va_arg(ap, int));
                break;
            }
            n++;
        }
        else
        {
            sql_req[cpy_count] = *(_genetic_request+n);
            n++;
            cpy_count++;
        }
    }

    va_end(ap);
    return SQLR_COMPOSED;
}

static enum STATUS_CODE dbInit(void)
{
    int result;

    if((dbComposeRequest(SQLR_CREATET_TASK)) != SQLR_COMPOSED)
    {
        printf("");
        return ERR_UNKNOWN;
    }

    if((sqlite3_exec(db, sql_req, NULL, NULL, &sql_errmsg)) != SQLITE_OK)
    {
        return ERR_UNKNOWN;
    }

    if((dbComposeRequest(SQLR_CREATET_TODO)) != SQLR_COMPOSED)
    {
        return ERR_UNKNOWN;
    }

    if((sqlite3_exec(db, sql_req, NULL, NULL, &sql_errmsg)) != SQLITE_OK)
    {
        return ERR_UNKNOWN;
    }
    
    return DB_INITIALIZED;
}

/************************* PUBLIC FUNCTIONS ****************************/
enum STATUS_CODE dbClose(void)
{
    if((sqlite3_close(db)) != SQLITE_OK) { return DB_CLOSED; }
    return ERR_UNKNOWN;
}

enum STATUS_CODE dbOpen(void)
{
    int
    result,
    init;
    FILE* fp;
    fp = fopen(DBNAME, "r");

    /* DATABASE DOES NOT EXIST SO NOT INITIALIZED */
    if(fp == NULL)
    {
        init = 0;
    }
    else
    {
        init = 1;
        fclose(fp);
    }

    /* Open/Create database */
    result = sqlite3_open(DBNAME, &db);
    if(result != SQLITE_OK)
    {
        printf("Failed to opened database\n");
        return ERR_UNKNOWN;
    }

    /* Initializes database */
    if(!init)
    {
        return (dbInit() == DB_INITIALIZED) ? DB_OPENED : ERR_UNKNOWN;
    }

    return DB_OPENED;
}

/* ------------------------------------------------------------------- */