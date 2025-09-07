//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_HARDWAREMANAGER_HPP
#define SORENSHELL_HARDWAREMANAGER_HPP
#include <string>

namespace SorenShell {
	class HardwareManager {
		public:
			static HardwareManager &getInstance();
			~HardwareManager();
			HardwareManager(const HardwareManager &) = delete;
			HardwareManager &operator=(const HardwareManager &) = delete;
			HardwareManager(HardwareManager &&) = delete;
			HardwareManager &operator=(HardwareManager &&) = delete;

			//getter
			[[nodiscard]] const std::string &getHostName() const;

		private:
			HardwareManager();

			std::string host_name_;
			std::string device_type_;
			std::string manufacturer_;
			std::string serial_number_;

			static std::string readFile(const std::string& path);
	};
} // SorenShell

#endif //SORENSHELL_HARDWAREMANAGER_HPP