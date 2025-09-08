//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_BASE_HPP
#define SORENSHELL_BASE_HPP

#include <csignal>
namespace SorenShell {
	enum ReturnCode {
		RET_EXIT_SUCCESS = 0,
		RET_EXECUTION_FAILURE = 1,
		RET_COMMAND_NOT_FOUND = 2,
		RET_PERMISSION_DENIED = 3,
		RET_RANGE_ERROR = 4,
		RET_OUT_OF_MEMORY = 5,
		RET_ARGUMENT_ERROR = 6,
		RET_OK = 7,
	};
	constexpr int MAX_COMMAND_LENGTH = 100;
	// inline volatile sig_atomic_t exit_status = 0;
	// inline void signal_handler() {}

}

#endif //SORENSHELL_BASE_HPP