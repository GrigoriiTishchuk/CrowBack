#include "TaskManager.hpp"
#include <crow.h>
/**
 * @brief Validates if the provided JSON body contains a valid task description.
 * 
 * @param body The JSON body to validate, expected to contain a "description" field.
 * @return true if the "description" field exists and is not empty, false otherwise.
 */

bool validateTaskJson(const crow::json::rvalue& body) {
    if (!body.has("description")) return false;
    if (body["description"].s().size() == 0) return false;
    return true;
}

/**
 * @brief Entry point of the Crow application.
 *
 * This function sets up a Crow application listening on port 18080 with
 * the following routes:
 * - GET /getTasks: Returns a list of all tasks in the TaskManager.
 * - POST /createTasks: Creates a new task with the given description.
 * - PUT /updateTask/<int>: Updates a task by ID with the given completion status.
 * - DELETE /deleteTasks/<int>: Deletes a task by ID.
 *
 * The TaskManager is used to store and manage all tasks. The application
 * is multithreaded to ensure that requests are handled concurrently.
 */
int main() {
    crow::SimpleApp app;
    TaskManager taskManager;

    CROW_ROUTE(app, "/getTasks")
        .methods("GET"_method)([&taskManager]() {
            auto tasks = taskManager.getAllTasks();
            crow::json::wvalue response = crow::json::wvalue::list();
            for (const auto& [id, task] : tasks) {
                response[response.size()] = {{"id", task.getId()}, {"description", task.getDescription()}, {"completed", task.isCompleted()}};
            }
            return crow::response(response);
        });

    CROW_ROUTE(app, "/createTasks")
        .methods("POST"_method)([&taskManager](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body || !validateTaskJson(body)) {
                return crow::response(400, "Invalid input");
            }
            Task task = taskManager.addTask(body["description"].s());
            return crow::response(crow::json::wvalue({{"id", task.getId()}, {"description", task.getDescription()}, {"completed", task.isCompleted()}}));
        });

    CROW_ROUTE(app, "/updateTask/<int>").methods("PUT"_method)(
    [&taskManager](const crow::request& req, crow::response& res, int id) {
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("completed")) {
                res.code = 400;
                res.body = "Invalid input: Missing 'completed' field.";
                res.end();
                return;
            }

            bool completed = body["completed"].b(); // Get the boolean value
            taskManager.updateTaskCompletion(id, completed);

            res.code = 200;
            res.body = "Task updated successfully.";
        } catch (const std::exception& e) {
            res.code = 404;
            res.body = "Task not found or invalid data.";
        }
        res.end();
    });

    CROW_ROUTE(app, "/deleteTasks/<int>").methods("DELETE"_method)(
    [&taskManager](const crow::request& req, crow::response& res, int id) {
        try {
            taskManager.deleteTask(id);  // Delete the task by ID
            res.code = 200;
            res.body = R"({"message": "Task deleted successfully."})";
        } catch (const std::exception& e) {
            res.code = 404;
            res.body = R"({"error": "Task not found."})";
        }
        res.end();
    });

    // Start the server on port 18080
    app.port(18080).multithreaded().run();
}