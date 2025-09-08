//
// Created by musheng on 9/8/25.
//

#ifndef SORENSHELL_USER_HPP
#define SORENSHELL_USER_HPP

#include <string>
#include <unistd.h>

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

} // SorenShell

#endif //SORENSHELL_USER_HPP