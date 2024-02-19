cmake_minimum_required(VERSION 3.29)

project(fire-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.0
)
FetchContent_MakeAvailable(
    glfw3 glm
)

file(GLOB SOURCE src/core/*.cpp)
file(GLOB SOURCE src/rendering/*.cpp)

add_executable(fire-engine src/main.cpp ${SOURCE} vendor/glad/src/glad.c)

target_include_directories(fire-engine PRIVATE vendor/glad/include)

target_include_directories(fire-engine PRIVATE build/_deps/glfw3-src/include)
target_include_directories(fire-engine PRIVATE build/_deps/glm-src/glm)

target_include_directories(fire-engine PRIVATE src/core)
target_include_directories(fire-engine PRIVATE src/rendering)

target_link_libraries(fire-engine glfw)
