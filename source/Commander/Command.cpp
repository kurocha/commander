//
//  Command.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Command.hpp"

#include <iostream>

namespace Commander
{
	Command::~Command()
	{
	}
	
	IteratorT Command::parse(IteratorT begin, IteratorT end)
	{
		if (begin != end) {
			if (_name.empty()) {
				_name = *begin;

				return table.parse(++begin, end);
			} else if (_name == *begin) {
				return table.parse(++begin, end);
			}
		}

		return begin;
	}
	
	void Command::print_usage(std::ostream & output) const noexcept
	{
		if (!_name.empty())
			output << _name;
		
		if (!table.empty()) {
			output << ' ';
			table.print_usage(output);
		}
	}
	
	void Command::print_full_usage(std::ostream & output, std::size_t level) const noexcept
	{
		output << std::string(level, '\t');
		
		print_usage(output);
		
		if (!_description.empty())
			output << std::endl << std::string(level+1, '\t') << _description;
		
		output << std::endl << std::endl;
		
		table.print_full_usage(output, level+1);
	}
}
