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
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g -fPIC -Wformat")




################################################################################
# Build Libraries
#-------------------------------------------------------------------------------
# - Build all external libraries
# - First make sure that CMake can see the .hpp files in inc/ folder
# - Make a Static Libary called simple_library that basically packages any class
#   you've made
################################################################################
include_directories("inc")
add_library(semaphore STATIC
src/semaphore.cpp
inc/semaphore.hpp
)
add_library(queue STATIC
src/queue.cpp
inc/queue.hpp
)
target_link_libraries(queue semaphore)
add_library(producer STATIC
src/producer.cpp
inc/producer.hpp
)
target_link_libraries(producer queue)
add_library(consumer STATIC
src/consumer.cpp
inc/consumer.hpp
)
target_link_libraries(consumer queue)




################################################################################
# Build Project
################################################################################
add_executable(pushpull src/main.cpp)
target_link_libraries(pushpull producer consumer queue semaphore pthread)
install(TARGETS pushpull DESTINATION bin)



################################################################################
# Build Unit Testing Module
#-------------------------------------------------------------------------------
# This is where you keep all unit testing code
################################################################################
message (STATUS "Making unit testing modules for this application")
add_subdirectory(tests)
add_subdirectory(doc)
