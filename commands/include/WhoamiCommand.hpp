//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_WHOAMICOMMAND_HPP
#define SORENSHELL_WHOAMICOMMAND_HPP
#include "Command.hpp"

namespace SorenShell {
	class WhoamiCommand : public Command {
		public:
			WhoamiCommand() = default;
			~WhoamiCommand() override = default;
			int execute(std::vector<std::string> args) override;

	};
} // SorenShell

#endif //SORENSHELL_WHOAMICOMMAND_HPP