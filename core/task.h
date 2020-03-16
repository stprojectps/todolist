/****************************************************************************
 * Copyright (C) 2020 by SARR Pape Moussa & TAMBADOU Sidy
 *
 * This file is part of TodoList.
 *
 *   TodoList is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by STPROJECTPS, either version 1 of the License, or
 *   (at your option) any later version.
 *   ToDo list can be used to create, edit and remove ToDos.
 *   A Todo is characterized by his identifiant, title, the date of creation,
 *   his status and the tasks to do. The status of Todo shows if the Todo 
 *   is completed or notTodos may not have tasks and can have many tasks.
 *   Task also can be created, edited, removed and marked as done as a Todo
 *
 ****************************************************************************/

/**
 * @file task.h
 * @authors SARR Pape Moussa & TAMBADOU Sidy
 * @date 17 March 2020
 * @brief File containing task usage for quick reference.
 * 
 */

#ifndef H_TASK_H
#define H_TASK_H

#include <time.h>
#include "../types.h"


/**
 * @brief initialize a Task.
 *
 * Allocates memory to variable @p _task and initializes @c _task->id ,
 *  @c _task->created_at , @c _task->modified_at ,@c _task->ended_at 
 * and @c _task->status to 0 if this one is @c NULL otherwise @c NULL is returned. 
 * It returns @c Task.
 * @code
 * Task _task = taskInit();
 * @endcode
 * @param _task A Task || @c NULL
 * @return @c Task is always returned
 */
Task taskInit(Task _task);

/**
 * @brief destroy a Task in memory
 * 
 * Desalocates memory of @param _task.if it is not @c NULL
 * @code 
 * if (taskDestroy(_task) == TASK_DESTROYED)
 * {
 *    //Do something
 * }
 * else
 * {
 *    //Do something
 * }
 * @endcode
 * @param _task A Task
 * @return @c STATUS_CODE ( @c TASK_DESTROYED || @c ERR_TASK) is always returned.
 */ 
enum STATUS_CODE taskDestroy(Task _task);

/**
 * @brief set a Task title.
 * 
 * 
 * @param _task A Task.
 * @param _title an constant @c char* to assign to the Title of @p _task
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE taskSetTitle(Task _task, const char* _title);

/**
 * @brief set a Task description.
 * 
 * 
 * @param _task A Task.
 * @param _desc an constant @c char* to assign to the Description of @p _task
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE taskSetDesc(Task _task, const char* _desc);

/**
 * @brief set the creation date of a Task.
 * 
 * 
 * @param _task A Task.
 * @param _created_at an constant @c time_t to assign to the Creation date of @p _task
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE taskSetCreatedAt(Task _task, const time_t _created_at);

/**
 * @brief set the deadline of a Task.
 * 
 * 
 * @param _task A Task.
 * @param _deadline an constant @c time_t to assign to the Deadline of @p _task
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE taskSetDeadline(Task _task, const time_t _deadline);

/**
 * @brief set a Task status.
 * 
 * 
 * @param _task A Task.
 * @param _status an constant @c int to assign to status of @p _task. (1 if it's completed, 0 otherwise)
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE taskSetStatus(Task _task, const int _status);

#endif //H_TASK_H