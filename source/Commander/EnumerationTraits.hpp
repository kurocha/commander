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
#include <iostream>

namespace Commander
{
	template <typename ValueT, const std::map<std::string, ValueT> & KEYS>
	struct EnumerationTraits
	{
		static ValueT parse(IteratorT & begin, IteratorT end)
		{
			if (begin != end) {
				auto pair = KEYS.find(*begin++);
				
				if (pair != KEYS.end()) {
					return pair->second;
				}
			}
			
			throw ArgumentError("Could not parse enumeration value", begin);
		}
		
		template <typename OptionT>
		static void assign(OptionT * option, const ValueT & value)
		{
			option->set(value);
		}
		
		static void print_value(const ValueT & value, std::ostream & output)
		{
			for (auto & pair : KEYS) {
				if (pair.second == value) {
					output << pair.first;
					
					return;
				}
			}
			
			output << "???";
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			output << '[' << option->flags() << " <";
			
			bool first = true;
			for (auto & pair : KEYS) {
				if (first) first = false;
				else output << '/';
				
				output << pair.first;
			}
			
			output << '>' << ']';
		}
	};
}
