# add_executable(TestExecutableName TestFileName.cpp)
add_executable(NodeTest NodeTest.cpp)
add_executable(ActionTest ActionTest.cpp)
add_executable(ConditionTest ConditionTest.cpp)

# target_link_libraries(TestExecutableName LINK_PUBLIC LibraryName)
# Where LibraryName is foundation
target_link_libraries(NodeTest LINK_PUBLIC foundation)
target_link_libraries(ActionTest LINK_PUBLIC foundation)
target_link_libraries(ConditionTest LINK_PUBLIC foundation)

# For SFML testing
# find_package(SFML 2 REQUIRED system window graphics network audio)
# if(SFML_FOUND)
#   include_directories(${SFML_INCLUDE_DIR})
#   target_link_libraries(AssetManagementTests ${SFML_LIBRARIES} hiillos)
# endif()

# Add tests
# add_test(test_name_test TestExecutableName)
add_test(node_test NodeTest)
add_test(action_test ActionTest)
add_test(condition_test ConditionTest)
