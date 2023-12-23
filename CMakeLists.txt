cmake_minimum_required(VERSION 3.5)
project(cppcrudsqlite)

set(CMAKE_CXX_STANDARD 17)

# Set the path to Boost installation
set(BOOST_ROOT /usr/local/Cellar/boost/1.83.0)  # Modify if your version differs

# Locate the required libraries
find_package(SqliteOrm REQUIRED)

# Find Jansson (add these lines)
find_library(JANSSON_LIBRARY NAMES jansson PATHS /usr/local/lib)

if(NOT JANSSON_LIBRARY)
    message(FATAL_ERROR "Jansson library not found")
endif()

include_directories(${JANSSON_INCLUDE_DIRS})
include_directories(${ASIO_DIRECTORY})

# Add your source files (including todo.cpp and todo.hpp)
add_executable(Main
    src/main.cpp
)

# Include directories for Boost and Crow
target_include_directories(Main PRIVATE 
    /usr/local/include
    /usr/local/lib
    ${BOOST_ROOT}/include
    ${CMAKE_SOURCE_DIR}/include  # Replace with your Crow include path
)

# Link against the SQLiteORM library
target_link_libraries(Main PRIVATE sqlite_orm::sqlite_orm ${JANSSON_LIBRARY})
