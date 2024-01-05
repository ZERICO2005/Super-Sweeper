cmake_minimum_required(VERSION 3.12)

set(TOOLCHAIN_PATH "/c/msys64/mingw64")
set(BIN_PATH "${TOOLCHAIN_PATH}/bin")
set(INCLUDE_PATH "${TOOLCHAIN_PATH}/include")
set(LIB_PATH "${TOOLCHAIN_PATH}/lib")

set(SRC_DIR "./src")
set(SRC_LCD_DIR "./src-lcd")

set(PROJECT_NAME "Super-Sweeper-Windows")
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

# Compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Set C and C++ standards
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(SDL2 REQUIRED)

file(GLOB SRC_FILES "${SRC_DIR}/*.c" "${SRC_LCD_DIR}/*.c")
# Create an executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_LCD_DIR})
# Compiler Flags Debug(-g -O0) Release(-O3)
set(OPT_FLAG -g -O3)
target_compile_options(${PROJECT_NAME} PUBLIC ${OPT_FLAG} -Wall -Wextra -Werror)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 SDL2main)
