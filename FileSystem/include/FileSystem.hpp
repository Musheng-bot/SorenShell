//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_FILESYSTEM_HPP
#define SORENSHELL_FILESYSTEM_HPP
#include "Directory.hpp"
#include "File.hpp"

namespace SorenShell {
	class FileSystem {
		public:
			static FileSystem& getInstance();
			~FileSystem() = default;
			FileSystem(const FileSystem&) = delete;
			FileSystem& operator=(const FileSystem&) = delete;
			FileSystem(FileSystem&&) = delete;
			FileSystem& operator=(FileSystem&&) = delete;

			bool createFile(const std::string& parent_dir, const std::string& file_name, mode_t permission = 0664);
			bool createDirectory(const std::string &parent_dir, const std::string& dir_name, mode_t permission = 0664);
			bool fileExists(const std::string& file_name) const;
			bool directoryExists(const std::string& dir_name) const;
			bool removeFile(const std::string& file_name);
			bool removeDirectory(const std::string& dir_name);
			bool setPermission(const std::string& file_name, mode_t permission);

			std::shared_ptr<BaseFile> getFile(const std::string& abs_path);

		private:
			FileSystem();
			std::shared_ptr<Directory> root_;

			static std::shared_ptr<Directory> readExistedDirectory(const std::string &dir_name);
			static std::string readFile(const std::string &file_name);
	};
} // SorenShell

#endif //SORENSHELL_FILESYSTEM_HPP