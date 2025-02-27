cmake_minimum_required(VERSION 3.30)
project(myDataStructures)

set(CMAKE_CXX_STANDARD 20)

# Add the include directory to the project
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all .cpp files in the src directory
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Iterate over the .cpp files and create an executable for each one
foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(EXEC_NAME ${SRC_FILE} NAME_WE)

    # Check if the file contains a main function
    file(READ ${SRC_FILE} CONTENTS)
    if("${CONTENTS}" MATCHES "int main\\(.*\\)")

        # Create the executable for this file
        add_executable(${EXEC_NAME} ${SRC_FILE} src/vector.cpp)

        # Make sure the include directory is included for this executable
        target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    endif()
endforeach()
