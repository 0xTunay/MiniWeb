cmake_minimum_required(VERSION 3.10)

project(miniweb)

set(CMAKE_C_STANDARD 99)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(SRC
        ${SRC_DIR}/mime.c
        ${SRC_DIR}/request.c
        ${SRC_DIR}/server.c
        ${SRC_DIR}/response.c
)

set(INCLUDE
        ${INCLUDE_DIR}/mime.h
        ${INCLUDE_DIR}/request.h
        ${INCLUDE_DIR}/server.h
        ${INCLUDE_DIR}/response.h
)

add_library(core STATIC
        ${SRC}
)

add_executable(miniweb main.c )


target_link_libraries(miniweb PRIVATE core)

set_target_properties(miniweb PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_include_directories(core PUBLIC ${INCLUDE_DIR})
target_include_directories(miniweb PRIVATE ${INCLUDE_DIR})