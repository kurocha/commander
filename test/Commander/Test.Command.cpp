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
	
	class Help : public Command
	{
		Program * _program;
	public:
		Help(Commands & commands, Program * program) : Command(commands, "help"), _program(program) {}
		
		virtual ~Help() {}
		
		virtual void invoke()
		{
			std::cerr << "Help" << std::endl;
		}
	};

	class Version : public Command
	{
		Program * _program;
	public:
		Version(Commands & commands, Program * program) : Command(commands, "version"), _program(program) {}
		
		virtual ~Version() {}
		
		virtual void invoke()
		{
			// program.table.print_usage(std::cerr);
			std::cerr << "Version" << std::endl;
		}
	};
	
	class Program : public Command
	{
	public:
		Program(Commands & commands) : Command(commands) {}

		Options options{table};
		Option<bool> debug{options, {"-d", "--debug"}, "Enable debug assertions and output."};

		Commands commands{table};
		Help help{commands, this};
		Version version{commands, this};
	};
	
	UnitTest::Suite CommandTestSuite {
		"Commander::Command",
		
		{"it recognize -d",
			[](UnitTest::Examiner & examiner) {
				ArgumentsT arguments{"exec", "-d", "help"};
				
				Table table;
				Commands commands{table};
				Program program{commands};
				
				auto end = table.parse(arguments.begin(), arguments.end());
				
				examiner << "Parsed all arguments" << std::endl;
				examiner.check(end == arguments.end());
				
				examiner.expect(program.debug.value()) == true;
				
				examiner.expect(program.commands.value()) == &program.help;
			}
		},
		
		{"it prints basic usage",
			[](UnitTest::Examiner & examiner) {
				Table table;
				Commands commands{table};
				Program program{commands};
				
				std::stringstream buffer;
				program.print_usage(buffer);
				
				examiner.expect(buffer.str()) == "-d/--debug <command>";
			}
		},
	};
}
