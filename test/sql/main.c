#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sql.h"
#include "types.h"
#include "uint_test.h"
#include "memop.h"

static const int CONST_TODO_ID = 0;

uint8_t unitTestAddTask(void)
{
    Task task1 = new(sizeof(struct __task_t));

    snprintf((char *)task1->title, (MAX_TITLE - 1), "%s", "Learn new skill");
    snprintf((char *)task1->desc, (MAX_DESC - 1), "%s", "Learning new thing every days");
    task1->created_at = 7899477;
    task1->ended_at = 7899499;
    task1->status = 0;

    if(TASK_ADDED != dbAddTask(CONST_TODO_ID, task1))
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t unitTestOpenDB(void)
{
    if (DB_OPENED != dbOpen())
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t unitTestCloseDB(void)
{
    if (DB_CLOSED != dbClose())
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t unitTestDeleteTask(void)
{
    if(TASK_DELETED != dbDeleteTask(2))
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t unitTestDeleteAllTasks(void)
{
    if(TASK_DELETED != dbDeleteAllTasks(CONST_TODO_ID))
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t unitTestFetchAllTasks(void)
{
    size_t i;
    uint32_t task_count = 0;
    Task* Tasks = dbFetchAllTasks(CONST_TODO_ID, &task_count);

    if(task_count == 0)
    {
        return FALSE;
    }

    for(i = 0; i < task_count; i++)
    {
        printf("Task title: %s\n", Tasks[i]->title);
    }

    return TRUE;
}

int main(void)
{

    addUnitTest(unitTestOpenDB, "OpenDB");
    addUnitTest(unitTestCloseDB, "CloseDB");
    addUnitTest(unitTestAddTask, "dbAddTask");
    addUnitTest(unitTestDeleteTask, "dbDeleteTask");
    addUnitTest(unitTestFetchAllTasks, "dbFetchAllTasks");
    addUnitTest(unitTestDeleteAllTasks, "dbDeleteAllTasks");

    launchUnitTests();
    displayUnitTestReports();

    return 0;
}