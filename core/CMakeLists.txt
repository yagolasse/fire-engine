add_library(engine-core STATIC src/application.cpp src/asset_loader.cpp src/debug_ui.cpp src/game_object.cpp src/input.cpp src/random.cpp src/scene.cpp src/scene_manager.cpp src/sprite.cpp src/window.cpp)

include(FetchContent)

FetchContent_Declare(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)

FetchContent_MakeAvailable(
    glfw3
)

target_include_directories(engine-core PRIVATE .)
target_include_directories(engine-core PRIVATE ../rendering/src)

target_include_directories(engine-core PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(engine-core PRIVATE ${glm_SOURCE_DIR}/glm)

target_include_directories(engine-core PRIVATE ../vendor/imgui)

target_link_libraries(engine-core glfw)
