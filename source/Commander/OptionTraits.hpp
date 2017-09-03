//
//  OptionTraits.hpp
//  This file is part of the "Commander" project and released under the MIT License.
//
//  Created by Samuel Williams on 3/9/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Parser.hpp"

#include <iostream>

namespace Commander
{
	template <typename T>
	struct OptionTraits
	{
		static T parse(IteratorT & begin, IteratorT end)
		{
			if (begin != end) {
				return *begin++;
			} else {
				throw ArgumentError("Reached end of input!", begin);
			}
		}
		
		template <typename OptionT>
		static void assign(OptionT * option, const T & value)
		{
			option->set(value);
		}
		
		static void print_value(const T & value, std::ostream & output)
		{
			output << value;
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			output << '[' << option->flags() << " <value>]";
		}
	};
	
	template<>
	struct OptionTraits<bool>
	{
		static bool parse(IteratorT & begin, IteratorT end)
		{
			return true;
		}
		
		template <typename OptionT>
		static void assign(OptionT * option, const bool & value)
		{
			option->set(value);
		}
		
		static void print_value(const bool & value, std::ostream & output)
		{
			output << (value ? "yes" : "no");
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			output << '[' << option->flags() << ']';
		}
	};
	
	template<typename T>
	struct OptionTraits<std::vector<T>>
	{
		using TraitsT = OptionTraits<T>;
		
		static T parse(IteratorT & begin, IteratorT end)
		{
			return TraitsT::parse(begin, end);
		}
		
		template <typename OptionT>
		static void assign(OptionT * option, const T & value)
		{
			// If the user sets something, we clear all the default values.
			if (option->specified() == Specified::DEFAULT) {
				option->value().clear();
			}
			
			option->value().push_back(value);
		}
		
		static void print_value(const std::vector<T> & value, std::ostream & output)
		{
			output << '{';
			bool first = true;
			for (const auto & item : value) {
				if (first) first = false;
				else output << ", ";
				
				TraitsT::print_value(item, output);
			}
			output << '}';
		}
		
		template <typename OptionT>
		static void print_usage(const OptionT * option, std::ostream & output)
		{
			TraitsT::print_usage(option, output);
			output << '*';
		}
	};
}
