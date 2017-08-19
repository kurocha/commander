//
//  Options.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Options.hpp"

#include <iostream>

namespace Commander
{
	Options::~Options()
	{
	}
	
	void Options::print_usage(std::ostream & output) const noexcept
	{
		bool first = true;
		
		for (auto field : _ordered) {
			if (!first) output << ' ';
			else first = false;
			
			field->print_usage(output);
		}
	}
}
