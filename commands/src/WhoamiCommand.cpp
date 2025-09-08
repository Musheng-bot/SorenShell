//
// Created by musheng on 9/7/25.
//

#include "WhoamiCommand.hpp"

#include <iostream>

#include "Base.hpp"
#include "../../User/include/User.hpp"

namespace SorenShell {
	int WhoamiCommand::execute(std::vector<std::string> args) {
		if (!args.empty()) {
			std::cout << "Usage: whoami\n To see the current user of the terminal" << std::endl;
			return RET_COMMAND_INCORRECT_USAGE;
		}
		auto& userManager = UserManager::getInstance();
		std::cout << userManager.getUser(userManager.getUid()).userName() << std::endl;
		return RET_EXIT_SUCCESS;
	}
} // SorenShell