# Description

This file represents the project roadmap.

It contains:
 - sql instructions for database creation
 - function prototypes to be implemented

The roadmap is divided into three big parts:
 - [Part 1](#backend): business logic (backend)
 - Part 2: graphical interface (ui)
 - Part 3: binding backend and ui (binding)

<br/>
<br/>

# <a name="backend"></a>PART 1: Backend

This part is focus in the business logic. The ways that that data are created, manipulated, stored and deleted are handled in this part.

<br/>

## SQL Statements

<br/>

### Statements for table creation

<br/>

```c
#define "CREATE TABLE IF NOT EXISTS TODO("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "title VARCHAR(100),"
            "desc VARCHAR(255),"
            "created_at INTEGER,"
            "modified_at INTEGER,"
            "ended_at INTEGER,"
            "status BOOLEAN"
        ");"

#define "CREATE TABLE IF NOT EXISTS TASK("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "title VARCHAR(100),"
            "desc VARCHAR(255),"
            "todo_id INTEGER REFERENCES TODO(id),"
            "created_at INTEGER,"
            "modified_at INTEGER,"
            "ended_at INTEGER,"
            "status BOOLEAN,"
        ");"
```

<br/>

### Request statements

<br/>

```c

```

<br/>

## Data Structures

<br/>

```c
/* Structure Todo */

struct __todo{
    unsigned int    id;
    unsigned int    len;
    char            title[100];
    char            desc[255];
    time_t          created_at;
    time_t          modified_at;
    time_t          ended_at;
    unsigned short  status;
    Task            tasks[20];
}
typedef struct __todo* Todo;

/* Structure Task */

struct __task{
    unsigned int    id;
    char            title[100];
    char            desc[255];
    time_t          created_at;
    time_t          modified_at;
    time_t          ended_at;
    unsigned short  status;
}
typedef struct __task* Task;

/* Status code */

enum STATUS_CODE {
    ERR_MAX_TASK,
    ERR_MAX_TITLE,
    ERR_MAX_DESC,
    ERR_SQLR_MAX,
    ERR_TODO,
    ERR_TASK,
    ERR_UNKNOWN,
    TASK_ADDED,
    TASK_DELETED,
    TASK_UPDATED,
    TASK_DESTROYED,
    TODO_ADDED,
    TODO_DESTROYED,
    TODO_UPDATED,
    SQLR_COMPOSED,
    SQLR_OP_OK,
    DB_CLOSED,
    DB_INITIALIZED,
    DB_OPENED
}
```

## Database operation functions

<br/>


- [x] Function that composes sql request. The sql request is a format string. For the format string %s and %d are supported.
    ```c
    static enum STATUS_CODE dbComposeRequest(const char*, ...);
    ```

- [x] Function that initializes database.
    ```c
    static enum STATUS_CODE dbInit(void);
    ```

- [x] Function to open  database and creates it if it does not exist
    ```c
    enum STATUS_CODE dbOpen(void);
    ```

- [x] Function to close database
    ```c
    enum STATUS_CODE dbClose(void);
    ```


- [x] Function to add a Task
    ```c
    enum STATUS_CODE dbAddTask(const unsigned int, const Task);
    ```

- [x] Function to update a Task
    ```c
    enum STATUS_CODE dbUpdateTask(const Task, const unsigned int);
    ```

- [x] Function to delete a Task
    ```c
    enum STATUS_CODE dbDeleteTask(const unsigned int);
    ```

- [x] Function to delete all Todo's Tasks
    ```c
    enum STATUS_CODE dbDeleteAllTasks(const unsigned int);
    ```

- [x] Function to fetch all Todo's tasks
    ```c
    Task* dbFetchAllTasks(const unsigned int);
    ```

- [ ] Function to add a Todo
    ```c
    enum STATUS_CODE dbAddTodo(const Todo);
    ```

- [ ] Function to update a Todo
    ```c
    enum STATUS_CODE dbUpdateTodo(const Todo, const unsigned int);
    ```

- [ ] Function to delete a Todo
    ```c
    enum STATUS_CODE dbDeleteTodo(const unsigned int);
    ```

- [ ] Function to select all Todos
    ```c
    Todo* dbFetchAllTodos(void);
    ```

## Core Functionalities

<br/>

### Todo functions

<br/>

- [x] Function to initialize a Todo
    ```c
    Todo todoInit();
    ```

- [x] Function to destroy a Todo in memory
    ```c
    enum STATUS_CODE todoDestroy(Todo);
    ```

- [x] Function to delete a Todo
    ```c
    enum STATUS_CODE todoDelete(Todo);
    ```

- [x] Function to set a Todo title
    ```c
    enum STATUS_CODE todoSetTitle(Todo, const char*);
    ```

- [x] Function to set a Todo description
    ```c
    enum STATUS_CODE todoSetDesc(Todo, const char*);
    ```

- [x] Function to set the creation date of a Todo
    ```c
    enum STATUS_CODE todoSetCreatedAt(Todo, const time_t);
    ```

- [x] Function to set the modification date of a Todo
    ```c
    enum STATUS_CODE todoSetModifiedAt(Todo, const time_t);
    ```

- [x] Function to set the deadline a Todo
    ```c
    enum STATUS_CODE todoSetDeadline(Todo, const time_t);
    ```

- [x] Function to set a Todo status
    ```c
    enum STATUS_CODE todoSetStatus(Todo, const int);
    ```

- [x] Function to set a Todo length
    ```c
    enum STATUS_CODE todoSetLength(Todo, const unsigned int);
    ```

- [x] Function to add a Todo task
    ```c
    enum STATUS_CODE void todoAddTask(Todo, const Task);
    ```

- [x] Function to delete a Todo task
    ```c
    enum STATUS_CODE todoDeleteTask(Todo, Task);
    ```

<br/>

### Task functions

<br/>

- [x] Function to initialize a Task
    ```c
    Task taskInit();
    ```

- [x] Function to destroy a Task in memory
    ```c
    enum STATUS_CODE taskDestroy(Task);
    ```

- [x] Function to delete a Task
    ```c
    enum STATUS_CODE taskDelete(Todo);
    ```

- [x] Function to set a Task title
    ```c
    enum STATUS_CODE taskSetTitle(Task, const char*);
    ```

- [x] Function to set a Task description
    ```c
    enum STATUS_CODE taskSetDesc(Task, const char*);
    ```

- [x] Function to set the creation date of a Task
    ```c
    enum STATUS_CODE taskSetCreatedAt(Task, const time_t);
    ```

- [x] Function to set the modification date of a Task
    ```c
    enum STATUS_CODE taskSetModifiedAt(Task, const time_t);
    ```

- [x] Function to set the deadline a Task
    ```c
    enum STATUS_CODE taskSetDeadline(Task, const time_t);
    ```

- [x] Function to set a Task status
    ```c
    enum STATUS_CODE todoSetStatus(Todo, const int);
    ```
