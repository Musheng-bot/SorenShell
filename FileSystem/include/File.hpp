//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_FILE_HPP
#define SORENSHELL_FILE_HPP
#include "BaseFile.hpp"

namespace SorenShell {
	class File final : public BaseFile{
		public:
			File(int inode, std::string absolute_path, bool is_hidden, uid_t owner_uid);
			~File() override;
			[[nodiscard]] bool isDirectory() const override;
			[[nodiscard]] const std::vector<std::shared_ptr<BaseFile>> &children() const override;
			[[nodiscard]] std::shared_ptr<BaseFile> clone() const override;

	};
} // SorenShell

#endif //SORENSHELL_FILE_HPP