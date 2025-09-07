//
// Created by musheng on 9/3/25.
//

#ifndef SORENSHELL_USERMANAGER_HPP
#define SORENSHELL_USERMANAGER_HPP

#include <unistd.h>
#include <string>
#include <unordered_map>
#include <memory>

namespace SorenShell {
	class User {
		public:
			User(std::string name, uid_t uid, gid_t gid, std::string hash_password, bool is_admin);
			~User();
			User(const User&) = delete;
			User& operator=(const User&) = delete;
			User(User&&) = delete;
			User& operator=(User&&) = delete;

			//methods
			bool logIn(const std::string &password) const;
			void logOut() const;

			//getter
			[[nodiscard]] const std::string &userName() const;
			[[nodiscard]] uid_t userId() const;
			[[nodiscard]] gid_t groupId() const;
			[[nodiscard]] bool isAdmin() const;
			[[nodiscard]] bool isLoggedIn() const;
			[[nodiscard]] const std::string &hashPassword() const;

			//setter
			bool setUserName(const std::string &name);
			bool setGroupId(gid_t gid);
			bool changePassword(const std::string &new_password);

			static std::string hashPassword(const std::string &password);

		private:
			std::string user_name_;
			uid_t user_id_;		//唯一标识符，不能改动
			gid_t group_id_;
			std::string hash_password_;
			bool is_admin_;

			mutable bool is_logged_in_;
			[[nodiscard]] bool verifyPassword(const std::string &password) const;
	};

	class UserManager {
		public:
			~UserManager();
			static UserManager &getInstance();
			const User &getUser(uid_t uid) const;

			UserManager(const UserManager&) = delete;
			UserManager& operator=(const UserManager&) = delete;
			UserManager(UserManager&&) = delete;
			UserManager& operator=(UserManager&&) = delete;

			bool addUser(std::string name, gid_t gid, const std::string &password, bool is_admin = false);
			bool deleteUser(uid_t uid);
			bool existsUser(uid_t uid) const;
			bool changeUser(uid_t uid, const std::string &password);
			uid_t getUid(const std::string &user_name) const;
			uid_t getUid() const; //返回当前的用户UID
			uid_t getDefaultUid() const;
			bool setDefaultUid(uid_t uid);

			enum {
				nuid = 100000 //not uid
			};
		private:
			UserManager();
			void loadUsers(const std::string &file_name);
			void saveAsFile(const std::string &file_name) const;
			std::unordered_map<uid_t, std::shared_ptr<User>> user_db_;
			uid_t current_uid_ = nuid;
			uid_t default_uid_ = nuid;
			std::string config_file_name_ = "../config/user.yaml";
			uid_t highest_uid_ = 0;
	};

} // SorenShell

#endif //SORENSHELL_USERMANAGER_HPP