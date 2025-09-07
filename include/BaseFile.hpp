//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_BASEFILE_HPP
#define SORENSHELL_BASEFILE_HPP
#include <memory>
#include <string>

#include "Directory.hpp"

namespace SorenShell {
	class BaseFile {
		public:
			BaseFile();
			virtual ~BaseFile();

			[[nodiscard]] int inode() const;
			[[nodiscard]] const std::string &absolutePath() const;
			[[nodiscard]] bool isDirectory() const;
			[[nodiscard]] bool isHidden() const;

			bool setAbsolutePath(const std::string &path);
			void serHidden(bool hidden);

		private:
			int inode_;
			std::string absolute_path_;
			bool is_directory;
			bool is_hidden_;
			uid_t owner_uid_;
	};
} // SorenShell

#endif //SORENSHELL_BASEFILE_HPP