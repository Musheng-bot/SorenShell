//
// Created by musheng on 9/2/25.
//

#ifndef SORENSHELL_TERMINAL_HPP
#define SORENSHELL_TERMINAL_HPP

#include <string>

namespace SorenShell {
	class Terminal {
		public:
			Terminal();
			~Terminal();
			int start();
			int execute(const std::string &command);
			int stop();

			enum {
				RET_RUNNING = 99,
				RET_EXIT_SUCCESS = 0,
			};

		private:
			bool is_running_ = false;
			std::string user_name_;
			std::string current_dir_;
			std::string device_name_;
	};
} // SorenShell

#endif //SORENSHELL_TERMINAL_HPP