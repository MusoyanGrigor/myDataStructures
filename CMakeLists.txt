cmake_minimum_required(VERSION 3.30)
project(myDataStructures)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(EXEC_NAME ${SRC_FILE} NAME_WE)

    file(READ ${SRC_FILE} CONTENTS)

    if("${CONTENTS}" MATCHES "int main\\(.*\\)")
        add_executable(${EXEC_NAME} ${SRC_FILE} src/main.cpp
                include/string.h
                src/string.cpp
                include/utils.h
                src/utils.cpp
                include/array.h
                include/node.h
                include/forward_list.h
                include/list.h
                include/deque.h
        )

        target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    endif()
endforeach()
