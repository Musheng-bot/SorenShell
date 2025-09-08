//
// Created by musheng on 9/7/25.
//

#include "../include/HardwareManager.hpp"

#include <fstream>

namespace SorenShell {
	HardwareManager &HardwareManager::getInstance() {
		static HardwareManager manager;
		return manager;
	}

	HardwareManager::~HardwareManager() = default;

	const std::string & HardwareManager::getHostName() const {
		return host_name_;
	}

	HardwareManager::HardwareManager() {
		host_name_ = readFile("/proc/sys/kernel/hostname");
		host_name_.pop_back();
	}

	std::string HardwareManager::readFile(const std::string &path) {
		std::ifstream file;
		file.open(path, std::ios::in | std::ios::binary);
		if (file.is_open()) {
			return std::string{std::istreambuf_iterator<char>(file),
							   std::istreambuf_iterator<char>()};
		}
		return ""; // 读取失败返回空
	}
} // SorenShell