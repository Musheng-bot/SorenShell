//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_WHOAMICOMMAND_HPP
#define SORENSHELL_WHOAMICOMMAND_HPP
#include "Command.hpp"

namespace SorenShell {
	class WhoamiCommand final : public Command {
		DEFINE_COMMAND_CLASS(WhoamiCommand)
	};
} // SorenShell

#endif //SORENSHELL_WHOAMICOMMAND_HPP