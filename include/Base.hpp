//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_BASE_HPP
#define SORENSHELL_BASE_HPP

#include <iostream>
namespace SorenShell {
	enum ReturnCode {
		RET_EXIT_SUCCESS = EXIT_SUCCESS,
		RET_EXIT_FAILURE = EXIT_FAILURE,
		RET_EXCEPTION = 3,
		RET_COMMAND_NOT_FOUND = 4,
		RET_PERMISSION_DENIED = 5,
		RET_INCORRECT_USAGE = 6,
		RET_TERMINATION = 7,
	};
	constexpr int MAX_COMMAND_LENGTH = 100;

}

#endif //SORENSHELL_BASE_HPP