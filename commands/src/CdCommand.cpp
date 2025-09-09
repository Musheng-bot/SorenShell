//
// Created by musheng on 9/9/25.
//

#include "CdCommand.hpp"
#include <filesystem>
#include <iostream>
#include "Base.hpp"
#include "Terminal.hpp"

namespace SorenShell {
	void CdCommand::help() {
		std::cout << "Usage: cd [$relative_path, $absolute_path]" << std::endl;
	}

	void CdCommand::preprocess(const std::string &current_path) {
		current_path_ = current_path;
		path_ = ".";
		handleOptionalParameters();
		if (!path_.empty() && path_[0] == '/') {
			mode = ABSOLUTE_MODE;
		}
	}

	void CdCommand::handleOptionalParameters() {
		bool found = false;
		for (const auto &arg : args_) {
			if (arg == "-h" || arg == "--help") {
				help_ = true;
			}
			else if (!arg.empty()){
				if (!found) {
					found = true;
					path_ = arg;
				}
				else {
					help_ = true;
				}
			}
		}
	}

	int CdCommand::execute() {
		if (help_) {
			help();
		}
		std::filesystem::path path;
		if (mode == 0) {
			path = path_;
		}
		else if (mode == 1) {
			if (path_ == ".") {
				path = current_path_;
			}
			else if (path_ == "..") {
				path = current_path_.substr(
					0,
					current_path_.find_last_of('/')
				);
				if (path.empty()) {
					path = "/";
				}
			}
			else{
				path = current_path_ + "/" + path_;
			}
		}

		if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
			terminal_.changeWorkingDirectory(path.string());
			return RET_EXIT_SUCCESS;
		}
		std::cout << "ERROR: Can't change to \"" << path.string() << "\"" << std::endl;
		return EXIT_FAILURE;
	}



} // SorenShell