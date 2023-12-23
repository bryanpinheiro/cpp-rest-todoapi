#include "crow_all.h"
#include "todoroutes.hpp"
#include <iostream>
#include <jansson.h>

int main() {
    crow::SimpleApp app;

  auto storage = make_storage("./database/todos.sqlite",
    make_table("todos",
      make_column("id", &Todo::id, primary_key().autoincrement()),
      make_column("title", &Todo::title),
      make_column("completed", &Todo::completed)));

    storage.sync_schema();

    auto allTodos = storage.get_all<Todo>();

    if (allTodos.empty()) {
        std::cout << "Empty list of todos" << std::endl;
    } else {
        for (const auto& todo : allTodos) {
            std::cout << "ID: " << todo.id 
                      << ", Title: " << todo.title 
                      << ", Completed: " << todo.completed 
                      << std::endl;
        }
    }

    // Call todo routes
    setupTodoRoutes(app, storage);

    // Start the server on port 8080
    app.port(8080).run();

    return 0;
}
