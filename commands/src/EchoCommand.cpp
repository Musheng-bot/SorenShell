//
// Created by musheng on 9/7/25.
//

#include "EchoCommand.hpp"
#include <iostream>
#include "Base.hpp"

namespace SorenShell {
	int EchoCommand::execute(std::vector<std::string> args) {
		for (const auto& arg : args) {
			std::cout << arg << " ";
		}
		std::cout << std::endl;
		return RET_EXIT_SUCCESS;
	}
} // SorenShell