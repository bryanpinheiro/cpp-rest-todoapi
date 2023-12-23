#include "crow_all.h"
#include <iostream>
#include <jansson.h>

int main() {
    crow::SimpleApp app;

    // Handler for the root endpoint '/'
    CROW_ROUTE(app, "/")(
        [](const crow::request& req, crow::response& res) {
            // Create a simple JSON object
            json_t* root = json_object();
            json_object_set_new(root, "message", json_string("Hello, World!"));

            // Convert the JSON object to a string
            char* jsonStr = json_dumps(root, JSON_INDENT(2));
            json_decref(root);

            // Set the response with JSON content
            res.set_header("Content-Type", "application/json");
            res.write(jsonStr);
            res.end();

            // Free the allocated JSON string
            free(jsonStr);
        }
    );

    // Start the server on port 8080
    app.port(8080).run();

    return 0;
}
