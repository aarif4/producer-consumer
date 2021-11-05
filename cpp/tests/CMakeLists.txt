# Locate GTest

# the old way is this
### find_package(GTest REQUIRED)
### include_directories(${GTEST_INCLUDE_DIRS})

# this is a new era - a travis era
include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(executeTests test.cpp)
# the old way
### target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread producer consumer semaphore)
# the new era
target_link_libraries(executeTests gtest pthread producer consumer semaphore)
