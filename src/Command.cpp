//
// Created by musheng on 9/2/25.
//

#include "Command.hpp"

#include <utility>

namespace SorenShell {
	Command::Command(std::string command, const std::vector<std::string> &args) :
		command_(std::move(command)),
		args_(args)
	{}

	Command::~Command() = default;
} // SorenShell