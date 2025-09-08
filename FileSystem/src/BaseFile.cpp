//
// Created by musheng on 9/7/25.
//

#include "../include/BaseFile.hpp"

#include <utility>

#include "../../User/include/UserManager.hpp"

namespace SorenShell {
	BaseFile::BaseFile(int inode, std::string absolute_path, bool is_hidden, uid_t owner_uid) :
		inode_(inode),
		absolute_path_(std::move(absolute_path)),
		is_hidden_(is_hidden),
		owner_uid_(owner_uid),
		permission_(0664) {
		auto begin = absolute_path_.find_last_of("/\\");
		file_name_ = absolute_path_.substr(begin + 1);
	}

	BaseFile::~BaseFile() = default;

	int BaseFile::inode() const {
		return inode_;
	}

	const std::string & BaseFile::absolutePath() const {
		return absolute_path_;
	}

	const std::string &BaseFile::fileName() const {
		return file_name_;
	}

	bool BaseFile::isHidden() const {
		return is_hidden_;
	}

	uid_t BaseFile::ownerUid() const {
		return owner_uid_;
	}

	bool BaseFile::isOwner(uid_t uid) const {
		return owner_uid_ == uid;
	}

	void BaseFile::setAbsolutePath(const std::string &path) {
		absolute_path_ = path;
	}

	void BaseFile::setHidden(bool hidden) {
		is_hidden_ = hidden;
	}

	bool BaseFile::isUserReadable(uid_t uid) const {
		auto &user_manager = UserManager::getInstance();
		const User &user = user_manager.getUser(uid);
		if (user.isAdmin()) {
			return (permission_ >> 8) & 1;
		}
		if (isOwner(uid)) {
			return (permission_ >> 5) & 1;
		}
		if (user.groupId() == user_manager.getUser(owner_uid_).groupId()) {
			return (permission_ >> 2) & 1;
		}
		return false;
	}

	bool BaseFile::isUserWritable(uid_t uid) const {
		auto &user_manager = UserManager::getInstance();
		const User &user = user_manager.getUser(uid);
		if (user.isAdmin()) {
			return (permission_ >> 7) & 1;
		}
		if (isOwner(uid)) {
			return (permission_ >> 4) & 1;
		}
		if (user.groupId() == user_manager.getUser(owner_uid_).groupId()) {
			return (permission_ >> 1) & 1;
		}
		return false;
	}

	bool BaseFile::isUserExecutable(uid_t uid) const {
		auto &user_manager = UserManager::getInstance();
		const User &user = user_manager.getUser(uid);
		if (user.isAdmin()) {
			return (permission_ >> 6) & 1;
		}
		if (isOwner(uid)) {
			return (permission_ >> 3) & 1;
		}
		if (user.groupId() == user_manager.getUser(owner_uid_).groupId()) {
			return permission_ & 1;
		}
		return false;
	}

	std::map<std::string, std::shared_ptr<BaseFile>> &BaseFile::pathToFile() {
		static std::map<std::string, std::shared_ptr<BaseFile>> path_to_file;
		return path_to_file;
	}

} // SorenShell