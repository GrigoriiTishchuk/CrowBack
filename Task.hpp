#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <nlohmann/json.hpp>

class Task {
    int id;
    std::string description;
    bool completed;

public:
    // Default constructor
    Task();
    // Parameterized constructor
    Task(int id, const std::string& description, bool completed = false);

    int getId() const;
    const std::string& getDescription() const;
    bool isCompleted() const;

    void setDescription(const std::string& desc);
    void setCompleted(bool status);

    /* 
    * Inline is used to allow these functions to be defined in the header file
    * without causing multiple definition errors during linking. This is necessary
    * because these functions are template specializations for nlohmann::json,
    * and they need to be visible to all translation units that include this header. 
    */
    friend inline void to_json(nlohmann::json& j, const Task& task);
    friend inline void from_json(const nlohmann::json& j, Task& task);
};


/**
 * @brief Serializes a Task into a JSON object.
 *
 * @param j The JSON object to which the Task is serialized.
 * @param task The Task to be serialized.
 */
inline void to_json(nlohmann::json& j, const Task& task) {
    j = nlohmann::json{
        {"id", task.getId()},
        {"description", task.getDescription()},
        {"completed", task.isCompleted()}
    };
}


/**
 * @brief Deserializes a Task from a JSON object.
 *
 * @param j The JSON object from which the Task is deserialized.
 * @param task The Task to be deserialized.
 */
inline void from_json(const nlohmann::json& j, Task& task) {
    task.id = j.at("id").get<int>();
    task.description = j.at("description").get<std::string>();
    task.completed = j.at("completed").get<bool>();
}

#endif // TASK_HPP