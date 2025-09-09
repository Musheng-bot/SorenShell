//
// Created by musheng on 9/2/25.
//

#ifndef SORENSHELL_TERMINAL_HPP
#define SORENSHELL_TERMINAL_HPP

#include <string>
#include <vector>
#include "CommandFactory.hpp"

namespace SorenShell {
	class Terminal {
		public:
			Terminal();
			~Terminal();
			int start();

			void stop();
			[[nodiscard]] bool isRunning() const;
			void changeWorkingDirectory(const std::string &new_dir);

		private:
			using args_t = std::vector<std::string>;
			std::string current_working_directory_;
			bool is_running_ = false;
			std::string command_str_;
			std::unique_ptr<Command> command_;
			args_t args_;
			CommandFactory &command_factory_;

			[[nodiscard]] int execute();
			int run();
			int readCommand();

			void parseCommand(const std::string &command);
			void handleReturnCode(int res);
	};
} // SorenShell

#endif //SORENSHELL_TERMINAL_HPP