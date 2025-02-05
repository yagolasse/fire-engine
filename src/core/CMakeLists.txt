add_library(engine-core application.cpp asset_loader.cpp camera.cpp orthographic_camera.cpp debug_ui.cpp scene.cpp sprite.cpp window.cpp)

target_include_directories(engine-core PRIVATE .)
target_include_directories(engine-core PRIVATE ../rendering)

target_include_directories(engine-core PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(engine-core PRIVATE ${glm_SOURCE_DIR}/glm)

target_include_directories(engine-core PRIVATE ../../vendor/imgui)
target_include_directories(engine-core PRIVATE ../../vendor/glad/include)

target_link_libraries(engine-core glfw)
