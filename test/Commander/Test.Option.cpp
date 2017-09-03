//
//  Test.Option.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 3/9/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Commander/Option.hpp>

namespace Commander
{
	UnitTest::Suite OptionTestSuite {
		"Commander::Option",
		
		{"it can set boolean value",
			[](UnitTest::Examiner & examiner) {
				Table table;
				Options options{table};
				Option<bool> boolean_option{options, {"-b", "--boolean"}, "Set a boolean value."};
				
				ArgumentsT arguments{"--boolean"};
				
				examiner << "Parse arguments." << std::endl;
				examiner.check(table.parse(arguments));
				
				examiner.expect(*boolean_option) == true;
			}
		},
		
		{"it can set string value",
			[](UnitTest::Examiner & examiner) {
				Table table;
				Options options{table};
				Option<std::string> string_option{options, {"-s", "--string"}, "Set a string value.", "default"};
				
				ArgumentsT arguments{"--string", "foo"};
				
				examiner << "Parse arguments." << std::endl;
				examiner.check(table.parse(arguments));
				
				examiner.expect(*string_option) == "foo";
			}
		},
		
		{"it can set string value in array",
			[](UnitTest::Examiner & examiner) {
				Table table;
				Options options{table};
				Option<std::vector<std::string>> string_option{options, {"-v", "--vector"}, "Append a string value.", {"default"}};
				
				ArgumentsT arguments{"-v", "a", "--vector", "b"};
				
				examiner << "Parse arguments." << std::endl;
				examiner.check(table.parse(arguments));
				
				examiner.expect(string_option.value().size()) == 2;
				examiner.expect(string_option.value()[0]) == "a";
				examiner.expect(string_option.value()[1]) == "b";
			}
		},
	};
}
