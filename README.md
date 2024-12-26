# CrowBackend

CrowBackend is a C++ project that uses the Crow web framework and nlohmann::json for managing tasks. This project demonstrates how to create a simple REST API for task management.

## Features

- Create, read, update, and delete tasks
- JSON serialization and deserialization
- REST API endpoints using Crow

## Requirements

- C++17 or later
- CMake 3.15 or later
- vcpkg for dependency management
- Crow
- nlohmann::json

## Installation

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/CrowBackend.git
    cd CrowBackend
    ```

2. **Install dependencies using vcpkg:**

    ```sh
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.bat
    ./vcpkg integrate install
    ./vcpkg install 
    ```

3. **Configure and build the project:**

    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Debug
    ```

## Usage

1. **Run the application:**

    ```sh
    ./build/CrowBackend
    ```
    Or launch manually by pressing on `CrowBackend.exe

2. **API Endpoints:**

    - `GET /getTasks`: Returns a list of all tasks
    - `POST /createTask`: Creates a new task with the given description
    - `PUT /updateTask`: Updates the completion status of a task
    - `DELETE /deleteTask`: Deletes a task by its ID

## Example

Here is an example of how to use the API:

- **Create a new task:**

    ```sh
    curl -X POST -H "Content-Type: application/json" -d '{"description": "Complete the project"}' http://localhost:18080/createTask
    ```

- **Get all tasks:**

    ```sh
    curl http://localhost:18080/getTasks
    ```

- **Update a task:**

    ```sh
    curl -X PUT -H "Content-Type: application/json" -d '{"id": 1, "completed": true}' http://localhost:18080/updateTask
    ```

- **Delete a task:**

    ```sh
    curl -X DELETE -H "Content-Type: application/json" -d '{"id": 1}' http://localhost:18080/deleteTask
    ```

## Documentation

You can generate the documentation using Doxygen. Follow these steps:

1. **Install Doxygen:**

    Download and install Doxygen from [Doxygen Downloads](http://www.doxygen.nl/download.html).

2. **Generate the documentation:**

    ```sh
    doxygen Doxyfile
    ```

3. **View the documentation:**

    Open `docs/html/index.html` in your web browser.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## License

This project is not licensed. See the LICENSE file for details.
