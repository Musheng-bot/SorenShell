//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_BASE_HPP
#define SORENSHELL_BASE_HPP

#include <csignal>
namespace SorenShell {
	enum ReturnCode {
		RET_RUNNING = 99,
		RET_EXIT_SUCCESS = 0,
		RET_EXIT_FAILURE = 1,
		RET_PLEASE_STOP = 2,
		RET_COMMAND_NOT_FOUND = 3,
		RET_COMMAND_TOO_LONG = 4,
	};
	constexpr int MAX_COMMAND_LENGTH = 100;
	// inline volatile sig_atomic_t exit_status = 0;
	// inline void signal_handler() {}

}

#endif //SORENSHELL_BASE_HPP