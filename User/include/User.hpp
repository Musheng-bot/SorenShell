#ifndef SORENSHELL_USER_HPP
#define SORENSHELL_USER_HPP

#include <functional>
#include <string>

namespace SorenShell {
	class User {
		public:
			static uid_t getUid();
			static std::string getUserName();
			static gid_t getGid();
			static std::string getHomeDirectory();
			static std::string getUserName(uid_t uid);
			static std::string getHomeDirectory(uid_t uid);
			static gid_t getGid(gid_t uid);

			static void runTaskAsUser(std::function<void()> task, const std::string& user);
			static bool setUid(uid_t uid);
			[[maybe_unused]] static bool changeUserName(uid_t uid, const std::string &userName);
	};

} // SorenShell

#endif //SORENSHELL_USER_HPP