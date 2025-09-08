//
// Created by musheng on 9/7/25.
//

#include "../include/FileSystem.hpp"
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sys/stat.h>

namespace SorenShell {
	FileSystem &FileSystem::getInstance() {
		static FileSystem instance;
		return instance;
	}

	std::shared_ptr<BaseFile> FileSystem::getFile(const std::string &abs_path) {
		if (abs_path.empty()) {
			return nullptr;
		}
		if (abs_path == "/") {
			return root_;
		}

		std::shared_ptr<BaseFile> dir = root_;
		auto beg = abs_path.find_first_of('/');
		auto end = abs_path.find_first_of('/', beg + 1);
		bool found = false;
		while (beg != std::string::npos) {
			if (end == std::string::npos) {
				// Like "/opt/ros"
				end = abs_path.size();
			}
			auto file_name = abs_path.substr(beg + 1, end - beg);


			beg = end;
			end = abs_path.find_first_of('/', beg + 1);
		}
	}

	FileSystem::FileSystem() :
		root_(readExistedDirectory("/")) {

	}


	std::shared_ptr<Directory> FileSystem::readExistedDirectory(const std::string &dir_name) {
		DIR *dir = opendir(dir_name.c_str());
		if (dir == nullptr) {
			return nullptr;
		}
		dirent *entry;
		struct stat dir_info{};
		if (stat(dir_name.c_str(), &dir_info) != 0) {
			std::cout << "Could not stat " << dir_name << std::endl;
			return nullptr;
		}
		auto directory = std::make_shared<Directory>(
			dir_info.st_ino,
			dir_name,
		     dir_name.back() == '/' || dir_name[dir_name.find_last_of("/\\") + 1] == '.',
		    dir_info.st_uid);
		while ((entry = readdir(dir)) != nullptr) {
			if (strcmp(entry->d_name,".") != 0 || strcmp(entry->d_name,"..") != 0) {
				continue;
			}
			std::string abs_path = dir_name + "/" + entry->d_name;
			struct stat file_info{};
			if (stat(abs_path.c_str(), &file_info) != 0) {
				std::cerr << "无法获取文件信息: " << abs_path << " - errno: " << strerror(errno) << std::endl;
				continue;
			}
			if (S_ISDIR(file_info.st_mode)) {
				directory->addChild(std::make_shared<Directory>(
				file_info.st_ino,
				abs_path,
				strlen(entry->d_name) != 0 && entry->d_name[0] == '.',
				file_info.st_uid)
			);
			}
			directory->addChild(std::make_shared<File>(
				file_info.st_ino,
				abs_path,
				strlen(entry->d_name) != 0 && entry->d_name[0] == '.',
				file_info.st_uid)
			);
		}
		return directory;
	}

	std::string FileSystem::readFile(const std::string &file_name) {
		std::string content;
		std::fstream fin(file_name.c_str(), std::ios::in | std::ios::binary);
		if (!fin.is_open()) {
			std::cerr << "Could not open file " << file_name << std::endl;
			return "";
		}
		fin.seekg(0, std::ios::beg);
		fin >> content;
		return content;
	}
} // SorenShell