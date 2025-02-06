add_library(game game_application.cpp game_scene.cpp ship.cpp)

target_include_directories(game PRIVATE .)
target_include_directories(game PRIVATE ../rendering)
target_include_directories(game PRIVATE ../core)

# target_include_directories(game PRIVATE ../../vendor/glad/include)
target_include_directories(game PRIVATE ${glm_SOURCE_DIR}/glm)
