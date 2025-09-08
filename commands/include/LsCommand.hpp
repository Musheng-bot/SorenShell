//
// Created by musheng on 9/8/25.
//

#ifndef SORENSHELL_LSCOMMAND_HPP
#define SORENSHELL_LSCOMMAND_HPP
#include <filesystem>
#include "Command.hpp"

namespace SorenShell {
	class LsCommand final : public Command {
		public:
			LsCommand() = default;
			~LsCommand() override = default;
			int execute(std::vector<std::string> args) override;
		private:
			bool all_ = false;
			bool list_ = false;
			bool help_ = false;
			std::filesystem::path dir_name_;

			int helpExecute();
			int normalExecute();
			int listExecute();
			void reset();
	};
} // SorenShell

#endif //SORENSHELL_LSCOMMAND_HPP