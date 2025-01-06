cmake_minimum_required(VERSION 3.15)

project(CrowBackend)
project(TaskManagerTests)
set(CMAKE_CXX_STANDARD 17)
# Path to vcpkg.cmake
set(CMAKE_TOOLCHAIN_FILE "C:/vcpg/vcpkg/scripts/buildsystems/vcpkg.cmake") 
# Path to vcpkg_installed directory on your machine, change it accordingly  
set(CMAKE_PREFIX_PATH "C:/crowbackend/vcpkg_installed/x64-windows") 
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
enable_testing()
add_definitions(-D_WIN32_WINNT=0x0601)
add_executable(CrowBackend main.cpp Task.cpp TaskManager.cpp)
# Path to include directory of vcpkg_installed on your machine, change it accordingly
target_include_directories(CrowBackend PRIVATE C:/crowbackend/vcpkg_installed/x64-windows/include)
target_link_libraries(CrowBackend PRIVATE Crow::Crow)
target_link_libraries(CrowBackend PRIVATE nlohmann_json::nlohmann_json)
# Add test executable
add_executable(TaskManagerTests tests/TaskManagerTests.cpp Task.cpp TaskManager.cpp)
target_link_libraries(TaskManagerTests PRIVATE GTest::gtest GTest::gtest_main)