cmake_minimum_required(VERSION 3.28.3 FATAL_ERROR)
cmake_policy(VERSION 3.28.3)

project(fire-engine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(IMGUI_BACKEND vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp)
set(IMGUI_SOURCE vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp vendor/imgui/imgui.cpp)
 
add_subdirectory(rendering)
add_subdirectory(core)
add_subdirectory(game)

add_executable(fire-engine ${IMGUI_BACKEND} ${IMGUI_SOURCE} src/main.cpp)

target_include_directories(fire-engine PRIVATE vendor/imgui)

target_include_directories(fire-engine PRIVATE core/src)
target_include_directories(fire-engine PRIVATE game/src)

target_link_libraries(fire-engine engine-core)

target_link_libraries(fire-engine engine-rendering)

target_link_libraries(fire-engine game)
