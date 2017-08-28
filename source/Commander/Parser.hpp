//
//  Parser.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <vector>
#include <string>

#include <stdexcept>

namespace Commander
{
	using ArgumentT = std::string;
	using ArgumentsT = std::vector<ArgumentT>;
	using IteratorT = ArgumentsT::const_iterator;
	
	class ArgumentError : public std::invalid_argument
	{
	public:
		ArgumentError(std::string description, IteratorT at) : std::invalid_argument(description), _at(at) {}
		
		auto at() const noexcept {return _at;}
		
	private:
		IteratorT _at;
	};
}
