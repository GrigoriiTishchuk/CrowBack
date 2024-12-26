#include "./TaskManager.hpp"
#include <gtest/gtest.h>
#include <fstream>

// Helper function to remove the test file after each test
void removeTestFile(const std::string& fileName) {
    std::remove(fileName.c_str());
}

// Test fixture for TaskManager tests
class TaskManagerTest : public ::testing::Test {
protected:
    std::string testFileName = "test_tasks.json";
    TaskManager taskManager;

    TaskManagerTest() : taskManager(testFileName) {}

    void SetUp() override {
        // Remove the test file before each test
        removeTestFile(testFileName);
    }

    void TearDown() override {
        // Remove the test file after each test
        removeTestFile(testFileName);
    }
};

// Test adding a task
TEST_F(TaskManagerTest, AddTask) {
    Task task = taskManager.addTask("Test Task");
    auto tasks = taskManager.getAllTasks();
    ASSERT_EQ(tasks.size(), 1);
    ASSERT_EQ(tasks[1].getDescription(), "Test Task");
}

// Test deleting a task
TEST_F(TaskManagerTest, DeleteTask) {
    Task task = taskManager.addTask("Test Task");
    taskManager.deleteTask(task.getId());
    auto tasks = taskManager.getAllTasks();
    ASSERT_EQ(tasks.size(), 0);
}

// Test updating task status
TEST_F(TaskManagerTest, UpdateTaskStatus) {
    Task task = taskManager.addTask("Test Task");
    taskManager.updateTask(task.getId(), "Updated Task Description");
    auto tasks = taskManager.getAllTasks();
    ASSERT_EQ(tasks[task.getId()].getDescription(), "Updated Task Description");
}

// Test loading tasks from file
TEST_F(TaskManagerTest, LoadFromFile) {
    Task task = taskManager.addTask("Test Task");
    taskManager.saveToFile();

    TaskManager newTaskManager(testFileName);
    newTaskManager.loadFromFile();
    auto tasks = newTaskManager.getAllTasks();
    ASSERT_EQ(tasks.size(), 1);
    ASSERT_EQ(tasks[1].getDescription(), "Test Task");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}