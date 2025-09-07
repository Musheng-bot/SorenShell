//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_ECHOCOMMAND_HPP
#define SORENSHELL_ECHOCOMMAND_HPP
#include "Command.hpp"

namespace SorenShell {
	class EchoCommand : public Command {
		public:
			EchoCommand() = default;
			~EchoCommand() override = default;
			int execute(std::vector<std::string> args) override;
	};
} // SorenShell

#endif //SORENSHELL_ECHOCOMMAND_HPP