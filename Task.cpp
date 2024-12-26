#include "Task.hpp"
#include <nlohmann/json.hpp>

// Default constructor
Task::Task() : id(0), description(""), completed(false) {}

// Parameterized constructor
Task::Task(int id, const std::string& description, bool completed)
    : id(id), description(description), completed(completed) {}

// Getter for task ID
int Task::getId() const {
    return id;
}

// Getter for task description
const std::string& Task::getDescription() const {
    return description;
}

// Getter for task completion status
bool Task::isCompleted() const {
    return completed;
}

// Setter for task description
void Task::setDescription(const std::string& desc) {
    description = desc;
}

// Setter for task completion status
void Task::setCompleted(bool status) {
    completed = status;
}
