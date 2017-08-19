//
//  Flags.cpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Flags.hpp"

#include <iostream>

namespace Commander
{
	Flags::~Flags()
	{
	}
	
	std::ostream & operator<<(std::ostream & output, const Flags & flags)
	{
		bool first = true;
		
		for (auto & key : flags.keys()) {
			if (!first) output << '/';
			else first = false;
			
			output << key;
		}
	}
}
