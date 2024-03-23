
add_executable(testRubik TestRubikState.cpp)
target_include_directories(testRubik PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(testRubik PUBLIC RubikSimulator)
add_test(NAME TestRubik COMMAND testRubik)