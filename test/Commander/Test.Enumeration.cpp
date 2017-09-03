//
//  Test.Enumeration.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Commander/Command.hpp>
#include <Commander/EnumerationTraits.hpp>

#include <map>

namespace Commander
{
	enum class OutputFormat : std::uint32_t {
		PNG, JPEG, WEBP_LOSSY, WEBP_LOSSLESS, RAW
	};
	
	template <>
	class OptionTraits<OutputFormat> : public EnumerationTraits<OutputFormat>
	{
	public:
		OptionTraits() : EnumerationTraits<OutputFormat>{
			{"png", OutputFormat::PNG, "PNG encoded data."},
			{"jpeg", OutputFormat::JPEG, "JPEG encoded data."},
			{"webp-lossy", OutputFormat::WEBP_LOSSY, "WebP lossy encoded data."},
			{"webp-lossless", OutputFormat::WEBP_LOSSY, "WebP lossless encoded data."},
			{"raw", OutputFormat::RAW, "Raw RGBA data."},
		} {}
	};
	
	class EnumerationProgram : public Command
	{
	public:
		EnumerationProgram(Commands & commands) : Command(commands, "", "Enumerate some values") {}

		Options options{table};
		
		Option<OutputFormat> output_format{options, {"-f", "--output-format"}, "The output pixel buffer format.", OutputFormat::PNG};
		Option<std::string> output_path{options, {"-o", "--output-path"}, "The output path", "things.txt"};
	};
	
	UnitTest::Suite EnumerationTestSuite {
		"Commander::Enumeration",
		
		{"it should have some real tests",
			[](UnitTest::Examiner & examiner) {
				ArgumentsT arguments{"program", "-f", "raw"};
				
				Table table;
				Commands commands{table};
				EnumerationProgram program{commands};
				
				auto end = table.parse(arguments.begin(), arguments.end());
				
				examiner << "Parsed all arguments" << std::endl;
				examiner.check(end == arguments.end());
				
				examiner.check(program.output_format.value() == OutputFormat::RAW);
				
				table.print_full_usage(std::cerr);
			}
		},
	};
}
