//
// Created by musheng on 9/2/25.
//

#include "../include/Command.hpp"

#include <utility>

namespace SorenShell {
	Command::Command(const std::vector<std::string> &args) :
		args_(args) {

	}

	Command::~Command() = default;
} // SorenShell