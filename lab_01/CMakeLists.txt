cmake_minimum_required(VERSION 4.3.0)
project(app)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)