//
//  Flags.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <vector>
#include <string>
#include <iosfwd>

namespace Commander
{
	class Flags
	{
		std::vector<std::string> _keys;

	public:
		Flags(std::initializer_list<std::string> keys) : _keys(keys) {}
		Flags(std::string key) : _keys({key}) {}
		Flags(const char * key) : _keys({key}) {}
		
		virtual ~Flags();

		auto keys() const {return _keys;}
	};
	
	std::ostream & operator<<(std::ostream & output, const Flags & flags);
}
