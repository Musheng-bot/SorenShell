cmake_minimum_required(VERSION 4.0)
project(SorenShell)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)
find_package(yaml-cpp REQUIRED)

add_library(UserManagement
		include/UserManager.hpp
		src/UserManager.cpp
)
target_include_directories(UserManagement
		PRIVATE include /usr/local/include)
target_link_libraries(UserManagement PRIVATE
		OpenSSL::Crypto yaml-cpp
)

add_executable(SorenShell main.cpp
		src/Terminal.cpp
		src/Command.cpp
		src/UserManager.cpp
)
target_include_directories(SorenShell PRIVATE include /usr/local/include)
target_link_libraries(SorenShell PRIVATE
		OpenSSL::Crypto yaml-cpp
)

add_executable(test test.cpp)
target_include_directories(test PUBLIC include)
target_link_libraries(test PRIVATE UserManagement)

