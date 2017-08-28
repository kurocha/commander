//
//  Enumeration.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/8/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Option.hpp"

#include <map>

namespace Commander
{
	template <typename ValueT>
	class Enumeration : public GenericOption<ValueT>
	{
	using KeysT = std::map<ArgumentT, ValueT>;
		
	public:
		Enumeration(Options & options, Flags flags, std::string description, ValueT initial, KeysT keys) : GenericOption<ValueT>(options, flags, description, initial), _keys(keys) {}
		virtual ~Enumeration() {}
		
		virtual IteratorT parse(IteratorT begin, IteratorT end)
		{
			if (begin != end) {
				auto pair = _keys.find(*begin);

				if (pair != _keys.end()) {
					this->_value = pair->second;
					
					// Consume token:
					begin++;
				} else {
					
				}
			}
			
			return begin;
		}
		
		virtual void print_full_usage(std::ostream & output, std::size_t level = 0) const noexcept
		{
			GenericOption<ValueT>::print_full_usage(output, level);
			
			output << std::string(level+1, '\t') << "<value> One of: ";
			
			bool first = true;
			for (auto & pair : _keys) {
				if (first) first = false;
				else output << ", ";
				
				output << pair.first;
			}
			
			output << std::endl;
		}
		
		// ArgumentT & name_for(ValueT value)
		// {
		// 	for (auto & pair : _keys) {
		// 		if (pair.second == value) return pair.first;
		// 	}
		// 	
		// 	return "???";
		// }
		
	protected:
		KeysT _keys;
	};
}
