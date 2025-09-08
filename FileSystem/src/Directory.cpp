//
// Created by musheng on 9/7/25.
//

#include "../include/Directory.hpp"

#include <utility>

namespace SorenShell {
	Directory::Directory(int inode, std::string absolute_path, bool is_hidden, uid_t owner_uid, const std::vector<std::shared_ptr<BaseFile>> &children) :
		BaseFile(inode, std::move(absolute_path), is_hidden, owner_uid),
		children_(children) {
	}

	Directory::~Directory() = default;

	bool Directory::isDirectory() const {
		return true;
	}

	const std::vector<std::shared_ptr<BaseFile>> &Directory::children() const {
		return this->children_;
	}

	std::shared_ptr<BaseFile> Directory::clone() const {
		return std::make_shared<Directory>(inode(), absolutePath(), isHidden(), ownerUid(), children());
	}

	void Directory::addChild(const std::shared_ptr<BaseFile>& child) {
		this->children_.push_back(child);
	}

	bool Directory::removeChild(const std::shared_ptr<BaseFile>& child) {
		const auto it = std::find(children_.begin(), children_.end(), child);
		if (it == children_.end()) {
			return false;
		}
		children_.erase(it);
		return true;
	}
} // SorenShell