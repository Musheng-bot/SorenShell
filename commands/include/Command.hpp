//
// Created by musheng on 9/2/25.
//

#ifndef SORENSHELL_COMMAND_HPP
#define SORENSHELL_COMMAND_HPP
#include <string>
#include <vector>

namespace SorenShell {
	class Terminal;

	class Command {
		public:
			explicit Command(const std::vector<std::string> &args, Terminal &terminal);
			virtual ~Command();
			virtual int execute() = 0;
			virtual void preprocess(const std::string &current_path) = 0;
			virtual void handleOptionalParameters() = 0;
			virtual void help() = 0;

		protected:
			std::string command_;
			std::vector<std::string> args_;
			bool help_ = false;
			Terminal &terminal_;
	};
} // SorenShell

#define DEFINE_COMMAND_CLASS(CLASS_NAME) \
	public:\
		explicit CLASS_NAME(const std::vector<std::string> &args, Terminal &terminal) :\
			Command(args, terminal){}\
		~CLASS_NAME() = default;\
		int execute() override;\
		void preprocess(const std::string &current_path) override;\
		void handleOptionalParameters() override;\
		void help() override;\

#endif //SORENSHELL_COMMAND_HPP