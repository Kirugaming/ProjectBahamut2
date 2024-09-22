cmake_minimum_required(VERSION 3.22)
project(ProjectBahamut)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#add_compile_options(-Wno-error=dangling-reference) # assimp (compile bug?)

# imgui
set(IMGUI_SOURCES lib/imgui/imgui.cpp
        lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/backends/imgui_impl_opengl3.cpp
        lib/imgui/backends/imgui_impl_sdl2.cpp
        lib/imgui/backends/imgui_impl_sdlrenderer2.cpp)

include_directories(lib/imgui)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
set(SOURCE_FILES
        engine
        ui
        engine/Engine.cpp
        engine/Engine.h
        main.cpp
        main.h
        Texture.cpp
        Texture.h
        Types.cpp
        Types.h
        engine/BaseDrawable.cpp
        engine/BaseDrawable.h
        engine/Line.cpp
        engine/Line.h
)

file(GLOB SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.h
        ${CMAKE_SOURCE_DIR}/ui/*.cpp
        ${CMAKE_SOURCE_DIR}/ui/*.h
        ${CMAKE_SOURCE_DIR}/engine/*.cpp
        ${CMAKE_SOURCE_DIR}/engine/*.h
)

set(LIB_FILES engine/glad.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${LIB_FILES} ${IMGUI_SOURCES})


# include libraries with the project
set(BUILD_SHARED_LIBS ON)

target_include_directories(${PROJECT_NAME} PRIVATE include/)

# yaml-cpp
add_subdirectory("lib/yaml-cpp")
target_link_libraries(${PROJECT_NAME} yaml-cpp::yaml-cpp)

# SDL
add_subdirectory("lib/SDL2/")
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

# stb
include_directories(${PROJECT_NAME} PRIVATE lib/stb)

# assimp
add_subdirectory("lib/assimp/")
target_link_libraries(${PROJECT_NAME} assimp::assimp)

# glm
add_subdirectory("lib/glm/")
target_link_libraries(${PROJECT_NAME} glm)

# lua
add_subdirectory("lib/lua")
target_link_libraries(${PROJECT_NAME} lua)

# sol2
add_subdirectory("lib/sol2")
target_link_libraries(${PROJECT_NAME} sol2)


# Copy Needed DLLs to build
set(lib_dlls
        ${PROJECT_BINARY_DIR}/lib/assimp/bin/libassimp-5d.dll
        ${PROJECT_BINARY_DIR}/lib/SDL2/SDL2d.dll
        ${PROJECT_BINARY_DIR}/lib/yaml-cpp/libyaml-cppd.dll
        ${PROJECT_BINARY_DIR}/lib/lua/libluad.dll
        )
add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying DLLs to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${lib_dlls} ${PROJECT_BINARY_DIR} > copy_dlls.log 2>&1
        COMMENT "Copying DLLs to build directory"
)

# Copy Shader files to build
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying engine assets to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Assets ${PROJECT_BINARY_DIR}/Assets > copy_assets.log 2>&1
        COMMENT "Copying Shaders to build directory")
