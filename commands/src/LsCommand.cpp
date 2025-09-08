//
// Created by musheng on 9/8/25.
//

#include "LsCommand.hpp"

#include "Base.hpp"
#include <filesystem>
#include <iostream>

namespace SorenShell {
	int LsCommand::execute(std::vector<std::string> args) {
		// if (args.empty()) {
		// 	std::cout << "Usage: ls <dir_name> [-a] [-l] [-h]\n" << std::endl;
		// }
		for (const auto& arg : args) {
			if (arg[0] == '-') {
				if (arg == "-a") {
					all_ = true;
				}
				else if (arg == "-l") {
					list_ = true;
				}
				else if (arg == "-h") {
					help_ = true;
				}
				else {
					std::cout << "Unrecognized option: " << arg << std::endl;
					help_ = true;
				}
			}
			else {
				if (!dir_name_.empty()) {
					std::cout << "Too many parameters" << std::endl;
					help_ = true;
				}
				else {
					dir_name_ = arg;
				}
			}
		}
		int ret;
		if (help_) {
			 ret = helpExecute();
		}
		else if (list_) {
			ret = listExecute();
		}
		else {
			ret = normalExecute();
		}
		reset();
		return ret;
	}

	int LsCommand::helpExecute() {
		std::cout << "Usage: ls <directory_name> [-a] [-l] [-h]" << std::endl;
		return RET_EXIT_SUCCESS;
	}

	int LsCommand::normalExecute() {
		try {
			if (!std::filesystem::exists(dir_name_)) {
				std::cout << "Directory does not exist" << std::endl;
				return RET_EXIT_FAILURE;
			}
			if (!std::filesystem::is_directory(dir_name_)) {
				std::cout << "Target is not a directory" << std::endl;
				return RET_EXIT_FAILURE;
			}

			for (const auto& entry : std::filesystem::directory_iterator(dir_name_)) {
				const auto& path = entry.path();
				if (!all_ && path.filename().string()[0] == '.') {
					continue;
				}
				std::cout << path.filename().string() << std::endl;
			}
			return RET_EXIT_SUCCESS;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			return RET_EXCEPTION_HAPPEN;
		}
	}

	int LsCommand::listExecute() {
		return this->normalExecute();
	}

	void LsCommand::reset() {
		all_ = false;
		list_ = false;
		help_ = false;
		dir_name_.clear();
	}
} // SorenShell