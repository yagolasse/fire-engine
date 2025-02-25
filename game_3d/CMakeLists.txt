add_library(game-3d STATIC src/custom_3d_camera.cpp src/game_application_3d.cpp src/game_scene_3d.cpp)

add_custom_target(copy_resources_voxel_game ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory"
)

target_include_directories(game-3d PRIVATE src)
target_include_directories(game-3d PRIVATE ../rendering/src)
target_include_directories(game-3d PRIVATE ../core/src)

target_include_directories(game-3d PRIVATE ${glm_SOURCE_DIR}/glm)

target_link_libraries(game-3d engine-rendering)
target_link_libraries(game-3d engine-core)

target_link_libraries(game-3d glfw)
