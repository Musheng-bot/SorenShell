//
// Created by musheng on 9/7/25.
//

#include "WhoamiCommand.hpp"

#include <iostream>

#include "Base.hpp"
#include "User.hpp"

namespace SorenShell {
	void WhoamiCommand::help() {
		std::cout << "Usage: whoami" << std::endl;
	}

	void WhoamiCommand::preprocess(const std::string &current_path) {
		handleOptionalParameters();
	}

	void WhoamiCommand::handleOptionalParameters() {
		for (const auto &args : args_) {
			if (args == "--help" || args == "-h") {
				help_ = true;
			}
			else {
				help();
				exit(RET_INCORRECT_USAGE);
			}
		}
	}

	int WhoamiCommand::execute() {
		std::cout << User::getUserName() << std::endl;
		return RET_EXIT_SUCCESS;
	}




} // SorenShell