cmake_minimum_required(VERSION 3.28.3)

project(fire-engine LANGUAGES CXX C)

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

if(APPLE AND UNIX)
target_compile_options(glm PRIVATE
    -Wno-c++98-compat 
    -Wno-c++98-compat-pedantic
)
endif()

set(IMGUI_BACKEND vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp)
set(IMGUI_SOURCE vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp vendor/imgui/imgui.cpp)
 
add_subdirectory(rendering)
add_subdirectory(core)
add_subdirectory(src/game)

add_executable(fire-engine ${IMGUI_BACKEND} ${IMGUI_SOURCE} src/main.cpp)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory"
)

target_include_directories(fire-engine PRIVATE vendor/imgui)

target_include_directories(fire-engine PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(fire-engine PRIVATE ${glm_SOURCE_DIR}/glm)

target_include_directories(fire-engine PRIVATE core)
target_include_directories(fire-engine PRIVATE src/rendering)
target_include_directories(fire-engine PRIVATE src/game)

# target_link_libraries(fire-engine glfw)

target_link_libraries(fire-engine engine-core)

target_link_libraries(fire-engine engine-rendering)

target_link_libraries(fire-engine game)
