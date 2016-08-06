add_library(foundation Node.cpp HashMap.cpp Action.cpp FiniteAction.cpp InstantAction.cpp)

target_include_directories(foundation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
