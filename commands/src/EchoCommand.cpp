//
// Created by musheng on 9/7/25.
//

#include "EchoCommand.hpp"
#include <iostream>
#include "Base.hpp"

namespace SorenShell {
	int EchoCommand::execute() {
		if (help_) {
			help();
		}
		else {
			for (auto &args : args_) {
				std::cout << args << " ";
			}
			std::cout << std::endl;
		}
		return RET_EXIT_SUCCESS;
	}

	void EchoCommand::help() {
		std::cout << "Usage: echo [args]" << std::endl;
	}

	void EchoCommand::handleOptionalParameters() {
		for (const auto &args : args_) {
			if (args == "--help" || args == "-h") {
				help_ = true;
			}
		}
	}

	void EchoCommand::preprocess(const std::string &current_path) {
		handleOptionalParameters();
	}
} // SorenShell