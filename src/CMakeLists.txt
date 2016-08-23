add_library(foundation SHARED Node.cpp Action.cpp FiniteAction.cpp InstantAction.cpp RepeatingAction.cpp Condition.cpp)

target_include_directories(foundation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
