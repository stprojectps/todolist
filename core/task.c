#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../sql/sql.h"
#include "task.h"


Task taskInit(Task _task)
{
    if (_task == NULL)
    {
        printf("pointeur existant \n");
        Task _task = (Task) malloc(sizeof(struct __task));
        _task->id               = 0;
        _task->created_at       = 0;
        _task->modified_at      = 0;
        _task->ended_at         = 0;
        _task->status           = 0;
        return _task;
    }
    free(_task);
    return NULL;
}

enum STATUS_CODE taskDestroy(Task _task)
{
    if (_task)
    {
        taskInit(_task);
        return TASK_DESTROYED;
    }

    return ERR_TASK;
}

enum STATUS_CODE taskDelete(Task _task)
{
    if (_task)
    {
        if (dbDeleteTask(_task->id) == TASK_DELETED)
        {
            taskDestroy(_task);
            return TASK_DELETED;
        }
    } 

    return ERR_TASK;
}

enum STATUS_CODE taskSetTitle(Task _task, const char* _title)
{
    if (_task)
    {
        strncpy(_task->title,_title,MAX_TITLE);
        return TASK_UPDATED;
    }

    return ERR_TASK;
}

enum STATUS_CODE taskSetDesc(Task _task, const char* _desc)
{
    if (_task)
    {
        strncpy(_task->desc,_desc,MAX_DESC);
        return TASK_UPDATED;
    }

    return ERR_TASK;
}

enum STATUS_CODE taskSetCreatedAt(Task _task, const time_t _created_at)
{
    if (_task)
    {
        _task->created_at = _created_at;
        return TASK_UPDATED;
    }

    return ERR_TASK;
}

enum STATUS_CODE taskSetModifiedAt(Task _task, const time_t _modified_at)
{
    if (_task)
    {
        _task->modified_at = _modified_at;
        return TASK_UPDATED;
    }

    return ERR_TASK;
}

enum STATUS_CODE taskSetDeadline(Task _task, const time_t _deadline)
{
    if (_task)
    {
        _task->ended_at = _deadline;
        return TASK_UPDATED;
    }

    return ERR_TASK;
}

enum STATUS_CODE taskSetStatus(Task _task, const int _status)
{
    if (_task)
    {
        _task->status = _status;
        return TASK_UPDATED;
    }

    return ERR_TASK;
}