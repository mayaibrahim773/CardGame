cmake_minimum_required(VERSION 3.20)

project(GLProject LANGUAGES C CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies path
set(DEPENDENCIES_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenGL.SharedModule/dependencies"
)

set(SHARED_SRC_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenGL.SharedModule/src"
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Project executable
add_executable(GLProject

    main.cpp

    Card.cpp
    Game.cpp
    Room.cpp
    Table.cpp

    "${SHARED_SRC_DIR}/glad.c"
    "${SHARED_SRC_DIR}/stb_image.cpp"
)

# Include directories
target_include_directories(GLProject PRIVATE

    "${CMAKE_CURRENT_SOURCE_DIR}"

    "${DEPENDENCIES_DIR}/include"
)

# Library directories
target_link_directories(GLProject PRIVATE

    "${DEPENDENCIES_DIR}/libs"
)

# Link libraries
target_link_libraries(GLProject PRIVATE

    glfw3

    OpenGL::GL
)

# Copy shaders
add_custom_command(
    TARGET GLProject POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:GLProject>/shaders"
)

# Copy textures
add_custom_command(
    TARGET GLProject POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/textures"
        "$<TARGET_FILE_DIR:GLProject>/textures"
)