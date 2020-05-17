#include <sqlite3.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "sql.h"
#include "../tools/memop.h"

/*************************** Global variable ***************************/
static sqlite3 *G_DB = NULL;
static char *G_SQL_ERRMSG;
static char G_SQL_REQ[SQLR_MAX];
static int G_INDEX = 0;

/************************** PRIVATE FUNCTIONS **************************/

/**
 * Creates Task from database information
 * 
 * char** _task_data: task data from database
 */
static Task
createTaskFromDB(char** _task_data)
{
    Task task = (Task) malloc(sizeof(struct __task));
    tools_memop_bzero(task->title, (size_t) MAX_TITLE);
    tools_memop_bzero(task->desc, (size_t) MAX_DESC);
    snprintf(task->title, (MAX_TITLE-1), _task_data[1]);
    snprintf(task->desc, (MAX_DESC-1), _task_data[2]);
    task->id = atoi(_task_data[0]);
    task->created_at = atoi(_task_data[4]);
    task->modified_at = atoi(_task_data[5]);
    task->ended_at = atoi(_task_data[6]);
    task->status = atoi(_task_data[7]);

    return task;
}

/**
 * Creates valid SQL request from generic sql request passed as first arg
 * @param _generic_request: sql generic req that will be used to create a
 * specialized sql request. The specialized request is available in
 * the global variable sql_req.
 * @return SQLR_COMPOSED on success.
 */
static enum STATUS_CODE
dbComposeRequest(const char* _request, ...)
{
    int
    cpy_count = 0,
    n = 0;

    /* clean sql_req memory area */
    tools_memop_bzero(G_SQL_REQ, (sizeof(char) * SQLR_MAX));

    va_list ap;
    va_start(ap, _request);

    while(_request[n])
    {
        if(_request[n] == '%')
        {
            n++;
            switch(_request[n])
            {
                case 's':
                    {
                        const char *string = (const char *) va_arg(ap, const char *);
                        cpy_count += snprintf(
                            (G_SQL_REQ+cpy_count),
                            (SQLR_MAX-cpy_count-1),"%s", string
                        );
                    }
                break;
                case 'd':
                    {
                        int value = (int) va_arg(ap, int);
                        cpy_count += snprintf(
                            (G_SQL_REQ+cpy_count),
                            (SQLR_MAX-cpy_count-1), "%d", value
                        );
                    }
                break;
                default:
                    return ERR_UNKNOWN;
            }
            n++;
        }
        else
        {
            G_SQL_REQ[cpy_count] = *(_request+n);
            n++;
            cpy_count++;
        }

        if(cpy_count >= SQLR_MAX)
        {
            return ERR_SQLR_MAX;
        }
    }

    va_end(ap);
    return SQLR_COMPOSED;
}

/**
 * Initializes database. Creates database and tables(if not exist).
 * @return DB_OPENED on success, ERR_UNKNOWN otherwise
 */
static enum STATUS_CODE
dbInit(void)
{
    if((dbComposeRequest(SQLR_CREATET_TASK)) != SQLR_COMPOSED)
    {
        return ERR_UNKNOWN;
    }

    if((sqlite3_exec(G_DB, G_SQL_REQ, NULL, NULL, &G_SQL_ERRMSG)) != SQLITE_OK)
    {
        return ERR_UNKNOWN;
    }

    if((dbComposeRequest(SQLR_CREATET_TODO)) != SQLR_COMPOSED)
    {
        return ERR_UNKNOWN;
    }

    if((sqlite3_exec(G_DB, G_SQL_REQ, NULL, NULL, &G_SQL_ERRMSG)) != SQLITE_OK)
    {
        return ERR_UNKNOWN;
    }

    return DB_INITIALIZED;
}

/**
 * Generic data base operation performer,
 * 
 * @param _status_code: status code to return on success
 * @param _cb: callback on operation success
 * @param _udata: user data to pass to callback _cb
 * @param _closeDB: close database after request if 1
 * @return _status_code on success, ERR_UNKNOWN otherwise
 */
static enum STATUS_CODE
dbOperationPerform(
    enum STATUS_CODE _status_code,
    int (*_cb)(void*, int, char**, char**),
    void* _udata,
    unsigned int _closeDB
)
{
    int result;

    // stop execution because database cannot be opened
    if(dbOpen() != DB_OPENED)
    {
        return ERR_UNKNOWN;
    }

    G_INDEX = 0;

    printf("Will Perform: ");
    displayComposedRequest();

    result = sqlite3_exec(G_DB, G_SQL_REQ, _cb, _udata, &G_SQL_ERRMSG);
    if(_closeDB)
    {
        dbClose();
    }

    // checks if task is added in the database
    if(result != SQLITE_OK)
    {
        printf("%s", G_SQL_ERRMSG);
        return ERR_UNKNOWN;
    }

    return _status_code;
}

/***************************** CALLBACKS *******************************/

/**
 * Callback for getting count
 */
static int 
getCount(void* _udata, int _col_n, char** _col_val, char** _col_name)
{
    int* count = (int*) _udata;
    *count = atoi(_col_val[0]);
    return 0;
}

/**
 * Callback for creating tasks from result
 */
static int
createTasksFromSQLResult(
    void* _udata, int _col_n,
    char** _col_val, char** _col_name
)
{
    Task* tasks = (Task*) _udata;
    tasks[G_INDEX++] = createTaskFromDB(_col_val);
    return 0;
}

/************************* PUBLIC FUNCTIONS ****************************/

static void
displayComposedRequest(void)
{
    printf("%s\n", G_SQL_REQ);
}
/* ------------------------------------------------------------------- */

enum STATUS_CODE
dbClose(void)
{
    if((sqlite3_close(G_DB)) != SQLITE_OK) { return DB_CLOSED; }
    return ERR_UNKNOWN;
}

enum STATUS_CODE
dbOpen(void)
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
    result = sqlite3_open(DBNAME, &G_DB);
    if(result != SQLITE_OK)
    {
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

enum STATUS_CODE
dbAddTask(const unsigned int _todo_id, const Task _task)
{
    int result;

    // compose request with generic request 'SQLR_ADD_TASK' and parameters
    result = dbComposeRequest(
        SQLR_ADD_TASK,
        _task->title,
        _task->desc,
        _todo_id,
        _task->created_at,
        _task->ended_at,
        _task->status
    );

    // Checks if request composer success
    if(result != SQLR_COMPOSED)
    {
        return ERR_UNKNOWN;
    }

    result = dbOperationPerform(TASK_ADDED, NULL, NULL, 0);

    //
    if(result == TASK_ADDED)
    {
        _task->id = (int) sqlite3_last_insert_rowid(G_DB);
    }

    return result;
}

enum STATUS_CODE
dbDeleteAllTasks(const unsigned int _todo_id)
{
    int result;

    result = dbComposeRequest(SQLR_DELETE_ALL_TAKS, _todo_id);

    // Checks if request composer success
    if(result != SQLR_COMPOSED)
    {
        dbClose();
        return ERR_UNKNOWN;
    }

    return dbOperationPerform(TASK_DELETED, NULL, NULL, 1);
}

enum STATUS_CODE
dbDeleteTask(const unsigned int _task_id)
{
    int result;

    result = dbComposeRequest(SQLR_DELETE_TASK, _task_id);

    // Checks if request composer success
    if(result != SQLR_COMPOSED)
    {
        dbClose();
        return ERR_UNKNOWN;
    }

    return dbOperationPerform(TASK_DELETED, NULL, NULL, 1);
}

Task*
dbFetchAllTasks(const unsigned int _todo_id)
{
    int result, task_count, i;
    Task* tasks = NULL;

    result = dbComposeRequest(SQLR_GET_TASK_COUNT);

    // Checks if request composer success
    if(result != SQLR_COMPOSED)
    {
        return NULL;
    }

    result = dbOperationPerform(SQLR_OP_OK, getCount, &task_count, 1);

    if(result != SQLR_OP_OK)
    {
        return NULL;
    }

    // create arrays of tasks and Null for all fields
    tasks = (Task*) malloc(sizeof(Task)*(task_count+1));
    for(i = 0; i <= task_count; i++)
    {
        tasks[i] = NULL;
    }

    result = dbComposeRequest(SQLR_FETCH_TASKS_BY, _todo_id);

    result = dbOperationPerform(
        SQLR_OP_OK,
        createTasksFromSQLResult,
        tasks,
        1
    );

    return tasks;
}

/**
 * Updates task record in the database. Uses the second parameter
 * to specify what column(s) update. The second parameter can be a mix of
 * flags.
 * 
 * @param _task: task to update.
 * @param _update_flag: column(s) to update.
 * @return TASK_UPDATED on success.
 */
enum STATUS_CODE
dbUpdateTask(const Task _task, const unsigned int _update_flag)
{
    int result;

    // update title
    if((_update_flag & UPDATE_TITLE))
    {
        result = dbComposeRequest(
            SQLR_UPDATE_TASK_TITLE,
            _task->title, _task->id
        );

        result = dbOperationPerform(TASK_UPDATED, NULL, NULL, 1);

        if(result != TASK_UPDATED) { return result; }
    }

    // update description
    if((_update_flag & UPDATE_DESC))
    {
        result = dbComposeRequest(
            SQLR_UPDATE_TASK_DESC,
            _task->desc, _task->id
        );

        result = dbOperationPerform(TASK_UPDATED, NULL, NULL, 1);

        if(result != TASK_UPDATED) { return result; }
    }

    // update modification date
    if((_update_flag & UPDATE_MDATE))
    {
        result = dbComposeRequest(
            SQLR_UPDATE_TASK_MDATE,
            _task->modified_at, _task->id
        );

        result = dbOperationPerform(TASK_UPDATED, NULL, NULL, 1);

        if(result != TASK_UPDATED) { return result; }
    }

    // update end date
    if((_update_flag & UPDATE_EDATE))
    {
        result = dbComposeRequest(
            SQLR_UPDATE_TASK_EDATE,
            _task->ended_at, _task->id
        );

        result = dbOperationPerform(TASK_UPDATED, NULL, NULL, 1);

        if(result != TASK_UPDATED) { return result; }
    }

    // update status
    if((_update_flag & UPDATE_STATUS))
    {
        result = dbComposeRequest(
            SQLR_UPDATE_TASK_STATUS,
            _task->status, _task->id
        );

        result = dbOperationPerform(TASK_UPDATED, NULL, NULL, 1);

        if(result != TASK_UPDATED) { return result; }
    }

    return result;
}

// enum STATUS_CODE
// dbDeleteTodo(const unsigned int _todo_id)
// {
//     return TODO_DELETED;
// }
