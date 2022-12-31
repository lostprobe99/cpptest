cmake_minimum_required(VERSION 3.16)

project(socketlab)

if(MSVC)
    # 为 msvc 指定源文件为 utf8
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
endif()

set(CMAKE_CXX_STANDARD 17)

set(INC inc src/util)

include_directories(${INC})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add_subdirectory(src/asio)
include_directories(
    src
    src/asio
)

# file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c)
aux_source_directory(src sources)
aux_source_directory(src/asio ASIO)
list(APPEND sources ${ASIO})
aux_source_directory(src/multithreading THREADING)
list(APPEND sources ${THREADING})
aux_source_directory(src/meta-programing METAP)
list(APPEND sources ${METAP})
aux_source_directory(src/http HTTP)
list(APPEND sources ${HTTP})
aux_source_directory(test TEST)
list(APPEND sources ${TEST})

# message(STATUS "Found ${sources} source files\n")

foreach(main IN LISTS sources)
    message(STATUS "Found source file ${main}")
    get_filename_component(mainname ${main} NAME_WE)
    add_executable(${mainname} ${main})
    if(WIN32)
        # 连接 winsock2.lib
        target_link_libraries(${mainname} wsock32 ws2_32)
    endif()
    target_link_libraries(${mainname} ${CONAN_LIBS})
endforeach()