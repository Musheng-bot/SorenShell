//
// Created by musheng on 9/7/25.
//

#ifndef SORENSHELL_COMMANDFACTORY_HPP
#define SORENSHELL_COMMANDFACTORY_HPP

#include <Command.hpp>
#include <functional>
#include <map>
#include <memory>

namespace SorenShell {
	class CommandFactory {
		public:
			using Function = std::function<std::unique_ptr<Command>(const std::vector<std::string> &)>;

			static CommandFactory &getInstance();
			~CommandFactory();
			std::unique_ptr<Command> create(const std::string &command, const std::vector<std::string> &args);
			void registerCommand(const std::string& command, const Function& function);

		private:
			CommandFactory();
			std::map<std::string, Function> commands_;
	};
} // SorenShell

#endif //SORENSHELL_COMMANDFACTORY_HPP