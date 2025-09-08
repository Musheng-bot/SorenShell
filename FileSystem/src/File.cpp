//
// Created by musheng on 9/7/25.
//

#include "../include/File.hpp"

#include <utility>

namespace SorenShell {
	File::File(int inode, std::string absolute_path, bool is_hidden, uid_t owner_uid) :
		BaseFile(inode, std::move(absolute_path), is_hidden, owner_uid) {
	}

	File::~File() = default;

	bool File::isDirectory() const {
		return false;
	}

	const std::vector<std::shared_ptr<BaseFile>> &File::children() const {
		return {};
	}

	std::shared_ptr<BaseFile> File::clone() const {
		return std::make_shared<File>(this->inode_, this->absolute_path_, this->is_hidden_, this->owner_uid_);
	}
} // SorenShell