/**
 * 2020-03-15
 *
 ************************************************************************
 * This header groups definitions and prototypes related to the database.
 */
#ifndef H__SQL__H
#define H__SQL__H

#include "../types.h"

/******************************* MACROS ********************************/
/*
 * Defintion of generic SQL request.
 */
#define SQLR_ADD_TASK           "INSERT INTO TASK(title, desc, todo_id,"\
                                " created_at, ended_at, status) "\
                                "VALUES('%s', '%s', %d, %d, %d, %d);"
#define SQLR_ADD_TODO           "INSERT INTO TODO(title, desc, "\
                                "created_at, ended_at, status) "\
                                "VALUES('%s', '%s', %d, %d, %d);"
#define SQLR_CREATET_TASK       "CREATE TABLE IF NOT EXISTS TASK("\
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "title VARCHAR(100),"\
                                "desc VARCHAR(255),"\
                                "todo_id INTEGER REFERENCES TODO(id),"\
                                "created_at INTEGER,"\
                                "modified_at INTEGER DEFAULT NULL,"\
                                "ended_at INTEGER,"\
                                "status BOOLEAN"\
                                ");"
#define SQLR_CREATET_TODO       "CREATE TABLE IF NOT EXISTS TODO("\
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"\
                                "title VARCHAR(100),"\
                                "desc VARCHAR(255),"\
                                "created_at INTEGER,"\
                                "modified_at INTEGER DEFAULT NULL,"\
                                "ended_at INTEGER,"\
                                "status BOOLEAN"\
                                ");"
#define SQLR_DELETE_ALL_TAKS    "DELETE FROM TASK WHERE todo_id=%d;"
#define SQLR_DELETE_TASK        "DELETE FROM TASK WHERE id=%d;"
#define SQLR_DELETE_TODO        "DELETE FROM TODO WHERE id=%d;"
#define SQLR_FETCH_TASKS_BY     "SELECT * FROM TASK WHERE todo_id=%d"
#define SQLR_GET_TASK_COUNT     "SELECT count(*) FROM TASK;"
#define SQLR_GET_TODO_COUNT     "SELECT count(*) FROM TODO;"
#define SQLR_UPDATE_TASK_DESC   "UPDATE TASK SET desc='%s' WHERE id=%d;"
#define SQLR_UPDATE_TASK_EDATE  "UPDATE TASK SET ended_at=%d WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TASK_MDATE  "UPDATE TASK SET modified_at=%d WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TASK_STATUS "UPDATE TASK SET status=%d WHERE id=%d;"
#define SQLR_UPDATE_TASK_TITLE  "UPDATE TASK SET title='%s' WHERE id=%d;"
#define SQLR_UPDATE_TODO_DESC   "UPDATE TODO SET desc='%s' WHERE id=%d;"
#define SQLR_UPDATE_TODO_EDATE  "UPDATE TODO SET ended_at='%s'WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TODO_MDATE  "UPDATE TODO SET modified_at=%d WHERE "\
                                "id=%d;"
#define SQLR_UPDATE_TODO_TITLE  "UPDATE TODO SET title='%s' WHERE id=%d;"
#define SQLR_UPDATE_TODO_STATUS "UPDATE TODO SET status=%d WHERE id=%d;"

/*
 * UPDATE FLAGS
 */
#define UPDATE_TITLE            0x001
#define UPDATE_DESC             0x002
#define UPDATE_MDATE            0x004
#define UPDATE_EDATE            0x008
#define UPDATE_STATUS           0x010

#define DBNAME                  "data.db" /* Database name */

/************************* PUBLIC FUNCTIONS ****************************/

/**
 * Display last composed request.
 */
void
displayComposedRequest(void);

/* ------------------------------------------------------------------- */

/**
 * Closes database.
 * 
 * @return DB_CLOSED on success.
 */
enum STATUS_CODE
dbClose(void);

/**
 * Opens database.
 * 
 * @return DB_OPENED on success.
 */
enum STATUS_CODE
dbOpen(void);
/* ------------------------------------------------------------------- */
/**
 * Adds task record to the database.
 * 
 * @param _task: new task to add.
 * @param _todo_id: identifier of todo list.
 * @return TASK_ADDED on success.
 */
enum STATUS_CODE
dbAddTask(const unsigned int _todo_id, const Task _task);

/**
 * Deletes all tasks that belongs to a todo list.
 * 
 * @param _todo_id: identifier of todo list.
 * @return TASK_DELETED on success.
 */
enum STATUS_CODE
dbDeleteAllTasks(const unsigned int _todo_id);

/**
 * Deletes task record from database.
 * 
 * @param _task_id: identifier of task to delete.
 * @return TASK_DELETED on success, ERR_UNKNOW otherwise.
 */
enum STATUS_CODE
dbDeleteTask(const unsigned int _task_id);

/**
 * Gets all tasks that belongs to a todo list.
 * 
 * @param _todo_id: identifier of todo list.
 * @return pointer to the first task or NULL.
 */
Task*
dbFetchAllTasks(const unsigned int _todo_id);

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
dbUpdateTask(const Task _task, const unsigned int _update_flag);

/* ------------------------------------------------------------------- */

/**
 * Adds new todo list to the database.
 * 
 * @param _todolist: new todo list to add.
 * @return TODO_ADDED on success.
 */
enum STATUS_CODE
dbAddTodo(const Todo _todolist);

/**
 * Deletes a todo list from database.
 * 
 * @param _todo_id: identifier of todo list to delete.
 * @return TODO_DELETED on success.
 */
enum STATUS_CODE
dbDeleteTodo(const unsigned int _todo_id);

/**
 * Gets all todo lists from the database.
 * 
 * @return pointer to the first todo or NULL.
 */
Todo*
dbFetchAllTodos(void);

/**
 * Updates todo list record in the database. Uses the second parameter
 * to specify what column(s) update. The second parameter can be a mix
 * of flags.
 * 
 * @param _todolist: todo list to update.
 * @param _update_flag: column(s) to update.
 * @return TODO_UPDATED on success.
 */
enum STATUS_CODE
dbUpdateTodo(const Todo _todolist, const unsigned int _update_flag);

#endif /* H__SQL__H */
