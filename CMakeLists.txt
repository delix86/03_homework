cmake_minimum_required(VERSION 3.5)

project(03.homework)

SET(target "guess_the_number")

add_executable(
	${target} 
	${target}.cpp
)

target_compile_features(${target}  PUBLIC cxx_std_17)
set_target_properties(${target}  PROPERTIES CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${target}  PRIVATE
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target}  PRIVATE
        /W4
        /WX
    )
endif()