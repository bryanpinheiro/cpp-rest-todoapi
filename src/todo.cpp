#include "todo.hpp"
#include <iostream>

int TodoManager::createTodo(MyTodoStorage dbcontext, string title) 
{
  int newTodoID = dbcontext.insert(Todo{0, title, false});
  return newTodoID;
}

vector<Todo> TodoManager::getAllTodos(MyTodoStorage dbcontext) 
{
  auto allTodos = dbcontext.get_all<Todo>();
  return allTodos;
}

Todo TodoManager::getTodoByID(MyTodoStorage dbcontext, int id)
{
  return dbcontext.get<Todo>(id);
}

int TodoManager::updateTodoByID(MyTodoStorage dbcontext, int id, bool completed)
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

void TodoManager::deleteTodoByID(MyTodoStorage dbcontext, int id)
{
  dbcontext.remove<Todo>(id);
}
