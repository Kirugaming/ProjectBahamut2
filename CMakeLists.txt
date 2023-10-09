cmake_minimum_required(VERSION 3.22)
project(ProjectBahamut)

set(CMAKE_CXX_STANDARD 14)





# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
set(SOURCE_FILES window.cpp window.h Shader.cpp Shader.h Mesh.cpp Mesh.h Model.cpp Model.h)
set(LIB_FILES stb_image.h glad.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${LIB_FILES})

# SDL2
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2_image/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE include/)

# assimp
set(BUILD_SHARED_LIBS ON)
add_subdirectory("lib/assimp/")
target_link_libraries(${PROJECT_NAME} assimp::assimp)

# glm
add_subdirectory("lib/glm/")
target_link_libraries(${PROJECT_NAME} glm)

