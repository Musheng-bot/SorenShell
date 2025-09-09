//
// Created by musheng on 9/2/25.
//

#include "Terminal.hpp"
#include "CommandFactory.hpp"
#include "Base.hpp"
#include <iostream>
#include <sstream>
#include <sys/wait.h>

#include "HardwareManager.hpp"
#include "User.hpp"

namespace SorenShell {

	Terminal::Terminal() :
		current_working_directory_(User::getHomeDirectory()),
		command_factory_(CommandFactory::getInstance())
	{}

	Terminal::~Terminal() = default;

	int Terminal::start() {
		is_running_ = true;
		return run();
	}

	int Terminal::execute() {
		command_ = command_factory_.create(command_str_, args_);
		if (command_ == nullptr) {
			std::cout << "Command not found" << std::endl;
			return RET_COMMAND_NOT_FOUND;
		}
		command_->preprocess(current_working_directory_);
		// pid_t pid = fork();
		// add pipe here.
		return command_->execute();
	}

	int Terminal::run() {
		std::string user_name = User::getUserName();
		std::string host_name = HardwareManager::getHostName();

		while (isRunning()) {
			std::cout << "<SorenShell> ";
			std::cout << user_name << '@' << host_name << ':' << current_working_directory_ << '$' << ' ';
			int ret = RET_EXIT_SUCCESS;
			switch (readCommand()) {
				case RET_EXIT_SUCCESS:
					ret = execute();
					break;
				case RET_TERMINATION:
					ret = RET_TERMINATION;
					break;
				case RET_EXIT_FAILURE:
					std::cout << "Warning! The command fails!" << std::endl;
					break;
				default:
					break;
			}
			handleReturnCode(ret);
		}
		return RET_EXIT_SUCCESS;
	}

	int Terminal::readCommand() {
		std::string command;
		std::getline(std::cin, command);
		if (std::cin.eof()) {
			std::cin.clear();
			return RET_TERMINATION; //EOF
		}
		if (command.size() > MAX_COMMAND_LENGTH) {
			std::cout << "command too long" << std::endl;
			return RET_EXIT_FAILURE;
		}
		parseCommand(command);
		return RET_EXIT_SUCCESS;
	}

	void Terminal::parseCommand(const std::string &command) {
		std::stringstream ss(command);
		bool first = true;
		command_str_.clear();
		args_.clear();
		while (ss.good()) {
			std::string token;
			ss >> token;
			if (first) {
				first = false;
				command_str_ = token;
			}
			else {
				args_.push_back(token);
			}
		}
	}

	void Terminal::handleReturnCode(int res) {
		if (res == RET_TERMINATION) {
			this->stop();
		}
		else if (res == RET_INCORRECT_USAGE) {
			command_->help();
		}
		else if (res == RET_COMMAND_NOT_FOUND) {
			std::cout << "Command " << command_str_ << " not found" << std::endl;
		}
		else if (res == RET_PERMISSION_DENIED) {
			std::cout << "Command " << command_str_ << " permission denied" << std::endl;
		}
	}

	void Terminal::stop() {
		is_running_ = false;
	}

	bool Terminal::isRunning() const {
		return is_running_;
	}
} // SorenShell