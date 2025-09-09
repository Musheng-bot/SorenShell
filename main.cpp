#include <iostream>

#include "Terminal.hpp"
#include "Base.hpp"


int main() {
	SorenShell::Terminal terminal;
	int ret = terminal.start();
	if (ret == SorenShell::RET_EXIT_SUCCESS) {
		std::cout << "Successfully exit!" << std::endl;
	}
	else if (ret == SorenShell::RET_EXIT_FAILURE) {
		std::cout << "Failed to exit!" << std::endl;
	}
	terminal.stop();
	return 0;
}
