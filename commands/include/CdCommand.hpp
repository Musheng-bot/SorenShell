//
// Created by musheng on 9/9/25.
//

#ifndef SORENSHELL_CDCOMMAND_HPP
#define SORENSHELL_CDCOMMAND_HPP
#include "Command.hpp"

namespace SorenShell {
	class CdCommand final : public Command {
		DEFINE_COMMAND_CLASS(CdCommand)

		private:
			enum {
				ABSOLUTE_MODE = 0,
				RELATIVE_MODE = 1,
			};
			int mode = 1; // 0: absolute; 1: relative
			std::string current_path_;
			std::string path_;
	};
} // SorenShell

#endif //SORENSHELL_CDCOMMAND_HPP