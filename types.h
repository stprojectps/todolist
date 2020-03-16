/**
 * 2020-03-15
 *
 ************************************************************************
 * This header groups the entire type definitions and macros for this
 * project.
 */
#ifndef H__TYPES__H
#define H__TYPES__H

#include <time.h>

/******************************* MACROS ********************************/

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

/**
 *@brief Represents a task
 *
 */
struct __task
{
    unsigned int id;                    /* task identifier */
    char title[MAX_TITLE];              /* task title */
    char desc[MAX_DESC];                /* task description */
    time_t created_at;                  /* task creation date */
    time_t modified_at;                 /* task last modification date */
    time_t ended_at;                    /* task expiration date */
    unsigned short status;              /* task status*/
};

/**
 *@brief Represents a todo list
 */
struct __todo
{
    unsigned int id;                    /* todo identifier */
    unsigned int len;                   /* todo length. Number of tasks */
    char title[MAX_TITLE];              /* todo title */
    char desc[MAX_DESC];                /* todo description */
    time_t created_at;                  /* todo creation date */
    time_t modified_at;                 /* todo last modification date */
    time_t ended_at;                    /* todo expiration date */
    unsigned short status;              /* todo status */
    struct __task tasks[MAX_TASKS];     /* todo tasks */
};

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
    ERR_TODO,

    /* related to tasks */
    TASK_ADDED,
    TASK_DELETED,
    TASK_UPDATED,

    /* related to todo */
    TODO_ADDED,
    TODO_DELETED,
    TODO_UPDATED,
    TODO_DESTROYED,

    /* related to DB*/
    DB_CLOSED,
    DB_INITIALIZED,
    DB_OPENED,

    /* related to sql */
    SQLR_COMPOSED
};

/************************** TYPE DEFINITIONS ***************************/
typedef struct __task* Task;
typedef struct __todo* Todo;

#endif /* H__TYPES__H */
