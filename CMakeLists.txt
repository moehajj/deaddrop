cmake_minimum_required(VERSION 3.5)
project(deaddrop)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory (libs)

add_executable (sender sender.c)
target_link_libraries (sender LINK_PUBLIC util)

add_executable (receiver receiver.c)
target_link_libraries (receiver LINK_PUBLIC util)

find_package(Threads REQUIRED)

add_executable(duplex duplex.c)
target_link_libraries(duplex LINK_PUBLIC Threads::Threads util)
target_compile_definitions(duplex PRIVATE CSTATE_IDENT=0)

add_executable(duplex2 duplex.c)
target_link_libraries(duplex2 LINK_PUBLIC Threads::Threads util)
target_compile_definitions(duplex2 PRIVATE CSTATE_IDENT=1)
