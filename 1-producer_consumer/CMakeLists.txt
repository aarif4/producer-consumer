project(producer_consumer_problem)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

################################################################################
# Add Flags
#-------------------------------------------------------------------------------
# - Make sure that we use C++11 standard when compiling
# - Use -O3 to optmize the code
################################################################################
enable_testing()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g -fPIC")




################################################################################
# Build Libraries
#-------------------------------------------------------------------------------
# - Build all external libraries
# - First make sure that CMake can see the .hpp files in inc/ folder
# - Make a Static Libary called simple_library that basically packages any class
#   you've made
################################################################################
include_directories("inc")
add_library(producer STATIC
src/producer.cpp
inc/producer.hpp
)
add_library(consumer STATIC
src/consumer.cpp
inc/consumer.hpp
)



################################################################################
# Build Project
################################################################################
add_executable(main src/main.cpp)
target_link_libraries(main producer consumer)
install(TARGETS main DESTINATION bin)



################################################################################
# Build Unit Testing Module
#-------------------------------------------------------------------------------
# This is where you keep all unit testing code
################################################################################
message (STATUS "Making unit testing modules for this application")
add_subdirectory(tests)
add_subdirectory(doc)
