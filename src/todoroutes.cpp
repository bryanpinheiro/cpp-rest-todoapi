#include "crow_all.h"
#include "todo.hpp"
#include "todoroutes.hpp"
#include <jansson.h>
#include <vector>
#include <string>

void getTodos(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext) {
  TodoManager todoManager;
  std::vector<Todo> allTodos = todoManager.getAllTodos(dbcontext);

  json_t* root = json_array(); // Create a JSON array

  for (const auto& todo : allTodos) {
      json_t* task = json_object(); // Create a JSON object for each task
      json_object_set_new(task, "id", json_integer(todo.id));
      json_object_set_new(task, "title", json_string(todo.title.c_str()));
      json_object_set_new(task, "completed", json_boolean(todo.completed));

      json_array_append_new(root, task); // Add task to the root array
  }

  char* output = json_dumps(root, JSON_INDENT(2)); // Convert JSON to string with indentation
  json_decref(root); // Clean up the root JSON object

  res.set_header("Content-Type", "application/json");
  res.write(output);
  res.end();

  // Don't forget to free the output after sending the response
  free(output);
}

void getTodoById(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext, int id) {
  try {
      TodoManager todoManager;
      Todo todo = todoManager.getTodoByID(dbcontext, id);

      json_t* task = json_object(); // Create a JSON object for the task
      json_object_set_new(task, "id", json_integer(todo.id));
      json_object_set_new(task, "title", json_string(todo.title.c_str()));
      json_object_set_new(task, "completed", json_boolean(todo.completed));

      char* output = json_dumps(task, JSON_INDENT(2)); // Convert JSON object to string with indentation
      json_decref(task); // Clean up the JSON object

      res.set_header("Content-Type", "application/json");
      res.write(output);
      res.end();

      // Don't forget to free the output after sending the response
      free(output);
  } catch (const std::system_error& e) {
    res.code = 404;
    res.write("Todo not found");
    res.end();
  }
}

void createTodo(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext)
{
  try {
    // Extract the title from the request body
    auto jsonBody = crow::json::load(req.body);
    std::string title = jsonBody["title"].s();

    // Create a new todo
    TodoManager todoManager;
    int newTodoID = todoManager.createTodo(dbcontext, title);

    // Set response status and message
    if (newTodoID != 0) {
        res.code = 201; // Created
        res.write("New todo created with ID: " + std::to_string(newTodoID));
    } else {
        res.code = 500; // Internal Server Error
        res.write("Failed to create todo.");
    }
    res.end();
  } catch (const std::exception& e) {
    res.code = 400; // Bad Request
    res.write("Error creating todo: " + std::string(e.what()));
    res.end();
  }
}

void updateTodoById(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext, int id)
{
  try {
    auto jsonBody = crow::json::load(req.body);
    bool completed = jsonBody["completed"].b();

    TodoManager todoManager;
    int updateResult = todoManager.updateTodoByID(dbcontext, id, completed);

    if (updateResult == 0) {
        res.code = 200; // OK
        res.write("Todo with ID " + std::to_string(id) + " updated.");
    } else {
        res.code = 404; // Not Found
        res.write("Todo with ID " + std::to_string(id) + " not found or update failed.");
    }
    res.end();
  } catch (const std::exception& e) {
    res.code = 400; // Bad Request
    res.write("Error updating todo: " + std::string(e.what()));
    res.end();
  }
}

void deleteTodoById(const crow::request& req, crow::response& res, MyTodoStorage& dbcontext, int id)
{
  try {
    TodoManager todoManager;
    todoManager.deleteTodoByID(dbcontext, id);

    res.code = 200; // OK
    res.write("Todo with ID " + std::to_string(id) + " deleted.");
    res.end();
  } catch (const std::exception& e) {
    res.code = 400; // Bad Request
    res.write("Error deleting todo: " + std::string(e.what()));
    res.end();
  }
}

void setupTodoRoutes(crow::SimpleApp& app, MyTodoStorage& storage) {
    CROW_ROUTE(app, "/api/todos")
        .methods("GET"_method)
        ([&storage](const crow::request& req, crow::response& res) {
            getTodos(req, res, storage);
        });

    CROW_ROUTE(app, "/api/todos")
        .methods("POST"_method)
        ([&storage](const crow::request& req, crow::response& res) {
            createTodo(req, res, storage);
        });

    CROW_ROUTE(app, "/api/todos/<int>")
        .methods("GET"_method)
        ([&storage](const crow::request& req, crow::response& res, int id) {
            getTodoById(req, res, storage, id);
        });
    
    CROW_ROUTE(app, "/api/todos/<int>")
        .methods("PUT"_method)
        ([&storage](const crow::request& req, crow::response& res, int id) {
            updateTodoById(req, res, storage, id);
        });

    CROW_ROUTE(app, "/api/todos/<int>")
        .methods("DELETE"_method)
        ([&storage](const crow::request& req, crow::response& res, int id) {
            deleteTodoById(req, res, storage, id);
        });
}
