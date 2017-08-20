//
//  Field.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Field.hpp"

#include <iostream>

namespace Commander
{
	Field::~Field()
	{
	}
	
	void Field::print_full_usage(std::ostream & output, std::size_t level) const noexcept
	{
		output << std::string(level, '\t');
		
		print_usage(output);
		
		output << ' ' << _description << std::endl;
	}
}
