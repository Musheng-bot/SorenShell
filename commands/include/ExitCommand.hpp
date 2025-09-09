//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_EXITCOMMAND_HPP
#define SORENSHELL_EXITCOMMAND_HPP
#include "Command.hpp"

namespace SorenShell {
	class ExitCommand final : public Command {
		DEFINE_COMMAND_CLASS(ExitCommand)
	};
} // SorenShell

#endif //SORENSHELL_EXITCOMMAND_HPP