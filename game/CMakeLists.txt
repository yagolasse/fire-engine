add_library(game STATIC src/bullet.cpp src/game_application.cpp src/game_scene.cpp src/ship.cpp src/star.cpp)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory"
)

target_include_directories(game PRIVATE .)
target_include_directories(game PRIVATE ../rendering/src)
target_include_directories(game PRIVATE ../core/src)

target_include_directories(game PRIVATE ${glm_SOURCE_DIR}/glm)

target_link_libraries(game engine-rendering)
target_link_libraries(game engine-core)

target_link_libraries(game glfw)
