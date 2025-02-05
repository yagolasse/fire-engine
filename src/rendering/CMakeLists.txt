add_library(engine-rendering assertion.cpp batch_renderer.cpp element_array_buffer.cpp error.cpp error_check.cpp renderer.cpp shader_program.cpp sprite_sheet.cpp shader.cpp texture.cpp texture_storage.cpp texture_region.cpp vertex_array_buffer.cpp vertex_buffer.cpp)

target_include_directories(engine-rendering PRIVATE ${glm_SOURCE_DIR}/glm)

target_include_directories(engine-rendering PRIVATE ../../vendor/glad/include)
target_include_directories(engine-rendering PRIVATE ../../vendor/stb/include)
