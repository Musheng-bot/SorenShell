cmake_minimum_required(VERSION 4.0)
project(SorenShell)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)
find_package(yaml-cpp REQUIRED)

### UserManagement模块
add_library(UserManagement SHARED
		User/include/User.hpp
		User/src/User.cpp
)
target_include_directories(UserManagement
		PRIVATE include /usr/local/include User/include)
target_link_libraries(UserManagement PRIVATE
		OpenSSL::Crypto yaml-cpp
)

### HardwareManagement模块
add_library(HardwareManagement SHARED
		Hardware/include/HardwareManager.hpp
		Hardware/src/HardwareManager.cpp
)
target_include_directories(HardwareManagement PUBLIC include)

### Commands module
file(GLOB COMMAND_HEADERS
		commands/include/Command.hpp commands/include/CommandFactory.hpp commands/include/*.hpp
)
file(GLOB COMMAND_SOURCES
		commands/src/Command.cpp commands/src/CommandFactory.cpp commands/src/*.cpp
)
add_library(Commands SHARED
	${COMMAND_HEADERS} ${COMMAND_SOURCES}
		commands/src/LsCommand.cpp
		commands/include/LsCommand.hpp
)
target_include_directories(Commands PRIVATE
		include
		commands/include
		User/include
		Hardware/include)

### Terminal module
add_library(Terminal SHARED
	include/Terminal.hpp
	src/Terminal.cpp
)
target_include_directories(Terminal PUBLIC
		include commands/include Hardware/include User/include)
target_link_libraries(Terminal PUBLIC HardwareManagement UserManagement Commands)

### FileSystem module
add_library(FileSystem SHARED
		FileSystem/include/File.hpp
		FileSystem/src/File.cpp
		FileSystem/include/Directory.hpp
		FileSystem/src/Directory.cpp
		FileSystem/src/BaseFile.cpp
		FileSystem/include/BaseFile.hpp
		FileSystem/src/FileSystem.cpp
		FileSystem/include/FileSystem.hpp
)
target_include_directories(FileSystem PUBLIC include)

###
add_executable(SorenShell main.cpp
		include/Base.hpp
)
target_include_directories(SorenShell PUBLIC include commands/include /usr/local/include)
target_link_libraries(SorenShell
		PRIVATE
		UserManagement
		HardwareManagement
		Terminal
		Commands
)


