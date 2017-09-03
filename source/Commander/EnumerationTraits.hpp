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

namespace Commander
{
	template <typename ValueT>
	class EnumerationTraits
	{
	public:
		struct Mapping
		{
			std::string key;
			ValueT value;
			std::string description;
		};
		
		EnumerationTraits(std::initializer_list<Mapping> mappings) : _mappings(mappings)
		{
			for (auto & mapping : _mappings) {
				_keyed.insert({mapping.key, mapping.value});
			}
		}
		
		ValueT parse(IteratorT & begin, IteratorT end) const
		{
			if (begin != end) {
				auto pair = _keyed.find(*begin++);
				
				if (pair != _keyed.end()) {
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
			for (auto & mapping : _mappings) {
				if (mapping.value == value) {
					output << mapping.key;
					
					return;
				}
			}
			
			output << "???";
		}
		
		template <typename OptionT>
		void print_usage(const OptionT * option, std::ostream & output) const
		{
			output << '[' << option->flags() << " <key>]";
			
			// bool first = true;
			// for (auto & mapping : _mappings) {
			// 	if (first) first = false;
			// 	else output << '/';
			// 	
			// 	output << mapping.key;
			// }
			// 
			// output << '>' << ']';
		}
		
		void print_full_usage(std::ostream & output, std::size_t level) const
		{
			output << std::string(level, '\t');
			
			auto size = _mappings.size();
			
			if (size == 0) {
				output << "No values available." << std::endl;
			} else if (size == 1) {
				output << "<key> must be " << _mappings.front().key << '.' << std::endl;
			} else {
				output << "<key> must be one of ";
				bool first = true;
				
				for (auto & mapping : _mappings) {
					if (!first) output << ", ";
					else first = false;
					
					output << mapping.key;
				}
				
				output << '.';
			}
			
			output << std::endl;
			
			print_mappings(output, level+1);
		}
		
		void print_mappings(std::ostream & output, std::size_t level) const
		{
			std::string indent(level, '\t');
			
			for (auto & mapping : _mappings) {
				output << indent << mapping.key << ": " << mapping.description << std::endl;
			}
		}
		
	protected:
		std::vector<Mapping> _mappings;
		std::map<ArgumentT, ValueT> _keyed;
	};
}
