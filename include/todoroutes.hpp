// todoroutes.hpp

#ifndef TODOROUTES_HPP
#define TODOROUTES_HPP

#include "crow_all.h"
#include "todo.hpp"
#include <jansson.h>
#include <vector>
#include <string>

// Define your types
using MyTodoTable = sqlite_orm::internal::table_t<
    Todo,
    false,
    sqlite_orm::internal::column_t<int Todo::*, sqlite_orm::internal::empty_setter, sqlite_orm::internal::primary_key_with_autoincrement<sqlite_orm::internal::primary_key_t<>>>,
    sqlite_orm::internal::column_t<std::__1::string Todo::*, sqlite_orm::internal::empty_setter>,
    sqlite_orm::internal::column_t<bool Todo::*, sqlite_orm::internal::empty_setter>
>;

using MyTodoStorage = sqlite_orm::internal::storage_t<MyTodoTable>;

// Function declarations
void getTodos(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext);
void createTodo(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext);
void getTodoById(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext, int id);
void updateTodoById(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext, int id);
void deleteTodoById(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext, int id);
void setupTodoRoutes(crow::SimpleApp& app, MyTodoStorage& storage);

#endif // TODOROUTES_HPP
