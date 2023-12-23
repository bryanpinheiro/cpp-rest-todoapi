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

class TodoManager {
public:
    // CRUD operations
    int createTodo(storage_t<> dbcontext, std::string title);
    std::vector<Todo> getAllTodos(storage_t<> dbcontext);
    Todo getTodoByID(storage_t<> dbcontext, int id);
    int updateTodoByID(storage_t<> dbcontext, int id, bool completed);
    void deleteTodoByID(storage_t<> dbcontext, int id);
};

#endif // TODO_HPP
