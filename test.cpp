#include <iostream>

#include "UserManager.hpp"

int main(int argc, char** argv) {
	auto &manager = SorenShell::UserManager::getInstance();
	manager.addUser("musheng", 0, "musheng685", true);
}