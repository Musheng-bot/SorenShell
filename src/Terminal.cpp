//
// Created by musheng on 9/2/25.
//

#include "Terminal.hpp"
#include <iostream>

namespace SorenShell {
	Terminal::Terminal() = default;

	Terminal::~Terminal() = default;

	int Terminal::start() {
		if (is_running_) {
			return RET_RUNNING;
		}
		is_running_ = true;
	}

	int Terminal::execute(const std::string &command) {
		if (command == "exit") {
			this->stop();
			return RET_EXIT_SUCCESS;
		}

		return 1;
	}

	int Terminal::stop() {
		is_running_ = false;
		return RET_EXIT_SUCCESS;
	}
} // SorenShell