cmake_minimum_required(VERSION 3.29)
project(Engine CXX)

set(CMAKE_CXX_STANDARD 17)

file(COPY 
    "resources"
DESTINATION "${CMAKE_BINARY_DIR}")

set(HEADER_FILES
    include/Config.hpp
    include/Engine.hpp
    include/Mesh.hpp
    include/Camera.hpp
    include/Color.hpp
    include/Light.hpp
    include/Render.hpp
    include/DepthBuffer.hpp
    include/math/Vec2d.hpp
    include/math/Vec3d.hpp
    include/math/Triangle.hpp
    include/math/Mat4x4.hpp
)

set(SOURCE_FILES
    src/Main.cpp
    src/Engine.cpp
    src/Mesh.cpp
    src/Camera.cpp
    src/Color.cpp
    src/Light.cpp
    src/Render.cpp
    src/DepthBuffer.cpp
    src/math/Vec2d.cpp
    src/math/Vec3d.cpp
    src/math/Triangle.cpp
    src/math/Mat4x4.cpp
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(Engine ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(Engine PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Engine PRIVATE SFML::Graphics)