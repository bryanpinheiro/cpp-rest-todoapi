#include "todo.hpp"
#include <iostream>

int TodoManager::createTodo(storage_t<> dbcontext, string title) 
{
  int newTodoID = dbcontext.insert(Todo{0, title, false});
  return newTodoID;
}

vector<Todo> TodoManager::getAllTodos(storage_t<> dbcontext) 
{
  auto allTodos = dbcontext.get_all<Todo>();
  return allTodos;
}

Todo TodoManager::getTodoByID(storage_t<> dbcontext, int id)
{
  return dbcontext.get<Todo>(id);
}

int TodoManager::updateTodoByID(storage_t<> dbcontext, int id, bool completed)
{
  try
  {
    auto todo = dbcontext.get_pointer<Todo>(id);
    if (todo)
    {
      todo->completed = completed;
      dbcontext.update(*todo);
      return 0;
    }
    else
    {
      std::cout << "No todo with id 1" << std::endl;
      return 1;
    }
  }
  catch (const std::system_error &e)
  {
    std::cout << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cout << "Unknown exception occurred." << std::endl;
    return 1;
  }
}

void TodoManager::deleteTodoByID(storage_t<> dbcontext, int id)
{
  dbcontext.remove<Todo>(id);
}
