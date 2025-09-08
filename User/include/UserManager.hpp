//
// Created by musheng on 9/3/25.
//

#ifndef SORENSHELL_USERMANAGER_HPP
#define SORENSHELL_USERMANAGER_HPP

#include <unistd.h>
#include <string>
#include <unordered_map>
#include <memory>
#include "User.hpp"
namespace SorenShell {

	class UserManager {
		public:
			UserManager();
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