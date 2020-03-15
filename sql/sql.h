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
#define DBNAME          "data.db"
#define UPDATE_TITLE    0x001
#define UPDATE_DESC     0x002
#define UPDATE_MDATE    0x004
#define UPDATE_EDATE    0x008
#define UPDATE_STATUS   0x010

/************************** PRIVATE FUNCTIONS **************************/
/**
 * Closes database.
 * @return DB_CLOSED on success.
 */
static enum STATUS_CODE dbClose(void);

/**
 * Creates valid SQL request from generic sql request passed as first arg
 * @param _generic_request: sql generic req that will be used to create a
 * specialized sql request. The specialized request is available in
 * the global variable sql_req.
 * @return SQLR_COMPOSED on success.
 */
static enum STATUS_CODE
dbComposeRequest(const char* _genetic_request, ...);

/**
 * Initializes database. Creates database and tables(if not exist).
 * @return DB_OPENED on success.
 */
static enum STATUS_CODE dbInit(void);

/**
 * Opens database.
 * @return DB_OPENED on success.
 */
static enum STATUS_CODE dbOpen(void);

/************************* PUBLIC FUNCTIONS ****************************/
/**
 * Adds task record to the database.
 * @param _task: new task to add.
 * @return TASK_ADDED on success.
 */
enum STATUS_CODE dbAddTask(const Task _task);

/**
 * Deletes all tasks that belongs to a todo list.
 * @param _todo_id: identifier of todo list.
 * @return TASK_DELETED on success.
 */
enum STATUS_CODE dbDeleteAllTasks(const unsigned int _todo_id);

/**
 * Deletes task record from database.
 * @param _task_id: identifier of task to delete.
 * @return TASK_DELETED on success.
 */
enum STATUS_CODE dbDeleteTask(const unsigned int _task_id);

/**
 * Gets all tasks that belongs to a todo list.
 * @param _todo_id: identifier of todo list.
 * @return pointer to the first task or NULL.
 */
Task* dbFetchAllTasks(const unsigned int _todo_id);

/**
 * Updates task record in the database. Uses the second parameter
 * to specify what column(s) update. The second parameter can be a mix of
 * flags.
 * @param _task: task to update.
 * @param _update_flag: column(s) to update.
 * @return TASK_UPDATED on success.
 */
enum STATUS_CODE
dbUpdateTask(const Task _task, const unsigned int _update_flag);

/* ------------------------------------------------------------------- */

/**
 * Adds new todo list to the database.
 * @param _todolist: new todo list to add.
 * @return TODO_ADDED on success.
 */
enum STATUS_CODE dbAddTodo(const Todo _todolist);

/**
 * Deletes a todo list from database.
 * @param _todo_id: identifier of todo list to delete.
 * @return TODO_DELETED on success.
 */
enum STATUS_CODE dbDeleteTodo(const unsigned int _todo_id);

/**
 * Gets all todo lists from the database.
 * @return pointer to the first todo or NULL.
 */
Todo* dbFetchAllTodos(void);

/**
 * Updates todo list record in the database. Uses the second parameter
 * to specify what column(s) update. The second parameter can be a mix of
 * flags.
 * @param _todolist: todo list to update.
 * @param _update_flag: column(s) to update.
 * @return TODO_UPDATED on success.
 */
enum STATUS_CODE
dbUpdateTodo(const Todo _todolist, const unsigned int _update_flag);

#endif /* H__SQL__H */