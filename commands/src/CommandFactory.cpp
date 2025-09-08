//
// Created by musheng on 9/7/25.
//

#include "../include/CommandFactory.hpp"

#include <map>

#include "ExitCommand.hpp"
#include <memory>

#include "EchoCommand.hpp"
#include "LsCommand.hpp"
#include "WhoamiCommand.hpp"

namespace SorenShell {

	std::map<std::string, std::shared_ptr<Command>> CommandFactory::commands = {
		{"exit", std::make_shared<ExitCommand>()},
		{"echo", std::make_shared<EchoCommand>()},
		{"whoami", std::make_shared<WhoamiCommand>()},
		{"ls", std::make_shared<LsCommand>()},
	};

	CommandFactory::CommandFactory() = default;
	CommandFactory::~CommandFactory() = default;

	std::shared_ptr<Command> CommandFactory::create(const std::string &command) {
		if (commands.contains(command)) {
			return commands[command];
		}
		return nullptr;
	}
} // SorenShell