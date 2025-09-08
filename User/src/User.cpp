#include "User.hpp"

#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <sys/wait.h>

namespace SorenShell {
	uid_t User::getUid() {
		return getuid();
	}

	gid_t User::getGid() {
		return getGid(getUid());
	}

	std::string User::getHomeDirectory() {
		return getHomeDirectory(getUid());
	}

	std::string User::getUserName(uid_t uid) {
		const auto pwd = getpwuid(uid);
		if (pwd == nullptr) {
			return "";
		}
		return {pwd->pw_name};
	}

	std::string User::getHomeDirectory(uid_t uid) {
		const auto pwd = getpwuid(getUid());
		if (pwd == nullptr) {
			return "";
		}
		return {pwd->pw_dir};
	}

	gid_t User::getGid(gid_t uid) {
		auto pwd = getpwuid(uid);
		if (pwd == nullptr) {
			return -1;
		}
		return pwd->pw_gid;
	}

	void User::runTaskAsUser(std::function<void()> task, const std::string& user) {
		auto pwd = getpwnam(user.c_str());
		if (pwd == nullptr) {
			std::cout << "User " << user << " does not exist" << std::endl;
			return;
		}
		std::cout << "User " << getpwuid(getUid())->pw_name << " is switching to user " << pwd->pw_name << std::endl;
		pid_t pid = fork();
		if (pid == -1) {
			std::cout << "Error when creating process!" << std::endl;
			return;
		}
		if (pid == 0) {
			// 先切换组ID，再切换用户ID（顺序很重要）
			if (setgid(pwd->pw_gid) == -1) {
				std::cout << "Error when switching group!" << std::endl;
				exit(EXIT_FAILURE);
			}

			if (setuid(pwd->pw_uid) == -1) {
				std::cout << "Error when switching user!" << std::endl;
				exit(EXIT_FAILURE);
			}

			// 验证切换是否成功
			if (geteuid() != pwd->pw_uid) {
				std::cout << "Error when switching user!" << std::endl;
				exit(EXIT_FAILURE);
			}
			task();
			exit(EXIT_SUCCESS);
		}
		int status;
		waitpid(pid, &status, 0);
		if (status == EXIT_FAILURE) {
			std::cout << "Something went wrong when switching user! Please retry!" << std::endl;
		}
		else if (status == EXIT_SUCCESS) {
			std::cout << "Successfully when switching user!" << std::endl;
		}
	}


	bool User::setUid(uid_t uid) {
		bool ret = setuid(uid) != -1;
		if (!ret) {
			std::cout << "Failed to set user id: " << uid << std::endl;
		}
		return ret;
	}

	bool User::changeUserName(uid_t uid, const std::string &userName) {
		//... not inplemented
		return false;
	}

	std::string User::getUserName() {
		return getUserName(getUid());
	}


}
