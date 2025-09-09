//
// Created by musheng on 9/7/25.
//

#include "CommandFactory.hpp"

#include <map>

#include "CdCommand.hpp"
#include "ExitCommand.hpp"
#include "EchoCommand.hpp"
#include "LsCommand.hpp"
#include "WhoamiCommand.hpp"

namespace SorenShell {
	template<typename T>
	std::unique_ptr<T> commandFunc(const std::vector<std::string> &args, Terminal &terminal) {
		return std::make_unique<T>(args, terminal);
	}

	CommandFactory::CommandFactory() {
		registerCommand("exit", commandFunc<ExitCommand>);
		registerCommand("echo", commandFunc<EchoCommand>);
		registerCommand("ls", commandFunc<LsCommand>);
		registerCommand("whoami", commandFunc<WhoamiCommand>);
		registerCommand("cd", commandFunc<CdCommand>);
	}

	CommandFactory &CommandFactory::getInstance() {
		static CommandFactory instance;
		return instance;
	}

	CommandFactory::~CommandFactory() = default;

	std::unique_ptr<Command> CommandFactory::create(const std::string &command, const std::vector<std::string>& args, Terminal &terminal) {
		if (commands_.contains(command)) {
			return commands_[command](args, terminal);
		}
		return nullptr;
	}

	void CommandFactory::registerCommand(const std::string& command, const Function& function) {
		commands_[command] = function;
	}
} // SorenShell