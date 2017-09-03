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
	
	const std::map<std::string, OutputFormat> OutputFormatKeys {
		{"png", OutputFormat::PNG},
		{"jpeg", OutputFormat::JPEG},
		{"webp-lossy", OutputFormat::WEBP_LOSSY},
		{"webp-lossless", OutputFormat::WEBP_LOSSLESS},
		{"raw", OutputFormat::RAW}
	};
	
	template <>
	struct OptionTraits<OutputFormat> : public EnumerationTraits<OutputFormat, OutputFormatKeys> {};
	
	class EnumerationProgram : public Command
	{
	public:
		EnumerationProgram(Commands & commands) : Command(commands) {}

		Options options{table};
		
		// Enumeration<OutputFormat> output_formats{
		// 	{"png", OutputFormat::PNG, "PNG pixel data."}
		// 	{"jpeg", OutputFormat::JPEG, "JPEG pixel data."}
		// 	{"webp-lossy", OutputFormat::WEBP_LOSSY, "Lossy WebP pixel data."}
		// 	{"webp-lossless", OutputFormat::WEBP_LOSSY, "WebP pixel data."}
		// 	{"raw", OutputFormat::RAW, "Lossy WebP pixel data."}
		// };
		
		Option<OutputFormat> output_format{options, {"-f", "--output-format"}, "The output pixel buffer format.", OutputFormat::PNG};
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
