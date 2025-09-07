//
// Created by musheng on 9/2/25.
//

#ifndef SORENSHELL_TERMINAL_HPP
#define SORENSHELL_TERMINAL_HPP

#include <string>
#include <vector>

#include "HardwareManager.hpp"
#include "UserManager.hpp"

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
			UserManager &user_manager_;
			HardwareManager &hardware_manager_;
			std::string current_dir_ = "~";
			std::string command_;
			args_t args_;

			[[nodiscard]] int execute() const;
			int run();
			int readCommand();

			void parseCommand(const std::string &command);
	};
} // SorenShell

#endif //SORENSHELL_TERMINAL_HPP