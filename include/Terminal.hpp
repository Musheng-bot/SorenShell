//
// Created by musheng on 9/2/25.
//

#ifndef SORENSHELL_TERMINAL_HPP
#define SORENSHELL_TERMINAL_HPP

#include <string>
#include <vector>

#include "../Hardware/include/HardwareManager.hpp"
#include "../User/include/User.hpp"

namespace SorenShell {
	class Terminal {
		public:
			Terminal();
			~Terminal();
			int start();
			int stop();
			[[nodiscard]] bool isRunning() const;



		private:
			using args_t = std::vector<std::string>;

			bool is_running_ = false;

			[[nodiscard]] int execute() const;
			int run();
			int readCommand();

			void parseCommand(const std::string &command);
	};
} // SorenShell

#endif //SORENSHELL_TERMINAL_HPP