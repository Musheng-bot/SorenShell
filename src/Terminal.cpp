//
// Created by musheng on 9/2/25.
//

#include "Terminal.hpp"
#include "../commands/include/CommandFactory.hpp"
#include "Base.hpp"
#include <iostream>
#include <sstream>

namespace SorenShell {

	Terminal::Terminal() :
		user_manager_(UserManager::getInstance()),
		hardware_manager_(HardwareManager::getInstance()) {
	}

	Terminal::~Terminal() = default;

	int Terminal::start() {
		if (is_running_) {
			return RET_RUNNING;
		}
		is_running_ = true;
		return run();
	}

	int Terminal::execute() const {
		auto command = CommandFactory::create(command_);
		if (command == nullptr) {
			std::cout << "Command not found" << std::endl;
			return RET_COMMAND_NOT_FOUND;
		}
		return command->execute(args_);
	}

	int Terminal::run() {
		std::string user_name = user_manager_.getUser(user_manager_.getUid()).userName();
		std::string host_name = hardware_manager_.getHostName();

		while (is_running_) {
			std::cout << "<SorenShell> ";
			std::cout << user_name << '@' << host_name << ':' << current_dir_ << '$' << ' ';
			int ret = readCommand();
			int res = RET_EXIT_SUCCESS;
			if (ret == RET_EXIT_SUCCESS) {
				res = this->execute();
			}
			else if (ret == RET_PLEASE_STOP) {
				this->stop();
			}
			else {
				std::cout << "Command has not been executed!" << std::endl;
			}

			if (res == RET_PLEASE_STOP) {
				stop();
			}
		}
		return RET_EXIT_SUCCESS;
	}

	int Terminal::readCommand() {
		std::string command;
		std::getline(std::cin, command);
		if (std::cin.eof()) {
			std::cin.clear();
			return RET_PLEASE_STOP; //EOF
		}
		if (command.size() > MAX_COMMAND_LENGTH) {
			std::cerr << "command too long" << std::endl;
			return RET_COMMAND_TOO_LONG;
		}
		parseCommand(command);
		return RET_EXIT_SUCCESS;
	}

	void Terminal::parseCommand(const std::string &command) {
		std::stringstream ss(command);
		bool first = true;
		command_.clear();
		args_.clear();
		while (ss.good()) {
			std::string token;
			ss >> token;
			if (first) {
				first = false;
				command_ = token;
			}
			else {
				args_.push_back(token);
			}
		}
		if (command_ == "ls") {
			bool found = false;
			for (auto &arg : args_) {
				if (arg[0] != '-') {
					found = true;
				}
			}
			if (!found) {
				args_.emplace_back(current_dir_);
			}
		}
	}

	int Terminal::stop() {
		is_running_ = false;
		return RET_EXIT_SUCCESS;
	}

	bool Terminal::isRunning() const {
		return is_running_;
	}
} // SorenShell