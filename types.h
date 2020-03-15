/**
 * 2020-03-15
 *
 ************************************************************************
 * This header groups the entire type definitions and macros for this
 * project.
 */
#ifndef H__TYPES__H
#define H__TYPES__H

/******************************* MACROS ********************************/
/*
 * Defintion of generic SQL request.
 */
#define SQLR_ADD_TASK           "INSERT INTO TASK(title, desc, todo_id,"\
                                "created_at, ended_at, status) "\
                                "VALUES(%s, %s, %d, %d, %d, %d);"
#define SQLR_ADD_TODO           "INSERT INTO TODO(title, desc, "\
                                "created_at, ended_at, status) "\
                                "VALUES(%s, %s, %d, %d, %d);"
#define SQLR_CREATET_TASK       "CREATE TABLE IF NOT EXITS TASK("\
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "title VARCHAR(100),"\
                                "desc VARCHAR(255),"\
                                "todo_id INTEGER REFERENCES TODO(id),"\
                                "created_at INTEGER,"\
                                "modified_at INTEGER DEFAULT NULL,"\
                                "ended_at INTEGER,"\
                                "status BOOLEAN"\
                                ");"
#define SQLR_CREATET_TODO       "CREATE TABLE IF NOT EXITS TODO("\
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "title VARCHAR(100),"\
                                "desc VARCHAR(255),"\
                                "created_at INTEGER,"\
                                "modified_at INTEGER DEFAULT NULL,"\
                                "ended_at INTEGER,"\
                                "status BOOLEAN"\
                                ");"
#define SQLR_DELETE_TASK        "DELETE FROM TASK WHERE id=%d;"
#define SQLR_DELETE_TODO        "DELETE FROM TODO WHERE id=%d;"
#define SQLR_GET_TASK_COUNT     "SELECT count(*) FROM TASK;"
#define SQLR_GET_TODO_COUNT     "SELECT count(*) FROM TODO;"
#define SQLR_UPDATE_TASK_DESC   "UPDATE TASK SET desc='%s' WHERE id=%d;"
#define SQLR_UPDATE_TASK_EDATE  "UPDATE TASK SET ended_at=%d WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TASK_MDATE  "UPDATE TASK SET modified_at=%d WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TASK_STATUS "UPDATE TASK SET desc='%s' WHERE id=%d;"
#define SQLR_UPDATE_TASK_TITLE  "UPDATE TASK SET title='%s' WHERE id=%d;"
#define SQLR_UPDATE_TODO_DESC   "UPDATE TODO SET desc='%s' WHERE id=%d;"
#define SQLR_UPDATE_TODO_EDATE  "UPDATE TODO SET ended_at='%s'WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TODO_MDATE  "UPDATE TODO SET modified_at=%d WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TODO_TITLE  "UPDATE TODO SET title='%s' WHERE id=%d;"
#define SQLR_UPDATE_TODO_STATUS "UPDATE TODO SET status=%d WHERE id=%d;"

/*
 * LIMITS OF BUFFERS AND STRING
 */
#define MAX_TITLE               100
#define MAX_DESC                255
#define MAX_TASKS               20
#define SQLR_MAX                512

/*
 * TASK/TODO STATUS
 */
#define STAT_DONE               1
#define STAT_ONPROGRESS         0

/********************** STRUCTURES AND ENUMS ***************************/

/*
 * Represents a task
 */
struct __task
{
    unsigned int id;            /* task identifier */
    char title[MAX_TITLE];      /* task title */
    char desc[MAX_DESC];        /* task description */
    time_t created_at;          /* task creation date */
    time_t modified_at;         /* task last modification date */
    time_t ended_at;            /* task expiration date */
    unsigned short status;      /* task status*/
}

/*
 * Represents a todo list
 */
struct __todo
{
    unsigned int id;            /* todo identifier */
    unsigned int len;           /* todo length. Number of tasks */
    char title[MAX_TITLE];      /* todo title */
    char desc[MAX_DESC];        /* todo description */
    time_t created_at;          /* todo creation date */
    time_t modified_at;         /* todo last modification date */
    time_t ended_at;            /* todo expiration date */
    unsigned short status;      /* todo status */
    struct __task[MAX_TASKS];   /* todo tasks */
}

/*
 * Different status codes for function
 */
enum STATUS_CODE
{
    /* errors */
    ERR_MAX_TASK,
    ERR_MAX_TITLE,
    ERR_MAX_DESC,
    ERR_SQLR_MAX,
    ERR_UNKNOWN,

    /* related to tasks */
    TASK_ADDED,
    TASK_DELETED,
    TASK_UPDATED,

    /* related to todo */
    TODO_ADDED,
    TODO_DELETED,
    TODO_UPDATED,

    /* related to sql */
    SQLR_COMPOSED
}

/************************** TYPE DEFINITIONS ***************************/
typedef struct __task* Task;
typedef struct __todo* Todo;

#endif /* H__TYPES__H */