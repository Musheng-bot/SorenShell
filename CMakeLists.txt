cmake_minimum_required(VERSION 4.0)
project(SorenShell)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)
find_package(yaml-cpp REQUIRED)

### UserManagement模块
add_library(UserManagement SHARED
		include/UserManager.hpp
		src/UserManager.cpp
)
target_include_directories(UserManagement
		PRIVATE include /usr/local/include)
target_link_libraries(UserManagement PRIVATE
		OpenSSL::Crypto yaml-cpp
)

### HardwareManagement模块
add_library(HardwareManagement SHARED
	include/HardwareManager.hpp
	src/HardwareManager.cpp
)
target_include_directories(HardwareManagement PUBLIC include)

### Commands module
file(GLOB COMMAND_HEADERS
	include/Command.hpp include/CommandFactory.hpp commands/include/*.hpp
)
file(GLOB COMMAND_SOURCES
	src/Command.cpp src/CommandFactory.cpp commands/src/*.cpp
)
add_library(Commands SHARED
	${COMMAND_HEADERS} ${COMMAND_SOURCES}
)
target_include_directories(Commands PRIVATE include commands/include)

### Terminal module
add_library(Terminal SHARED
	include/Terminal.hpp
	src/Terminal.cpp
)
target_include_directories(Terminal PUBLIC include)
target_link_libraries(Terminal PUBLIC HardwareManagement UserManagement Commands)

### FileSystem module
add_library(FileSystem SHARED
	include/File.hpp
	src/File.cpp
	include/Directory.hpp
	src/Directory.cpp
	src/BaseFile.cpp
	include/BaseFile.hpp
)
target_include_directories(FileSystem PUBLIC include)

###
add_executable(SorenShell main.cpp
		include/Base.hpp
)
target_include_directories(SorenShell
	PRIVATE
		include commands/include /usr/local/include)
target_link_libraries(SorenShell PRIVATE
	Terminal UserManagement HardwareManagement Commands
)

###

add_executable(test
		test.cpp
		include/Base.hpp
)
target_include_directories(test PUBLIC include commands/include /usr/local/include)
target_link_libraries(test
	PRIVATE
		UserManagement
		HardwareManagement
		Terminal
		Commands
		FileSystem
)

