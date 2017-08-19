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
			output << _name << ' ';
		
		table.print_usage(output);
	}
}
