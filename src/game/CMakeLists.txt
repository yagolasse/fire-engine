add_library(game game_application.cpp game_scene.cpp ship.cpp star.cpp)

target_include_directories(game PRIVATE .)
target_include_directories(game PRIVATE ../rendering)
target_include_directories(game PRIVATE ../core)
target_include_directories(game PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(game PRIVATE ${glm_SOURCE_DIR}/glm)

target_link_libraries(game glfw)

target_link_libraries(game engine-core)
target_link_libraries(game engine-rendering)

# target_include_directories(game PRIVATE ../../vendor/glad/include)
