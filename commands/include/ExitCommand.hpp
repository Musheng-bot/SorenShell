//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_EXITCOMMAND_HPP
#define SORENSHELL_EXITCOMMAND_HPP
#include "Command.hpp"

namespace SorenShell {
	class ExitCommand : public Command {
		public:
			ExitCommand() = default;
			~ExitCommand() override = default;
			int execute(std::vector<std::string> args) override;
	};
} // SorenShell

#endif //SORENSHELL_EXITCOMMAND_HPP