cmake_minimum_required(VERSION 3.29)
project(Engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "D:/libs/SFML3/lib/cmake/SFML")

file(COPY 
    "resources"
DESTINATION "${CMAKE_BINARY_DIR}")

set(HEADER_FILES
    include/Config.hpp
    include/Engine.hpp
    include/Mesh.hpp
    include/Camera.hpp
    include/Render.hpp
    include/linalg/Vec3d.hpp
    include/linalg/Triangle.hpp
    include/linalg/Mat4x4.hpp
)

set(SOURCE_FILES
    src/Main.cpp
    src/Engine.cpp
    src/Mesh.cpp
    src/Camera.cpp
    src//Render.cpp
    src/linalg/Vec3d.cpp
    src/linalg/Triangle.cpp
    src/linalg/Mat4x4.cpp
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(Engine ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(Engine PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Engine PRIVATE SFML::Graphics)