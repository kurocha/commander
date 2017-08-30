//
//  Test.Command.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Commander/Command.hpp>
#include <Commander/Option.hpp>

namespace Commander
{
	class Program;
	
	class ListThings : public Command
	{
		Program * _program;
	public:
		ListThings(Commands & commands, Program * program) : Command(commands, "list-things", "Print all the things."), _program(program) {}
		
		virtual ~ListThings() {}
		
		virtual void invoke()
		{
			std::cerr << "1 2 3 " << _program << std::endl;
		}
	};
	
	class Program : public Command
	{
	public:
		Program(Commands & commands) : Command(commands) {}

		Options options{table};
		Option<bool> debug{options, {"-d", "--debug"}, "Enable debug assertions and output."};

		Commands commands{table};
		ListThings list_things{commands, this};
	};
	
	UnitTest::Suite CommandTestSuite {
		"Commander::Command",
		
		{"it recognize -d",
			[](UnitTest::Examiner & examiner) {
				ArgumentsT arguments{"exec", "-d", "list-things"};
				
				Table table;
				Commands commands{table};
				Program program{commands};
				
				auto end = table.parse(arguments.begin(), arguments.end());
				
				examiner << "Parsed all arguments" << std::endl;
				examiner.check(end == arguments.end());
				
				examiner.expect(program.debug.value()) == true;
				
				examiner.expect(program.commands.value()) == &program.list_things;
			}
		},
		
		{"it prints basic usage",
			[](UnitTest::Examiner & examiner) {
				Table table;
				Commands commands{table};
				Program program{commands};
				
				ArgumentsT arguments{"commander", "-d", "list-things"};
				table.parse(arguments.begin(), arguments.end());
				
				std::stringstream buffer;
				program.print_usage(buffer);
				
				examiner.expect(buffer.str()) == "commander [-d/--debug] <command>";
			}
		},
		
		{"it prints detailed usage",
			[](UnitTest::Examiner & examiner) {
				Table table;
				Commands commands{table};
				Program program{commands};
				
				ArgumentsT arguments{"commander", "-d", "help"};
				table.parse(arguments.begin(), arguments.end());
				
				std::stringstream buffer;
				table.print_full_usage(std::cerr);
				
				// examiner.expect(buffer.str()) == "commander [-d/--debug] <command>";
			}
		},
	};
}
