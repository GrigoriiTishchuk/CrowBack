#include "TaskManager.hpp"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Definition of the default constructor
TaskManager::TaskManager() : fileName("tasks.json") {
    loadFromFile();
}
// Definition of the parameterized constructor
TaskManager::TaskManager(const std::string& fileName) : fileName(fileName) {
    loadFromFile();
}
// Destructor
TaskManager::~TaskManager() {
    saveToFile();
}

/**
 * @brief Adds a new task to the TaskManager.
 *
 * @param description The description of the new task.
 *
 * @return The newly created task.
 */
Task TaskManager::addTask(const std::string& description) {
    Task task(nextId++, description, false);
    tasks[task.getId()] = task;
    saveToFile();
    return task;
}

/**
 * @brief Gets a task by its ID.
 *
 * @param id The ID of the task to look up.
 *
 * @return The task with the given ID.
 *
 * @throws std::runtime_error If the task with the given ID does not exist.
 */
Task TaskManager::getTask(int id) const {
    auto it = tasks.find(id);
    if (it == tasks.end()) throw std::runtime_error("Task not found");
    return it->second;
}

/**
 * @brief Updates the description of the task with the given ID.
 *
 * @param id The ID of the task to update.
 * @param description The new description of the task.
 *
 * @throws std::runtime_error If the task with the given ID does not exist.
 */
void TaskManager::updateTask(int id, const std::string& description) {
    auto it = tasks.find(id);
    if (it == tasks.end()) throw std::runtime_error("Task not found");
    it->second.setDescription(description);
    saveToFile();
}

/**
 * @brief Deletes a task by its ID from the TaskManager.
 *
 * @param id The ID of the task to be deleted.
 *
 * @throws std::runtime_error If the task with the given ID does not exist.
 */

void TaskManager::deleteTask(int id) {
    if (tasks.erase(id) == 0) throw std::runtime_error("Task not found");
    saveToFile();
}
/**
 * @brief Updates the completion status of a task.
 *
 * @param id The ID of the task whose completion status to update.
 * @param completed The new completion status of the task.
 *
 * @throws std::runtime_error If the task with the given ID does not exist.
 */
void TaskManager::updateTaskCompletion(int id, bool completed) {
    auto it = tasks.find(id);
    if (it == tasks.end()) {
        throw std::runtime_error("Task not found.");
    }

    it->second.setCompleted(completed);
    saveToFile(); // Persist changes to the file (optional)
}

std::map<int, Task> TaskManager::getAllTasks() const {
    return tasks;
}

/**
 * @brief Loads tasks from a file into the TaskManager.
 *
 * Loads tasks from a JSON file stored in @ref fileName. The file is expected
 * to contain a JSON object with string keys representing task IDs and values
 * being JSON objects with the properties "description" and "completed". If the
 * file does not exist or cannot be opened, nothing is done.
 *
 * The IDs of the loaded tasks are used to determine the next ID to use when
 * creating new tasks. If the loaded tasks contain IDs higher than the current
 * next ID, the next ID is updated to be one higher than the highest loaded ID.
 */
void TaskManager::loadFromFile() {
    std::ifstream file(fileName);
    if (file.is_open()) {
        nlohmann::json taskJson;
        file >> taskJson;

        for (const auto& item : taskJson.items()) {
            // Explicitly using 'from_json' to deserialize the Task object
            Task task;
            from_json(item.value(), task);  // Deserialize directly into task object
            tasks[task.getId()] = task;
            nextId = std::max(nextId, task.getId() + 1);
        }
    }
}


/**
 * @brief Saves all tasks in the TaskManager to a JSON file.
 *
 * Saves all tasks in the TaskManager to a JSON file stored in @ref fileName.
 * The file is a JSON object with string keys representing task IDs and values
 * being JSON objects with the properties "description" and "completed". If the
 * file cannot be opened, nothing is done.
 */
void TaskManager::saveToFile() {
    std::ofstream file(fileName);
    if (file.is_open()) {
        json taskJson = tasks;
        file << taskJson.dump(4);
    }
}
