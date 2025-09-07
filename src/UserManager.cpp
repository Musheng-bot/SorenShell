//
// Created by musheng on 9/3/25.
//

#include "UserManager.hpp"

#include <iostream>
#include <pwd.h>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <utility>
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace SorenShell {
	User::User(std::string name, const uid_t uid, const gid_t gid, std::string hash_password, bool is_admin) :
		user_name_(std::move(name)),
		user_id_(uid),
		group_id_(gid),
		is_admin_(is_admin),
		is_logged_in_(false),
		hash_password_(std::move(hash_password)) {
	}

	User::~User() = default;

	bool User::logIn(const std::string &password) const {
		if (!verifyPassword(password)) {
			std::cerr << "Wrong password!" << std::endl;
			return false;
		}
		is_logged_in_ = true;
		return true;
	}

	void User::logOut() const {
		is_logged_in_ = false;
	}

	const std::string & User::userName() const {
		return user_name_;
	}

	uid_t User::userId() const {
		return user_id_;
	}

	gid_t User::groupId() const {
		return group_id_;
	}

	bool User::isAdmin() const {
		return is_admin_;
	}

	bool User::isLoggedIn() const {
		return is_logged_in_;
	}

	const std::string &User::hashPassword() const {
		return hash_password_;
	}

	bool User::setUserName(const std::string &name) {
		this->user_name_ = name;
		return true;
	}

	bool User::setGroupId(gid_t gid) {
		this->group_id_ = gid;
		return true;
	}

	bool User::changePassword(const std::string &new_password) {
		this->hash_password_ = hashPassword(new_password);
		return true;
	}

	std::string User::hashPassword(const std::string &password) {
		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256(reinterpret_cast<const unsigned char*>(password.c_str()),
			   password.size(), hash);

		std::stringstream ss;
		for (const unsigned char i : hash) {
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
		}
		return ss.str();
	}

	bool User::verifyPassword(const std::string &password) const {
		return hash_password_ == hashPassword(password);
	}

	UserManager::~UserManager() {
		user_db_[current_uid_]->logOut();
		saveAsFile(config_file_name_);
	}

	UserManager & UserManager::getInstance() {
		static UserManager instance;
		return instance;
	}

	const User &UserManager::getUser(uid_t uid) const {
		return *user_db_.at(uid);
	}

	bool UserManager::addUser(std::string name, const gid_t gid, const std::string &password, bool is_admin) {
		uid_t uid = getUid(name);
		if (existsUser(uid)) {
			return false;
		}
		uid = highest_uid_ + 1;
		highest_uid_ = uid;
		user_db_.emplace(uid,
			std::make_shared<User>(std::move(name), uid, gid, User::hashPassword(password), is_admin)
		);
		return true;
	}

	bool UserManager::deleteUser(const uid_t uid) {
		if (!existsUser(uid)) {
			return false;
		}
		return user_db_.erase(uid);
	}

	bool UserManager::existsUser(const uid_t uid) const {
		return user_db_.contains(uid);
	}

	bool UserManager::changeUser(const uid_t uid, const std::string &password) {
		auto new_user = user_db_.find(uid);
		if (new_user == user_db_.end()) {
			return false;
		}
		user_db_.at(current_uid_)->logOut();
		return user_db_.at(uid)->logIn(password);
	}

	uid_t UserManager::getUid(const std::string &user_name) const {
		for (const auto &[uid, user] : user_db_) {
			if (user->userName() == user_name) {
				return uid;
			}
		}
		return nuid;
	}

	uid_t UserManager::getUid() const {
		return current_uid_;
	}

	uid_t UserManager::getDefaultUid() const {
		return default_uid_;
	}

	bool UserManager::setDefaultUid(uid_t uid) {
		if (existsUser(uid)) {
			default_uid_ = uid;
			return true;
		}
		return false;
	}

	UserManager::UserManager() {
		loadUsers(this->config_file_name_);
		for (const auto &[uid, user] : user_db_) {
			highest_uid_ = std::max(highest_uid_, uid);
		}
		const auto user = user_db_[getUid("musheng")];
		current_uid_ = user->userId();
		if (!user->logIn("musheng685")) {
			current_uid_ = nuid;
		}
	}

	void UserManager::loadUsers(const std::string &file_name) {
		YAML::Node config = YAML::LoadFile(file_name);
		for (auto it = config.begin(); it != config.end(); ++it) {
			uid_t uid = nuid;
			std::shared_ptr<User> user;
			try {
				if (it->first.as<int>() != nuid) {
					uid = it->first.as<uid_t>();
					user = std::make_shared<User>(
						it->second["user_name"].as<std::string>(),
						it->second["uid"].as<uid_t>(),
						it->second["gid"].as<gid_t>(),
						it->second["password"].as<std::string>(),
						it->second["is_admin"].as<bool>()
					);
				}
			}
			catch (const YAML::Exception &e) {
				if (it->first.as<std::string>() == "default_user") {
					default_uid_ = it->second["uid"].as<uid_t>();
				}
			}

			if (uid != nuid) {
				user_db_.emplace(uid, std::move(user));
			}
		}
	}

	void UserManager::saveAsFile(const std::string &file_name) const {
		YAML::Node config;
		for (const auto &[user_name, user] : user_db_) {
			YAML::Node node;
			node["user_name"] = user->userName();
			node["uid"] = user->userId();
			node["gid"] = user->groupId();
			node["password"] = user->hashPassword();
			node["is_admin"] = user->isAdmin();

			config[user->userId()] = node;
		}
		YAML::Node default_user;
		default_user["uid"] = default_uid_;
		config["default_user"] = default_user;

		std::ofstream out(config_file_name_, std::ofstream::trunc | std::ofstream::out);
		if (!out.is_open()) {
			std::cerr << "Can't open config file" << std::endl;
			return;
		}
		out << config << std::flush;
		out.close();
	}
} // SorenShell