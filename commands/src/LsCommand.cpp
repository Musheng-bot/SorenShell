//
// Created by musheng on 9/8/25.
//

#include "LsCommand.hpp"

#include "Base.hpp"
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <filesystem>
#include <iostream>
#include <grp.h>
#include "User.hpp"

namespace SorenShell {
	void LsCommand::help() {
		std::cout << "Usage: ls <dir_name> [options]" << std::endl;
		std::cout << "[Options: ]" << std::endl;
		std::cout << "  -h, --help: Show this help" << std::endl;
		std::cout << "  -a, --all: Show all files, including hidden ones" << std::endl;
		std::cout << "  -l, --list: Show as a list" << std::endl;
	}

	void LsCommand::showAsList(const std::vector<std::filesystem::directory_entry> &entries) const {
		std::filesystem::path path(path_);
		// uintmax_t total_blocks = 0;
		// for (const auto& entry : std::filesystem::directory_iterator(path)) {
		// 	if (entry.is_directory()) {
		// 		total_blocks += 1;
		// 	}
		// 	else if (entry.is_regular_file()) {
		// 		total_blocks += (entry.file_size() + 511) / 512;
		// 	}
		// }
		// std::cout << "total: " << total_blocks << '\n';
		for (const auto& entry : entries) {
			auto file_name = entry.path().filename().string();
			if (!file_name.empty() && file_name[0] == '.' && !all_) {
				continue;
			}
			struct stat file_stat{};
			if (stat(entry.path().string().c_str(), &file_stat) != 0) {
				std::cout << entry.path() << " file not found." << std::endl;
				continue;
			}
			std::cout <<
				getPermissionString(entry.status()) << ' ' <<
				std::setw(4) << std::right << entry.hard_link_count() << ' ' <<
				std::setw(8) << std::right << User::getUserName(file_stat.st_uid) << ' ' <<
				std::setw(8) << std::right << getgrgid(file_stat.st_gid)->gr_name << ' ' <<
				std::setw(8) << std::right << file_stat.st_size << ' ' <<
				formatTime(entry.last_write_time()) << ' ' <<
				file_name << ' ' <<
			'\n';
		}
		std::cout << std::flush;
	}

	void LsCommand::showNormal(const std::vector<std::filesystem::directory_entry> &entries) const {
		std::filesystem::path path(path_);
		for (const auto& entry : entries) {
			auto file_name = entry.path().filename().string();
			if (!(!file_name.empty() && file_name[0] == '.' && !all_)) {
				std::cout << file_name << ' ';
			}
		}
		std::cout << std::endl;
	}

	std::string LsCommand::getPermissionString(std::filesystem::file_status status) {
		std::string perm;

		// 确定文件类型
		if (std::filesystem::is_regular_file(status)) perm += '-';
		else if (std::filesystem::is_directory(status)) perm += 'd';
		else if (std::filesystem::is_symlink(status)) perm += 'l';
		else if (std::filesystem::is_character_file(status)) perm += 'c';
		else if (std::filesystem::is_block_file(status)) perm += 'b';
		else if (std::filesystem::is_fifo(status)) perm += 'p';
		else if (std::filesystem::is_socket(status)) perm += 's';
		else perm += '?';

		// 用户权限
		auto perms = status.permissions();
		perm += (perms & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? 'r' : '-';
		perm += (perms & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? 'w' : '-';
		perm += (perms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? 'x' : '-';

		// 组权限
		perm += (perms & std::filesystem::perms::group_read) != std::filesystem::perms::none ? 'r' : '-';
		perm += (perms & std::filesystem::perms::group_write) != std::filesystem::perms::none ? 'w' : '-';
		perm += (perms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? 'x' : '-';

		// 其他用户权限
		perm += (perms & std::filesystem::perms::others_read) != std::filesystem::perms::none ? 'r' : '-';
		perm += (perms & std::filesystem::perms::others_write) != std::filesystem::perms::none ? 'w' : '-';
		perm += (perms & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? 'x' : '-';

		return perm;
	}

	std::string LsCommand::formatTime(const std::filesystem::file_time_type &ft) {
		// 转换为系统时间
		auto tt = std::chrono::system_clock::to_time_t(
			std::chrono::file_clock::to_sys(ft)
		);
		std::tm tm = *std::localtime(&tt);

		std::stringstream ss;
		ss << std::put_time(&tm, "%b %d %H:%M");
		return ss.str();
	}

	void LsCommand::preprocess(const std::string &current_path) {
		path_ = current_path;
		path_found_ = false;
		handleOptionalParameters();
	}

	void LsCommand::handleOptionalParameters() {
		for (const auto &args : args_) {
			if (args == "-h" || args == "--help") {
				help_ = true;
			}
			else if (args == "-a" || args == "--all") {
				all_ = true;
			}
			else if (args == "-l" || args == "--list") {
				list_ = true;
			}
			else {
				if (!path_found_) {
					path_ = args;
					path_found_ = true;
				}
				else {
					std::cerr << "Unknown option: " << args << std::endl;
					return;
				}
			}
		}
	}

	int LsCommand::execute() {
		std::vector<std::filesystem::directory_entry> directory_entries;
		directory_entries.emplace_back(path_ + "/.");
		directory_entries.emplace_back(std::filesystem::path(path_ + "/.."));
		for (const auto &entry : std::filesystem::directory_iterator(path_)) {
			directory_entries.push_back(entry);
		}
		if (help_) {
			help();
		}
		else if (list_) {
			showAsList(directory_entries);
		}
		else {
			showNormal(directory_entries);
		}
		return EXIT_SUCCESS;
	}



} // SorenShell