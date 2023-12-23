#ifndef TODO_HPP
#define TODO_HPP

#include <sqlite_orm/sqlite_orm.h>
#include <vector>
#include <string>

using namespace std;
using namespace sqlite_orm;
using namespace sqlite_orm::internal;

struct Todo {
    int id;
    std::string title;
    bool completed;
};

using MyTodoTable = sqlite_orm::internal::table_t<
    Todo,
    false,
    sqlite_orm::internal::column_t<int Todo::*, sqlite_orm::internal::empty_setter, sqlite_orm::internal::primary_key_with_autoincrement<sqlite_orm::internal::primary_key_t<>>>,
    sqlite_orm::internal::column_t<std::__1::string Todo::*, sqlite_orm::internal::empty_setter>,
    sqlite_orm::internal::column_t<bool Todo::*, sqlite_orm::internal::empty_setter>
>;

using MyTodoStorage = sqlite_orm::internal::storage_t<MyTodoTable>;

class TodoManager {
public:
    // CRUD operations
    int createTodo(MyTodoStorage dbcontext, std::string title);
    std::vector<Todo> getAllTodos(MyTodoStorage dbcontext);
    Todo getTodoByID(MyTodoStorage dbcontext, int id);
    int updateTodoByID(MyTodoStorage dbcontext, int id, bool completed);
    void deleteTodoByID(MyTodoStorage dbcontext, int id);
};

#endif // TODO_HPP
