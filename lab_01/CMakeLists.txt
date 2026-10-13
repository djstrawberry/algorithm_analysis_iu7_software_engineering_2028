cmake_minimum_required(VERSION 4.3.0)
project(app)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

target_link_libraries(${PROJECT_NAME} PRIVATE m)