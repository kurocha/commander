//
//  EnumerationTraits.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 3/9/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Parser.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <sstream>

namespace Commander
{
	template <typename NumericT>
	class NumberTraits
	{
	public:
		NumericT parse(IteratorT & begin, IteratorT end) const
		{
			if (begin != end) {
				NumericT number;
				
				std::stringstream stream(*begin++);
				stream >> number;
				
				if (!stream.good()) {
					throw ArgumentError("Could not parse number!", begin);
				}
				
				return number;
			} else {
				throw ArgumentError("Reached end of input!", begin);
			}
		}
		
		template <typename OptionT>
		void assign(OptionT * option, const NumericT & value) const
		{
			option->set(value);
		}
		
		void print_value(const NumericT & value, std::ostream & output) const
		{
			output << value;
		}
		
		template <typename OptionT>
		void print_usage(const OptionT * option, std::ostream & output) const
		{
			output << '[' << option->flags() << " <number>]";
		}
		
		void print_full_usage(std::ostream & output, std::size_t level) const {}
	};
}
