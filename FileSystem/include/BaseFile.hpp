//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_BASEFILE_HPP
#define SORENSHELL_BASEFILE_HPP
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace SorenShell {
	class BaseFile {
		public:
			BaseFile(int inode, std::string absolute_path, bool is_hidden, uid_t owner_uid);
			virtual ~BaseFile();
			[[nodiscard]] virtual std::shared_ptr<BaseFile> clone() const = 0;

			[[nodiscard]] int inode() const;
			[[nodiscard]] const std::string &absolutePath() const;
			[[nodiscard]] const std::string &fileName() const;
			[[nodiscard]] virtual bool isDirectory() const = 0;
			[[nodiscard]] bool isHidden() const;
			[[nodiscard]] uid_t ownerUid() const;
			[[nodiscard]] bool isOwner(uid_t uid) const;

			void setAbsolutePath(const std::string &path);
			void setHidden(bool hidden);

			[[nodiscard]] bool isUserReadable(uid_t uid) const;
			[[nodiscard]] bool isUserWritable(uid_t uid) const;
			[[nodiscard]] bool isUserExecutable(uid_t uid) const;

			[[nodiscard]] virtual const std::vector<std::shared_ptr<BaseFile>> &children() const = 0;

		protected:
			int inode_;
			std::string absolute_path_;
			std::string file_name_;
			bool is_hidden_;
			uid_t owner_uid_;
			mode_t permission_;

			static std::map<std::string, std::shared_ptr<BaseFile>> &pathToFile();
	};
} // SorenShell

#endif //SORENSHELL_BASEFILE_HPP