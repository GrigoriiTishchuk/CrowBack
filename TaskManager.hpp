#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include "Task.hpp"
#include <map>
#include <string>

class TaskManager {
    std::map<int, Task> tasks;
    int nextId = 1; // Next task ID
    const std::string fileName = "tasks.json";

public:
    /**
     * @brief Default constructor.
     */
    TaskManager();
    /**
     * @brief Constructs a TaskManager with a specified file name.
     * @param fileName Name of the file to save/load tasks
     */
    TaskManager(const std::string& fileName);
    ~TaskManager();

    Task addTask(const std::string& description);
    Task getTask(int id) const;
    void updateTask(int id, const std::string& description);
    void deleteTask(int id);
    void updateTaskCompletion(int id, bool completed);
    std::map<int, Task> getAllTasks() const;

    void loadFromFile();
    void saveToFile();
};

#endif // TASKMANAGER_HPP