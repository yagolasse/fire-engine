cmake_minimum_required(VERSION 3.28.3)

project(fire-engine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LUA_VERSION "lua-5.4.7")

if(APPLE AND UNIX)
include(ExternalProject)

ExternalProject_Add(lua_project
  PREFIX ${CMAKE_BINARY_DIR}/${LUA_VERSION}
  URL https://www.lua.org/ftp/${LUA_VERSION}.tar.gz
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make generic
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE true
  DOWNLOAD_EXTRACT_TIMESTAMP false
)

ExternalProject_Get_Property(lua_project BINARY_DIR)
set(LUA_INCLUDE_DIR ${BINARY_DIR}/src)
set(LUA_LIBRARIES ${BINARY_DIR}/src/liblua.a)
endif()

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
if(WIN32)
FetchContent_Declare(
    lua
    GIT_REPOSITORY https://github.com/walterschell/Lua.git
    GIT_TAG v5.4.5
)
endif()

FetchContent_MakeAvailable(
    glfw3 glm
)
if(WIN32)
FetchContent_MakeAvailable(
    lua
)
endif()

if(APPLE AND UNIX)
target_compile_options(glm PRIVATE
    -Wno-c++98-compat 
    -Wno-c++98-compat-pedantic
)
endif()

set(CORE_SOURCE src/core/application.cpp src/core/assertion.cpp src/core/asset_loader.cpp src/core/error.cpp src/core/camera.cpp src/core/orthographic_camera.cpp src/core/debug_ui.cpp src/core/script.cpp src/core/scene.cpp src/core/sprite.cpp src/core/window.cpp)
set(RENDERING_SOURCE src/rendering/batch_renderer.cpp src/rendering/element_array_buffer.cpp src/rendering/error_check.cpp src/rendering/mesh.cpp src/rendering/renderer.cpp src/rendering/shader_program.cpp src/rendering/sprite_sheet.cpp src/rendering/shader.cpp src/rendering/texture.cpp src/rendering/texture_storage.cpp src/rendering/texture_region.cpp src/rendering/vertex_array_buffer.cpp src/rendering/vertex_buffer.cpp)

set(IMGUI_BACKEND vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp)
set(IMGUI_SOURCE vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp vendor/imgui/imgui.cpp)
 
add_executable(fire-engine vendor/glad/src/glad.c ${IMGUI_BACKEND} ${IMGUI_SOURCE} ${CORE_SOURCE} ${RENDERING_SOURCE} src/main.cpp)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory"
)

if(APPLE AND UNIX)
add_dependencies(fire-engine copy_resources lua_project)
endif()

target_include_directories(fire-engine PRIVATE vendor/imgui)

target_include_directories(fire-engine PRIVATE vendor/glad/include)
target_include_directories(fire-engine PRIVATE vendor/stb/include)

target_include_directories(fire-engine PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(fire-engine PRIVATE ${glm_SOURCE_DIR}/glm)

target_include_directories(fire-engine PRIVATE src/core)
target_include_directories(fire-engine PRIVATE src/rendering)

if(WIN32)
target_include_directories(fire-engine PRIVATE ${lua_SOURCE_DIR}/lua-5.4.5/include)
elseif(APPLE AND UNIX)
target_include_directories(fire-engine PRIVATE ${LUA_INCLUDE_DIR})
endif()

if(WIN32)
target_link_libraries(fire-engine lua_static)
elseif(APPLE AND UNIX)
target_link_libraries(fire-engine ${LUA_LIBRARIES} m)
endif()

target_link_libraries(fire-engine glfw)
