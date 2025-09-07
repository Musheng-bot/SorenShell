//
// Created by musheng on 9/7/25.
//

#include "ExitCommand.hpp"

#include "Base.hpp"
namespace SorenShell {
	int ExitCommand::execute(std::vector<std::string> args) {
		return RET_PLEASE_STOP;
	}
} // SorenShell