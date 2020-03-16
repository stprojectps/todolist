/****************************************************************************
 * Copyright (C) 2020 by SARR Pape Moussa & TAMBADOU Sidy
 *
 * This file is part of Box.
 *
 *   Box is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 ****************************************************************************/

/**
 * @file todo.h
 * @authors SARR Pape Moussa & TAMBADOU Sidy
 * @date 15 March 2020
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://
 */

#ifndef H_TODO_H
#define H_TODO_H

#include <time.h>
#include "../types.h"


/**
 * @brief initialize a Todo.
 *
 * Allocates memory to variable @c _todo and initializes @c _todo->id ,
 * @c _todo->len , @c _todo->created_at , @c _todo->modified_at ,
 * @c _todo->ended_at , and @c _todo->status to 0.
 * It returns @c Todo.
 * @code
 * Todo _todo = todoInit();
 * @endcode
 * @return @c Todo is always returned
 */
Todo todoInit(void);

/**
 * @brief destroy a Todo in memory
 * 
 * Desalocates memory of @param _todo.if it is not @c NULL
 * @code 
 * if (todoDestroy(_todo) == TODO_DESTROYED)
 * {
 *    //Do something
 * }
 * else
 * {
 *    //Do something
 * }
 * @endcode
 * @param _todo A Todo
 * @return @c STATUS_CODE ( @c TODO_DESTROYED || @c ERR_TODO) is always returned.
 */ 
enum STATUS_CODE todoDestroy(Todo _todo);

/**
 * @brief delete a Todo
 *
 * Deletes @param _todo on database and desalocates it's memory if it is not @c NULL
 * @code 
 * if (todoDelete(_todo) == TODO_DELETED)
 * {
 *    //Do something
 * }
 * else
 * {
 *    //Do something
 * }
 * @endcode
 * @param _todo A Todo
 * @return @c STATUS_CODE ( @c TODO_DELETED || @c ERR_TODO) is always returned.
 */
enum STATUS_CODE todoDelete(Todo _todo);

/**
 * @brief set a Todo title.
 * 
 * 
 * @param _todo A Todo.
 * @param _title an constant @c char* to assign to the Title of @p _todo
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE todoSetTitle(Todo _todo, const char* _title);

/**
 * @brief set a Todo description.
 * 
 * 
 * @param _todo A Todo.
 * @param _desc an constant @c char* to assign to the Description of @p _todo
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE todoSetDesc(Todo _todo, const char* _desc);

/**
 * @brief set the creation date of a Todo.
 * 
 * 
 * @param _todo A Todo.
 * @param _created_at an constant @c time_t to assign to the Creation date of @p _todo
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE todoSetCreatedAt(Todo _todo, const time_t _created_at);

/**
 * @brief set the deadline of a Todo.
 * 
 * 
 * @param _todo A Todo.
 * @param _deadline an constant @c time_t to assign to the Deadline of @p _todo
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE todoSetDeadline(Todo _todo, const time_t _deadline);

/**
 * @brief set a Todo status.
 * 
 * 
 * @param _todo A Todo.
 * @param _status an constant @c int to assign to status of @p _todo. (1 if it's completed, 0 otherwise)
 * @return a @c STATUS_CODE 
 */
enum STATUS_CODE todoSetStatus(Todo _todo, const int _status);

/**
 * @brief add a Todo task.
 * 
 * Verifies if @param _todo and @param _task are not @c NULL
 * and appends @param _task to @param _todo then increments by 1 @c _todo->len.
 * @code
 * if (todoAddTask(_todo, _task) == TODO_UPDATED)
 * {
 *    //Do something
 * }
 * else
 * {
 *    //Do something
 * }
 * @endcode
 * @param _todo A Todo.
 * @param _task an constant @c Task That is the Task to add to @p _todo
 * @return @c STATUS_CODE ( @c TODO_UPDATED || @c ERR_TODO) is always returned.
 */
enum STATUS_CODE todoAddTask(Todo _todo, const Task _task);


/**
 * @brief delete a Todo task.
 * 
 * Verifies if @param _todo and @param _task are not @c NULL
 * and searches @param _task into  @param _todo then deletes it if it is found.
 * Finily decrements by 1 @c _todo->len. All the @c Todo's Tasks are reorganized.
 * @code
 * if (todoDeleteTask(_todo, _task) == TODO_UPDATED)
 * {
 *    //Do something
 * }
 * else
 * {
 *    //Do something
 * }
 * @endcode
 * @param _todo A Todo.
 * @param _task an constant @c Task That is the Task to delete on @p _todo
 * @return @c STATUS_CODE ( @c TODO_UPDATED || @c ERR_TODO) is always returned.
 */
enum STATUS_CODE todoDeleteTask(Todo _todo, const Task _task);

#endif //H_TODO_H