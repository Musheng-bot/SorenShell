//
// Created by musheng on 9/7/25.
//

#include "ExitCommand.hpp"
#include <iostream>
#include "Base.hpp"

namespace SorenShell {
	int ExitCommand::execute() {
		if (help_) {
			help();
			return RET_EXIT_SUCCESS;
		}
		return RET_TERMINATION;
	}
	void ExitCommand::preprocess(const std::string &current_path) {
		handleOptionalParameters();
	}

	void ExitCommand::handleOptionalParameters() {
		for (auto &args : args_) {
			if (args == "-h" || args == "--help") {
				help_ = true;
			}
			else {
				help();
				exit(RET_INCORRECT_USAGE);
			}
		}
	}

	void ExitCommand::help() {
		std::cout << "Usage: exit [options]\n";
		std::cout << "Options: \n";
		std::cout << "\t-h show this page" << std::endl;
	}


} // SorenShell