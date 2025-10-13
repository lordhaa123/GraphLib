# Add a test executable
add_executable(GraphLibTests Test_path_finding.cpp)

# Link the test executable against our library and Catch2
target_link_libraries(GraphLibTests PRIVATE GraphLibCore Catch2::Catch2WithMain)

# Add the test to CTest
include(CTest)
add_test(NAME PathFindingTests COMMAND GraphLibTests)
