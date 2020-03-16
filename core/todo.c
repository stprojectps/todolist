#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../sql/sql.h"
#include "task.h"
#include "todo.h"


Todo todoInit(void)
{
    Todo _todo = (Todo) malloc(sizeof(struct __todo));

    _todo->id               = 0;
    _todo->len              = 0;
    _todo->created_at       = 0;
    _todo->modified_at      = 0;
    _todo->ended_at         = 0;
    _todo->status           = 0;
    return _todo;
}

enum STATUS_CODE todoDestroy(Todo _todo)
{
    if (_todo)
    {
        free(_todo);
        return TODO_DESTROYED;
    }

    return ERR_TODO;
}

enum STATUS_CODE todoDelete(Todo _todo)
{
    if (_todo)
    {
        if (dbDeleteTodo(_todo->id) == TODO_DELETED)
        {
            todoDestroy(_todo);
            return TODO_DELETED;
        }
    } 

    return ERR_TODO;
}

enum STATUS_CODE todoSetTitle(Todo _todo, const char* _title)
{
    if (_todo)
    {
        strncpy(_todo->title,_title,MAX_TITLE);
        return TODO_UPDATED;
    }

    return ERR_TODO;
}

enum STATUS_CODE todoSetDesc(Todo _todo, const char* _desc)
{
    if (_todo)
    {
        strncpy(_todo->desc,_desc,MAX_DESC);
        return TODO_UPDATED;
    }

    return ERR_TODO;
}

enum STATUS_CODE todoSetCreatedAt(Todo _todo, const time_t _created_at)
{
    if (_todo)
    {
        _todo->created_at = _created_at;
        return TODO_UPDATED;
    }

    return ERR_TODO;
}

enum STATUS_CODE todoSetDeadline(Todo _todo, const time_t _deadline)
{
    if (_todo)
    {
        _todo->ended_at = _deadline;
        return TODO_UPDATED;
    }

    return ERR_TODO;
}

enum STATUS_CODE todoSetStatus(Todo _todo, const int _status)
{
    if (_todo)
    {
        _todo->status = _status;
        return TODO_UPDATED;
    }

    return ERR_TODO;
}

enum STATUS_CODE todoAddTask(Todo _todo, const Task _task)
{
    if (_todo && _task)
    {
        if (dbAddTask(_task))
        {
            _todo->tasks[_todo->len] = *_task;
            _todo->len += 1;
            return TASK_ADDED;
        }
    }

    return ERR_TODO;
}

enum STATUS_CODE todoDeleteTask(Todo _todo, const Task _task)
{
    int task_found = 0;
    if (_todo && _task)
    {
        for (int i = 1; i < _todo->len; i++)
        {
            if (_todo->tasks[i].id == _task->id)
            {
                task_found = 1;
                for (int k = i+1; k < _todo->len; k++)
                {
                    _todo->tasks[i] = _todo->tasks[k];
                    i++;
                }
                break;
            }
        }
        if (_todo->tasks[0].id == _task->id || task_found == 1)
        {
            if (dbDeleteTask(_task->id) == TASK_DELETED)
            {
                _todo->len -= 1;
                return TODO_UPDATED;
            }
        }
    }

    return ERR_TODO;
}

enum STATUS_CODE todoDeleteTasks(Todo _todo)
{
    Task T = taskInit(NULL);
    if ((T && _todo) != NULL && dbDeleteAllTasks(_todo->id) == TASK_DELETED)
    {
        for (int i = 0; i < _todo->len; i++)
        {
            _todo->tasks[i] = *T;
        }
        _todo->len = 0;
        return TODO_UPDATED;
    }

    return ERR_TODO;
}