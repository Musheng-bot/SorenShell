//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_COMMANDFACTORY_HPP
#define SORENSHELL_COMMANDFACTORY_HPP

#include <Command.hpp>
#include <map>
#include <memory>

namespace SorenShell {
	class CommandFactory {
		public:
			CommandFactory();
			~CommandFactory();
			static std::shared_ptr<Command> create(const std::string &command);
			static std::map<std::string, std::shared_ptr<Command>> commands;
	};
} // SorenShell

#endif //SORENSHELL_COMMANDFACTORY_HPP