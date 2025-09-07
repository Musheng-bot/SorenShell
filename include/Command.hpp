//
// Created by musheng on 9/2/25.
//

#ifndef SORENSHELL_COMMAND_HPP
#define SORENSHELL_COMMAND_HPP
#include <string>
#include <vector>

namespace SorenShell {
	class Command {
		public:
			Command();
			virtual ~Command();
			virtual int execute(std::vector<std::string> args) = 0;
	};
} // SorenShell

#endif //SORENSHELL_COMMAND_HPP