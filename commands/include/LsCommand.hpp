//
// Created by musheng on 9/8/25.
//

#ifndef SORENSHELL_LSCOMMAND_HPP
#define SORENSHELL_LSCOMMAND_HPP
#include <filesystem>
#include "Command.hpp"

namespace SorenShell {
	class LsCommand final : public Command {
		DEFINE_COMMAND_CLASS(LsCommand)
		public:
			void showAsList(const std::vector<std::filesystem::directory_entry> &entries) const;
			void showNormal(const std::vector<std::filesystem::directory_entry> &entries) const;
		private:
			bool list_ = false;
			bool all_ = false;
			std::string path_;
			bool path_found_ = false;

			static std::string getPermissionString(std::filesystem::file_status status);
			static std::string formatTime(const std::filesystem::file_time_type& ft);
	};
} // SorenShell

#endif //SORENSHELL_LSCOMMAND_HPP