//
// Created by musheng on 9/8/25.
//

#include "User.hpp"
#include <string>
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

} // SorenShell