cmake_minimum_required(VERSION 3.2)

project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Main
add_executable(
	Main 
	src/edge.h
	src/edge.cpp
	src/kruskal.cpp
	src/vector.h
	src/vector.cpp
	src/queue.h
	src/queue.cpp
	src/treeAVL.h
	src/treeAVL.cpp
	src/vertex.h
	src/vertex.cpp
)

# Test
add_executable(
	Test 
	test/main.cpp
)
target_link_libraries(
  Test
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(Test)
