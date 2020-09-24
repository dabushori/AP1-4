cmake_minimum_required(VERSION 3.0.0)
project(ex4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the .cpp files of the project
add_executable(ex4.out 
                client_side/client_manager.cpp
                exceptions/exceptions.cpp
                graph_path_finding/algorithms.cpp
                graph_path_finding/cache.cpp
                graph_path_finding/paths.cpp
                server_side/client_handler.cpp
                server_side/server.cpp
                main.cpp
                )

# add the library
target_link_libraries(ex4.out pthread)

# add the folders of the .h and .hpp files (to be able to include them)
target_include_directories(ex4.out PUBLIC
                            ${CMAKE_SOURCE_DIR}/client_side
                            ${CMAKE_SOURCE_DIR}/exceptions
                            ${CMAKE_SOURCE_DIR}/graph_path_finding
                            ${CMAKE_SOURCE_DIR}/server_side
                            )

# make the cache directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/cache)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
