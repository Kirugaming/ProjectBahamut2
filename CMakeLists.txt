cmake_minimum_required(VERSION 3.22)
project(ProjectBahamut)

set(CMAKE_CXX_STANDARD 14)



# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
set(SOURCE_FILES window.cpp window.h Shader.cpp Shader.h Mesh.cpp Mesh.h Model.cpp Model.h Transformation.cpp Transformation.h GameObject.cpp GameObject.h)
set(LIB_FILES glad.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${LIB_FILES})


set(BUILD_SHARED_LIBS ON)

target_include_directories(${PROJECT_NAME} PRIVATE include/)

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


# Copy Needed DLLs to build
set(lib_dlls
        ${PROJECT_BINARY_DIR}/lib/assimp/bin/assimpd.dll
        ${PROJECT_BINARY_DIR}/lib/SDL2/SDL2d.dll
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
        COMMAND ${CMAKE_COMMAND} -E echo "Copying Shaders to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shaders ${PROJECT_BINARY_DIR}/shaders > copy_shaders.log 2>&1
        COMMENT "Copying Shaders to build directory")