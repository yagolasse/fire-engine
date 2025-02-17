add_library(engine-rendering STATIC vendor/glad/src/glad.c src/assertion.cpp src/batch_renderer.cpp src/element_array_buffer.cpp src/error.cpp src/error_check.cpp src/renderer.cpp src/shader_program.cpp src/sprite_sheet.cpp src/shader.cpp src/texture.cpp src/texture_storage.cpp src/texture_region.cpp src/vertex_array_buffer.cpp src/vertex_buffer.cpp)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.0
)

FetchContent_MakeAvailable(
    glm
)

target_compile_options(glm PRIVATE
    -Wno-c++98-compat 
    -Wno-c++98-compat-pedantic
)

add_custom_target(copy_rendering_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory"
)

target_include_directories(engine-rendering PUBLIC ${glm_SOURCE_DIR}/glm)

target_include_directories(engine-rendering PRIVATE vendor/glad/include)
target_include_directories(engine-rendering PRIVATE vendor/stb/include)
