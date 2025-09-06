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
			explicit Command(std::string command, const std::vector<std::string> &args = {});
			virtual ~Command();
			virtual int execute() = 0;

		protected:
			std::string command_;
			std::vector<std::string> args_;
	};
} // SorenShell

#endif //SORENSHELL_COMMAND_HPP