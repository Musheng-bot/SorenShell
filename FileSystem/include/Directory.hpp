//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_DIRECTORY_HPP
#define SORENSHELL_DIRECTORY_HPP

#include "BaseFile.hpp"

namespace SorenShell {
	class Directory : public BaseFile {
		public:
			Directory(int inode, std::string absolute_path, bool is_hidden, uid_t owner_uid,
			          const std::vector<std::shared_ptr<BaseFile> > &children = {});
			~Directory() override;
			[[nodiscard]] bool isDirectory() const override;
			[[nodiscard]] const std::vector<std::shared_ptr<BaseFile>> &children() const override;
			[[nodiscard]] std::shared_ptr<BaseFile> clone() const override;

			void addChild(const std::shared_ptr<BaseFile>& child);
			bool removeChild(const std::shared_ptr<BaseFile>& child);

		private:
			std::vector<std::shared_ptr<BaseFile>> children_;
	};
} // SorenShell

#endif //SORENSHELL_DIRECTORY_HPP