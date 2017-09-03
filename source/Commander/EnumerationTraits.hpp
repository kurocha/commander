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
	template <typename ValueT>
	struct EnumerationTraits
	{
		using KeysT = std::map<ArgumentT, ValueT>;
		
		KeysT keys;
		
		EnumerationTraits(const KeysT & _keys) : keys(_keys) {}
		
		ValueT parse(IteratorT & begin, IteratorT end) const
		{
			if (begin != end) {
				auto pair = keys.find(*begin++);
				
				if (pair != keys.end()) {
					return pair->second;
				}
			}
			
			throw ArgumentError("Could not parse enumeration value", begin);
		}
		
		template <typename OptionT>
		void assign(OptionT * option, const ValueT & value) const
		{
			option->set(value);
		}
		
		void print_value(const ValueT & value, std::ostream & output) const
		{
			for (auto & pair : keys) {
				if (pair.second == value) {
					output << pair.first;
					
					return;
				}
			}
			
			output << "???";
		}
		
		template <typename OptionT>
		void print_usage(const OptionT * option, std::ostream & output) const
		{
			output << '[' << option->flags() << " <";
			
			bool first = true;
			for (auto & pair : keys) {
				if (first) first = false;
				else output << '/';
				
				output << pair.first;
			}
			
			output << '>' << ']';
		}
	};
}
